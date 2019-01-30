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
