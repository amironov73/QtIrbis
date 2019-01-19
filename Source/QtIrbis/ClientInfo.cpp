// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "QtIrbis.h"

//=========================================================

ClientInfo::ClientInfo()
    : number(), ipAddress(), port(), name(), id(), workstation(),
    registered(), acknowledged(), lastCommand(), commandNumber() {
}

QString ClientInfo::toString() const {
    return QString("number=") + number +
    ", ipAddress=" + ipAddress +
    ", port=" + port +
    ", name=" + name +
    ", id=" + id +
    ", workstation=" + workstation +
    ", registered=" + registered +
    ", acknowledged=" + acknowledged +
    ", lastCommand=" + lastCommand +
    ", commandNumber=" + commandNumber;
}
