// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

static const qint32 LengthOfLength = 5;

MarcRecord* Iso2709::readRecord(QIODevice &device, QTextCodec &encoding) {

    // Считываем длину записи
    char marker[LengthOfLength];
    if (device.read(marker, LengthOfLength) != LengthOfLength) {
        return nullptr;
    }

    // а затем и ее остаток
    const qint32 recordLength = fastParse32(marker, 5);
    char *record = new char[recordLength];
    const int need = static_cast<int>(recordLength - LengthOfLength);
    if (device.read(record + LengthOfLength, need) != need) {
        delete []record;
        return nullptr;
    }

    // Простая проверка, что мы имеем дело
    // с нормальной ISO-записью
    if (record[recordLength - 1] != RecordDelimiter) {
        delete[] record;
        return nullptr;
    }

    const qint32 baseAddress = fastParse32(record + 12, 5);
    const qint32 indicatorLength = fastParse32(record + 10, 1); // как правило, 2
    MarcRecord *result = new MarcRecord;

    // Пошли по полям при помощи справочника
    for (qint32 directory = MarkerLength;; directory += 12) {
        // Переходим к очередному полю.
        // Если нарвались на разделитель, значит, справочник закончился
        if (record[directory] == FieldDelimiter) {
            break;
        }

        int tag = fastParse32(record + directory, 3);
        const qint32 fieldLength = fastParse32(record + directory + 3, 4); //-V112
        const qint32 fieldOffset = baseAddress + fastParse32(record + directory + 7, 5);
        RecordField field(tag);
        result->fields.append(field);
        if (tag < 10) {
            // Фиксированное поле
            // не может содержать подполей и индикаторов
            field.value = encoding.toUnicode(record + fieldOffset, fieldLength - 1);
        } else {
            // Поле переменной длины
            // Содержит два однобайтных индикатора
            // Может содержать подполя

            // Пропускаем индикаторы
            qint32 start = fieldOffset + indicatorLength;
            const qint32 stop = fieldOffset + fieldLength - indicatorLength + 1;
            qint32 position = start;

            // Ищем значение поля до первого разделителя
            while (position < stop) {
                if (record[start] == SubFieldDelimiter) {
                    break;
                }
                position++;
            }

            // Если есть текст до первого разделителя, запоминаем его
            if (position != start) {
                field.value = encoding.toUnicode(record + start, position - start);
            }

            // Просматриваем подполя
            start = position;
            while (start < stop) {
                position = start + 1;
                while (position < stop) {
                    if (record[position] == SubFieldDelimiter) {
                        break;
                    }
                    position++;
                }
                SubField subField(record[start + 1]);
                subField.value = encoding.toUnicode(record + start + 2, position - start - 1);
                field.subfields.append(subField);
                start = position;
            }
        }
    }

    delete []record;

    return result;
}

static void encode(QByteArray &bytes, qint32 pos, qint32 len, qint32 val) {
    len--;
    for (pos += len; len >= 0; len--) {
        bytes[pos] = static_cast<char>(val % 10 + '0');
        val /= 10;
        pos--;
    }
}

static qint32 encode(QByteArray &bytes, qint32 pos, const QString &str, QTextCodec &encoding) {
    if (!str.isEmpty()) {
        QByteArray encoded = encoding.fromUnicode(str);
        for (int i = 0; i < encoded.length(); pos++, i++) {
            bytes[pos] = encoded[i];
        }
    }

    return pos;
}

static int countBytes(const QString &text, QTextCodec &encoding) {
    if (text.isEmpty()) {
        return 0;
    }

    return encoding.fromUnicode(text).size();
}

