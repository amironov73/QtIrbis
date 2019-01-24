// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

SubField::SubField(QChar code, QString value) : code(code), value(value) {
}

SubField::SubField(const SubField &other) : code(other.code), value(other.value) {
}

bool SubField::isEmpty() const {
    return code.isNull() || value.isEmpty();
}

QString SubField::toString() const {
    return QString("^%1%2").arg(code).arg(value);
}

bool SubField::verify(bool throwOnError) const {
    bool result = !code.isNull() && !value.isEmpty();
    if (!result && throwOnError) {
        throw IrbisException();
    }

    return result;
}

std::ostream& operator << (std::ostream &stream, const SubField &subField) {
    stream << '^' << subField.code.toLatin1() << subField.value.toStdString();

    return stream;
}

std::wostream& operator << (std::wostream &stream, const SubField &subField) {
    stream << L'^' << subField.code.toLatin1() << subField.value.toStdWString();

    return stream;
}
