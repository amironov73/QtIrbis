// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

static const int LengthOfLength = 5;

MarcRecord* Iso2709::readRecord(QIODevice &device, QTextCodec &encoding) {
    MarcRecord *result = nullptr;

    // Считываем длину записи
    char marker[LengthOfLength];
    if (device.read(marker, LengthOfLength) != LengthOfLength) {
        return nullptr;
    }

    // а затем и ее остаток
    unsigned int recordLength = static_cast<unsigned int>(fastParse32(marker, 5));
    char *record = new char[recordLength];
    int need = static_cast<int>(recordLength - LengthOfLength);
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

    int indicatorLength = fastParse32(record + 10, 1); // как правило, 2
    int baseAddress = fastParse32(record + 12, 5);

    result = new MarcRecord;

    // Пошли по полям при помощи справочника
    for (int directory = MarkerLength;; directory += 12) {
        // Переходим к очередному полю.
        // Если нарвались на разделитель, значит, справочник закончился
        if (record[directory] == FieldDelimiter) {
            break;
        }

        int tag = fastParse32(record + directory, 3);
        int fieldLength = fastParse32(record + directory + 3, 4); //-V112
        int fieldOffset = baseAddress + fastParse32(record + directory + 7, 5);
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
            int start = fieldOffset + indicatorLength;
            int stop = fieldOffset + fieldLength - indicatorLength + 1;
            int position = start;

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

    if (record) { //-V668
        delete []record;
    }

    return result;
}

static void encode(char *bytes, int pos, int len, int val) {
    len--;
    for (pos += len; len >= 0; len--) {
        bytes[pos] = static_cast<char>(val % 10 + '0');
        val /= 10;
        pos--;
    }
}

static int encode(char *bytes, int pos, QString str, QTextCodec &encoding) {
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
    int recordLength = MarkerLength;
    int dictionaryLength = 1; // с учетом ограничителя справочника
    int *fieldLength = new int[static_cast<unsigned int>(record.fields.size())]; // Длины полей

    // Сначала подсчитываем общую длину
    for (int i = 0; i < record.fields.size(); i++) {
        dictionaryLength += 12; // одна статья справочника
        const RecordField &field = record.fields[i];

        if ((field.tag <= 0) || (field.tag >= 1000)) {
            delete []fieldLength;
            throw IrbisException();
        }

        int fldlen = 0;
        if (field.tag < 10) {
            // В фиксированном поле не бывает подполей и индикаторов
            fldlen += countBytes(field.value, encoding);
        } else {
            fldlen += 2; // индиакторы
            fldlen += countBytes(field.value, encoding);
            for (int j = 0; j < field.subfields.size(); j++) {
                const SubField &subfield = field.subfields[j];

                if ((subfield.code) <= ' ' || (subfield.code >= 127)) {
                    delete []fieldLength;
                    throw IrbisException();
                }

                fldlen += 2; // признак подполя и его код
                fldlen += countBytes(subfield.value, encoding);
            }
        }

        fldlen++; // разделитель полей

        if (fldlen >= 10000) {
            delete []fieldLength;
            throw IrbisException();
        }

        fieldLength[i] = fldlen;
        recordLength += fldlen;
    }

    recordLength += dictionaryLength; // справочник
    recordLength++; // разделитель записей

    if (recordLength >= 100000) {
        delete []fieldLength;
        throw IrbisException();
    }

    // Приступаем к кодированию
    int dictionaryPosition = MarkerLength;
    int baseAddress = MarkerLength + dictionaryLength;
    int currentAddress = baseAddress;
    char *bytes = new char[static_cast<unsigned int>(recordLength)]; // Закодированная запись

    // Маркер записи
    memset(bytes, ' ', static_cast<unsigned int>(recordLength));
    encode(bytes, 0, 5, recordLength);
    encode(bytes, 12, 5, baseAddress);
    bytes[5] = 'n';  // Record status
    bytes[6] = 'a';  // Record type
    bytes[7] = 'm';  // Bibligraphical index
    bytes[8] = '2';
    bytes[10] = '2';
    bytes[11] = '2';
    bytes[17] = ' '; // Bibliographical level
    bytes[18] = 'i'; // Cataloging rules
    bytes[19] = ' '; // Related record
    bytes[20] = '4'; // Field length
    bytes[21] = '5'; // Field offset
    bytes[22] = '0';

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

    // assert currentAddress == recordLength - 1;

    // Конец записи
    bytes[recordLength - 1] = RecordDelimiter;

    // Собственно запись в поток
    device.write(bytes, recordLength);
    delete []bytes;
    delete []fieldLength;
}
