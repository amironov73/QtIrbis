// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::read64bit;

//=========================================================

const qint32 MstRecordLeader64::LeaderSize = 32;

QDataStream& operator >> (QDataStream& stream, MstRecordLeader64 &leader) {
    stream >> leader.mfn >> leader.length;
    leader.previous = read64bit(stream);
    stream >> leader.base >> leader.nvf >> leader.version >> leader.status;

    return stream;
}
