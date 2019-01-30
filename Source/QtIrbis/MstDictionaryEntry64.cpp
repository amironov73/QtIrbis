// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

const qint32 MstDictionaryEntry64::EntrySize = 12;

QDataStream& operator >> (QDataStream &stream, MstDictionaryEntry64 &entry) {
    stream >> entry.tag >> entry.position >> entry.length;

    return stream;
}

QDataStream& operator << (QDataStream &stream, const MstDictionaryEntry64 &entry) {
    stream << entry.tag << entry.position << entry.length;

    return stream;
}

