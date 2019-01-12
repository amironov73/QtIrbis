#include "QtIrbis.h"

//=========================================================

bool sameChar(QChar first, QChar second) {
    return first.toUpper() == second.toUpper();
}

bool sameString(const QString &first, const QString &second) {
    return first.compare(second, Qt::CaseInsensitive) == 0;
}

qint32 fastParse32(const QString &text) {
    qint32 result = 0, length = text.length();
    for (int offset = 0; offset < length; offset++) {
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

QString& iif(QString &s1, QString &s2) {
    if (!s1.isEmpty()) {
        return s1;
    }

    return s2;
}

QString& iif(QString &s1, QString &s2, QString &s3) {
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
        count++;
    }

    if (position < length) {
        result.append(text.mid(position));
    }

    return result;
}
