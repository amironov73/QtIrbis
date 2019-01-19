// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

IrbisDate::IrbisDate(const QString &text) : text(text) {
    this->date = convert(text);
}

IrbisDate::IrbisDate(QDateTime date) : date(date) {
    this->text = convert(date);
}

QDateTime IrbisDate::convert(const QString &text) {
    return QDateTime::fromString(text, "yyyyMMdd");
}

QString IrbisDate::convert(const QDateTime &date) {
    return date.toString("yyyyMMdd");
}

QString IrbisDate::convert(const QDate &date) {
    return date.toString("yyyyMMdd");
}

IrbisDate* IrbisDate::safeParse(const QString &text) {
    if (text.isEmpty()) {
        return nullptr;
    }

    return new IrbisDate(text);
}

QString IrbisDate::today() {
    return QDate::currentDate().toString("yyyyMMdd");
}
