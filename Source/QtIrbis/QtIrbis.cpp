// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

namespace irbis
{

bool sameChar(QChar first, QChar second) {
    return first.toUpper() == second.toUpper();
}

bool sameString(const QString &first, const QString &second) {
    return first.compare(second, Qt::CaseInsensitive) == 0;
}

qint32 fastParse32(const QString &text) {
    qint32 result = 0, length = text.length();
    for (qint32 offset = 0; offset < length; offset++) {
        result = result * 10 + text.at(offset).unicode() - '0';
    }

    return result;
}

qint32 fastParse32(const char *text) {
    qint32 result = 0;
    while (*text != 0) {
        result = result * 10 + *text - '0';
        text++;
    }

    return result;
}

qint32 fastParse32(const char *text, qint32 length) {
    qint32 result = 0;
    while (length > 0) {
        result = result * 10 + *text - '0';
        text++;
        length--;
    }

    return result;
}

qint64 fastParse64(const QString &text) {
    qint64 result = 0;
    qint32 length = text.length();
    for (qint32 offset = 0; offset < length; offset++) {
        result = result * 10 + text.at(offset).unicode() - '0';
    }

    return result;
}

QString fastToString(qint32 value) {
    char buffer[11];
    memset(buffer, 0, sizeof(buffer));
    qint32 offset = 9;
    if (value == 0) {
        buffer[offset--] = '0';
    }
    else {
        for (; value != 0; offset--) {
            qint32 remainder = value % 10;
            value = value / 10;
            buffer[offset] = static_cast<char>('0' + remainder);
        }
    }

    return QString(buffer + 9 - offset);
}

const QString& iif(const QString &s1, const QString &s2) {
    if (!s1.isEmpty()) {
        return s1;
    }

    return s2;
}

const QString& iif(const QString &s1, const QString &s2, const QString &s3) {
    if (!s1.isEmpty()) {
        return s1;
    }

    if (!s2.isEmpty()) {
        return s2;
    }

    return s3;
}

QString itemAt(const QStringList &list, qint32 index) {
    if ((index < 0) || (index >= list.size())) {
        return QString();
    }

    return list[index];
}

QStringList maxSplit(const QString &text, QChar separator, qint32 count) {
    QStringList result;

    qint32 position = 0, length = text.length();
    while ((count > 1) && (position < length)) {
        int index = text.indexOf(separator, position);
        if (index >= 0) {
            result.append(text.mid(position, index - position));
            position = index + 1;
        } else {
            result.append(text.mid(position));
            break;
        }
        count--;
    }

    if (position < length) {
        result.append(text.mid(position));
    }

    return result;
}

QStringList split(const QString &text, const QChar *separators) {
    QStringList result;

    qint32 position = 0, length = text.length();
    while (position < length) {
        for (qint32 index = position; index < length; index++) {
            QChar c = text[index];
            for (const QChar *ptr = separators; (*ptr).unicode(); ptr++) {
                if (*ptr == c) {
                    if (index != position) {
                        QString chunk = text.mid(position, index - position);
                        result.append(chunk);
                    }
                    position = index + 1;
                    goto nextIter;
                }
            }
        }
        nextIter:;
    }

    return result;
}

qint32 sign(qint64 val) {
    return val == 0 ? 0 : val < 0 ? -1 : 1;
}

QString toDebug(const QByteArray &array) {

    QString result;
    QChar c;

    for ( int i=0 ; i < array.size() ; i++ ){
        c = array[i];
        if (c >= 0x20 && c <= 126) {
            result.append(c);
        } else {
            result.append(QString("<%1>").arg(c.unicode(), 2, 16, QChar('0')));
        }
    }

    return result;
}

QString QTIRBIS_EXPORT readString(QDataStream &stream, qint32 required, QTextCodec *codec) {
    QByteArray array(required, 0);
    qint32 readed = stream.readRawData(array.data(), required);
    if (readed != required) {
        throw IrbisException();
    }
    qint32 length = array.indexOf('\0');
    if (length < 0) {
        length = required;
    }
    QString result = codec->toUnicode(array.data(), length);

    return result;
}

}

