// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::fastParse32;
using irbis::sameChar;

//=========================================================

RecordField::RecordField(qint32 tag, const QString &value) : tag(tag), value(value) {
}

RecordField::RecordField(const RecordField &other)
    : tag(other.tag), value(other.value), subfields() {
    for(auto sub : other.subfields) {
        SubField copy(sub.code, sub.value);
        subfields.append(copy);
    }
}

bool RecordField::isEmpty() const {
    return !tag || (value.isEmpty() && subfields.isEmpty());
}

RecordField& RecordField::add(QChar code, const QString &value) {
    subfields.append(SubField(code, value));

    return *this;
}

RecordField& RecordField::clear() {
    subfields.clear();

    return *this;
}

SubField* RecordField::getFirstSubField(QChar code) const {
    for(auto iter=subfields.begin(); iter != subfields.end(); ++iter) {
        if (sameChar(iter->code, code)) {
            return const_cast<SubField*>(&*iter);
        }
    }

    return nullptr;
}

QString RecordField::getFirstSubFieldValue(QChar code) const {
    for (auto item : subfields) {
        if (sameChar(item.code, code)) {
            return item.value;
        }
    }

    return QString();
}

QList<SubField> RecordField::getSubField(QChar code) const {
    QList<SubField> result;
    for (auto item : subfields) {
        if (sameChar(item.code, code)) {
            result.append(item);
        }
    }

    return result;
}

RecordField RecordField::parse(const QString &line) {
    RecordField result;
    TextNavigator navigator(line);
    result.tag = fastParse32(navigator.readTo('#'));
    result.value = navigator.readTo('^');
    while (!navigator.eot()) {
        QString chunk = navigator.readTo('^');
        QChar code = chunk[0];
        QString value = chunk.mid(1);
        result.add(code, value);
    }

    return result;
}

QString RecordField::toString() const {
    QString result = QString("%1#%2").arg(tag).arg(value);
    for (auto item : subfields) {
        result.append(item.toString());
    }

    return result;
}

bool RecordField::verify(bool throwOnError) const {
    bool result = tag > 0;

    if (result) {
        if (subfields.isEmpty()) {
            result = !value.isEmpty();
        }
        else {
            for (const auto &sub : subfields) {
                if (!sub.verify(throwOnError)) {
                    result = false;
                    break;
                }
            }
        }
    }

    if (!result && throwOnError) {
        throw IrbisException();
    }

    return result;
}

QTextStream& operator << (QTextStream &stream, const RecordField &field) {
    stream << field.tag << '#' << field.value;
    for (const auto &subField : field.subfields) {
        stream << subField;
    }

    return stream;
}

