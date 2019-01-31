// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

MstRecord64::MstRecord64()
    : leader(), offset(0), dictionary() {
}

bool MstRecord64::isDeleted() const {
    return (leader.status & RecordStatus::Deleted) != 0;
}

MarcRecord MstRecord64::toMarcRecord() const {
    MarcRecord result;
    result.status = 0; // TODO obtain the status
    result.version = 0; // TODO obtain the version
    result.fields.reserve(dictionary.size());
    for (const MstDictionaryEntry64 &entry : dictionary) {
        RecordField field(entry.tag);
        // field.parse(entry.text); // TODO parse the field
        result.fields.append(field);
    }

    return result;
}

