// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::fastParse64;
using irbis::sign;

//=========================================================

NumberChunk::NumberChunk() : prefix(), value(0), length(0), haveValue(false) {
}

qint32 NumberChunk::compareTo(const NumberChunk &other) const {
    qint32 result = prefix.compare(other.prefix);
    if (result == 0)
    {
        result = haveValue && other.haveValue
            ? sign(value - other.value)
            : static_cast<qint32>(haveValue) - static_cast<qint32>(other.haveValue);
    }

    return result;
}

bool NumberChunk::havePrefix() const {
    return !prefix.isEmpty();
}

bool NumberChunk::setUp(const QString &str, const QString &number) {
    bool result = false;

    if (!str.isEmpty())
    {
        result = true;
        prefix = str;
    }

    if (!number.isEmpty())
    {
        result = true;
        haveValue = true;
        length = number.length();
        value = fastParse64(number);
    }

    return result;

}

QString NumberChunk::toString() const {
    QString result = prefix;

    if (haveValue) {
        if (length > 0) {
            result += QString("%1").arg(value, 5, 10, QChar('0'));
        } else {
            result += QString::number(value);
        }
    }

    return result;
}

