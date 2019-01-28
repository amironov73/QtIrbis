// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

RecordSerializer::RecordSerializer(QDataStream &stream)
    : stream(stream) {
}

MarcRecord RecordSerializer::deserialize() {
    MarcRecord result;
    qint16 fieldCount;
    stream >> fieldCount;
    result.fields.reserve(fieldCount);
    for (qint16 i = 0; i < fieldCount; ++i) {
        qint32 tag;
        QString value;
        stream >> tag >> value;
        result.add(tag, value);
        RecordField &field = result.fields.last();
        qint16 subfieldCount;
        stream >> subfieldCount;
        for (qint16 j = 0; j < subfieldCount; ++j) {
            QChar code;
            stream >> code >> value;
            field.add(code, value);
        }
    }

    return result;
}

void RecordSerializer::serialize(const MarcRecord &record) {
    qint16 fieldCount = static_cast<qint16> (record.fields.size());
    stream << fieldCount;
    for (const RecordField &field : record.fields) {
        stream << field.tag << field.value;
        qint16 subfieldCount = static_cast<qint16>(field.subfields.size());
        stream << subfieldCount;
        for (const SubField &subfield : field.subfields) {
            stream << subfield.code << subfield.value;
        }
    }
}

