// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::read64bit;
using irbis::write64bit;

//=========================================================

const qint32 MstControlRecord64::RecordSize = 36;
const qint64 MstControlRecord64::LockFlagPosition = 32;

QDataStream& operator >> (QDataStream &stream, MstControlRecord64 &record) {
    stream >> record.ctlMfn >> record.nextMfn;
    record.nextPosition = read64bit(stream);
    stream >> record.mftType >> record.recCnt >> record.reserv1 >> record.reserv2 >> record.blocked;

    return stream;
}

QDataStream& operator << (QDataStream &stream, const MstControlRecord64 &record) {
    stream << record.ctlMfn << record.nextMfn;
    write64bit(stream, record.nextPosition);
    stream << record.mftType << record.recCnt << record.reserv1 << record.reserv2 << record.blocked;

    return stream;
}