void Iso2709::writeRecord(QIODevice &device, const MarcRecord &record, QTextCodec &encoding) {
    qint32 recordLength = MarkerLength;
    qint32 dictionaryLength = 1; // с учетом ограничителя справочника
    QVector<qint32> fieldLength(record.fields.size());

    // Сначала подсчитываем общую длину
    for (int i = 0; i < record.fields.size(); i++) {
        dictionaryLength += 12; // одна статья справочника
        const RecordField &field = record.fields[i];

        if ((field.tag <= 0) || (field.tag >= 1000)) {
            throw IrbisException();
        }

        qint32 fldlen = 0;
        if (field.tag < 10) {
            // В фиксированном поле не бывает подполей и индикаторов
            fldlen += countBytes(field.value, encoding);
        } else {
            fldlen += 2; // индиакторы
            fldlen += countBytes(field.value, encoding);
            for (int j = 0; j < field.subfields.size(); j++) {
                const SubField &subfield = field.subfields[j];

                if ((subfield.code) <= ' ' || (subfield.code >= 127)) {
                    throw IrbisException();
                }

                fldlen += 2; // признак подполя и его код
                fldlen += countBytes(subfield.value, encoding);
            }
        }

        fldlen++; // разделитель полей

        if (fldlen >= 10000) {
            throw IrbisException();
        }

        fieldLength[i] = fldlen;
        recordLength += fldlen;
    }

    recordLength += dictionaryLength; // справочник
    recordLength++; // разделитель записей

    if (recordLength >= 100000) {
        throw IrbisException();
    }

    // Приступаем к кодированию
    qint32 dictionaryPosition = MarkerLength;
    const qint32 baseAddress = MarkerLength + dictionaryLength;
    qint32 currentAddress = baseAddress;
    QByteArray bytes(recordLength, ' ');

    // Маркер записи
    encode(bytes,  0, 5, recordLength);
    encode(bytes, 12, 5, baseAddress);
    bytes[5]  = 'n'; // Record status //-V557
    bytes[6]  = 'a'; // Record type //-V557
    bytes[7]  = 'm'; // Bibligraphical index //-V557
    bytes[8]  = '2'; //-V557
    bytes[10] = '2'; //-V557
    bytes[11] = '2'; //-V557
    bytes[17] = ' '; // Bibliographical level //-V557
    bytes[18] = 'i'; // Cataloging rules //-V557
    bytes[19] = ' '; // Related record //-V557
    bytes[20] = '4'; // Field length //-V557
    bytes[21] = '5'; // Field offset //-V557
    bytes[22] = '0'; //-V557

    // Конец справочника
    bytes[baseAddress - 1] = FieldDelimiter;

    // Проходим по полям
    for (int i = 0; i < record.fields.size(); i++) {
        const RecordField &field = record.fields[i];

        // Справочник
        encode(bytes, dictionaryPosition, 3, field.tag);
        encode(bytes, dictionaryPosition + 3, 4, fieldLength[i]); //-V112
        encode(bytes, dictionaryPosition + 7, 5, currentAddress - baseAddress);
        dictionaryPosition += 12;

        // Собственно поле
        if (field.tag < 10) {
            // В фиксированных полях не бывает подполей и индикаторов
            currentAddress = encode(bytes, currentAddress, field.value, encoding);
        } else {
            // Индискаторы
            bytes[currentAddress++] = ' ';
            bytes[currentAddress++] = ' ';

            // Значение поля
            currentAddress = encode(bytes, currentAddress, field.value, encoding);

            // Подполя
            for (int j = 0; j < field.subfields.size(); j++) {
                const SubField &subfield = field.subfields[j];
                bytes[currentAddress++] = SubFieldDelimiter;
                bytes[currentAddress++] = static_cast<char>(subfield.code.unicode());
                currentAddress = encode(bytes, currentAddress, subfield.value, encoding);
            }
        }

        // Ограничитель поля
        bytes[currentAddress++] = FieldDelimiter;
    }

    Q_ASSERT(currentAddress == recordLength - 1);

    // Конец записи
    bytes[recordLength - 1] = RecordDelimiter;

    // Собственно запись в поток
    device.write(bytes);
}
