#include "QtIrbis.h"

//=========================================================

RecordField::RecordField(qint32 tag) : value(), subfields() {
    this->tag = tag;
}

RecordField::RecordField(qint32 tag, QString value) : subfields() {
    this->tag = tag;
    this->value = value;
}

bool RecordField::isEmpty() const {
    return tag == 0 || (value.isEmpty() && subfields.isEmpty());
}

RecordField& RecordField::add(QChar code, const QString &value) {
    subfields.append(new SubField(code, value));

    return *this;
}

RecordField& RecordField::clear() {
    subfields.clear();

    return *this;
}

RecordField* RecordField::clone() const {
    RecordField *result = new RecordField(tag, value);
    foreach (const SubField *item, subfields) {
        result->subfields.append(item->clone());
    }

    return result;
}

SubField* RecordField::getFirstSubField(QChar code) const {
    foreach (SubField *item, subfields) {
        if (sameChar(item->code, code)) {
            return item;
        }
    }

    return nullptr;
}

QString RecordField::getFirstSubFieldValue(QChar code) const {
    foreach (SubField *item, subfields) {
        if (sameChar(item->code, code)) {
            return item->value;
        }
    }

    return QString();
}

QList<SubField*> RecordField::getSubField(QChar code) const {
    QList<SubField*> result;
    foreach (SubField *item, subfields) {
        if (sameChar(item->code, code)) {
            result.append(item);
        }
    }

    return result;
}

RecordField* RecordField::parse(const QString &line) {
    RecordField *result = new RecordField;
    TextNavigator navigator(line);
    result->tag = fastParse32(navigator.readTo('#'));
    result->value = navigator.readTo('^');
    while (!navigator.eot()) {
        QString chunk = navigator.readTo('^');
        QChar code = chunk[0];
        QString value = chunk.mid(1);
        result->add(code, value);
    }

    return result;
}

QString RecordField::toString() const {
    QString result = QString("%1%2").arg(tag).arg(value);
    foreach (const SubField *item, subfields) {
        result.append(item->toString());
    }

    return result;
}
