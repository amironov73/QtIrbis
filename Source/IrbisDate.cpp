#include "QtIrbis.h"

//=========================================================

IrbisDate::IrbisDate(const QString &text) {
    this->text = text;
    this->date = convert(text);
}

IrbisDate::IrbisDate(QDateTime date) {
    this->date = date;
    this->text = convert(date);
}

QDateTime IrbisDate::convert(const QString &text) {
    return QDateTime::fromString(text, "yyyyMMdd");
}

QString IrbisDate::convert(QDateTime date) {
    return date.toString("yyyyMMdd");
}

QString IrbisDate::convert(QDate date) {
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
