#include "QtIrbis.h"

//=========================================================

const QString ProtocolText::Delimiter = "\u001F\u001E";

void ProtocolText::encode(QTextStream &stream, const SubField &subField) {
    stream << Delimiter << subField.code << subField.value;
}

void ProtocolText::encode(QTextStream &stream, const RecordField &field) {
    stream << field.tag << "#" << field.value;
    for (const SubField *item : field.subfields) {
        encode(stream, *item);
    }
}

void ProtocolText::encode(QTextStream &stream, const MarcRecord &record) {
    stream << record.mfn << "#" << record.status << Delimiter;
    stream << 0 << "#" << record.version << Delimiter;
    for (const RecordField *item : record.fields) {
        encode(stream, *item);
        stream << Delimiter;
    }
}

QString ProtocolText::encode(const MarcRecord &record) {
    QString result;
    QTextStream stream (&result);
    encode(stream, record);
    return result;
}
