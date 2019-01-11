#include "QtIrbis.h"

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
        int length = lines.size();
        if (length != 0) {
            client.number = lines[0];
        }

        if (length > 1) {
            client.ipAddress = lines[1];
        }

        if (length > 2) {
            client.port = lines[2];
        }

        if (length > 3) {
            client.name = lines[3];
        }

        if (length > 4) {
            client.id = lines[4];
        }

        if (length > 5) {
            client.workstation = lines[5];
        }

        if (length > 6) {
            client.registered = lines[6];
        }

        if (length > 7) {
            client.acknowledged = lines[7];
        }

        if (length > 8) {
            client.lastCommand = lines[8];
        }

        if (length > 9) {
            client.commandNumber = lines[9];
        }

        clients.append(client);
    }
    result.runningClients = clients;

    return result;
}
