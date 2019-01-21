// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::itemAt;

//=========================================================

ServerStat::ServerStat() : runningClients(), clientCount(0),
    totalCommandCount(0) {
}

ServerStat ServerStat::parse(ServerResponse &response) {
    ServerStat result;
    result.totalCommandCount = response.readInt32();
    result.clientCount = response.readInt32();
    int linesPerClient = response.readInt32();
    if (linesPerClient == 0) {
        return result;
    }

    QList<ClientInfo> clients;
    for (int i = 0; i < result.clientCount; i++) {
        QStringList lines = response.readAnsi(linesPerClient + 1);
        if (lines.isEmpty()) {
            break;
        }

        ClientInfo client;
        client.number = itemAt(lines, 0);
        client.ipAddress = itemAt(lines, 1);
        client.port = itemAt(lines, 2);
        client.name = itemAt(lines, 3);
        client.id = itemAt(lines, 4); //-V112
        client.workstation = itemAt(lines, 5);
        client.registered = itemAt(lines, 6);
        client.acknowledged = itemAt(lines, 7);
        client.lastCommand = itemAt(lines, 8);
        client.commandNumber = itemAt(lines, 9);

        clients.append(client);
    }
    result.runningClients = clients;

    return result;
}
