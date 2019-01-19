// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

IrbisVersion::IrbisVersion()
    : organization(), version(), maxClients(0), connectedClients() {
}

// разбор ответа сервера
IrbisVersion IrbisVersion::parse (ServerResponse &response) {
    QStringList lines = response.readRemainingAnsiLines();
    IrbisVersion result;
    if (lines.length() == 3) {
        result.version = lines[0];
        result.connectedClients = fastParse32(lines[1]);
        result.maxClients = fastParse32(lines[2]);
    } else {
        result.organization = lines[0];
        result.version = lines[1];
        result.connectedClients = fastParse32(lines[2]);
        result.maxClients = fastParse32(lines[3]);
    }

    return result;
}

QString IrbisVersion::toString() const {
    return QString("organization=") + organization +
        ", version=" + version +
        ", maxClients=" + QString::number(maxClients) +
        ", connectedClients=" + QString::number(connectedClients);
}
