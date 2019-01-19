// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

const QChar EmbeddedField::DefaultCode = '1';

QList<RecordField> EmbeddedField::getEmbeddedFields(const RecordField &field, QChar sign) {
    QList<RecordField> result;
    for (SubField *subField : field.subfields) {
        if (subField->code == sign) {
            QString value = subField->value;
            QString tagValue = value.mid(0, 3);
            int tag = fastParse32(tagValue);
            RecordField found(tag);
            if (tagValue.startsWith("00") && value.length() > 3) {
                found.value = value.mid(3);
            }
            result.append(found);
        } else {
            if (!result.isEmpty()) {
                RecordField &last = result.last();
                last.add(subField->code, subField->value);
            }
        }
    }

    return result;
}
