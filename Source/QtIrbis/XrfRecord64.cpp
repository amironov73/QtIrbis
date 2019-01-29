// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

const qint32 XrfRecord64::RecordSize = sizeof(qint64) + sizeof (qint32);

bool XrfRecord64::isDeleted() const {
    return (status & RecordStatus::Deleted) != 0;
}

bool XrfRecord64::isLocked() const {
    return (status & RecordStatus::Locked) != 0;
}

QString XrfRecord64::toString() const {
    return QString("MFN=%1, Offset=%2, Status=%3").arg(mfn).arg(offset).arg(status);
}
