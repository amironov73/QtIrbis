#include "QtIrbis.h"

//=========================================================

SubField::SubField(QChar code)  : value() {
    this->code = code;
}

SubField::SubField(QChar code, QString value) {
    this->code = code;
    this->value = value;
}

bool SubField::isEmpty() const {
    return code.isNull() || value.isEmpty();
}

SubField* SubField::clone() const {
    return new SubField(code, value);
}

QString SubField::toString() const {
    return QString("^%1%2").arg(code).arg(value);
}
