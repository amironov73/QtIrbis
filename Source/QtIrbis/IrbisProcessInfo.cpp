// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::itemAt;

//=========================================================

IrbisProcessInfo::IrbisProcessInfo()
    : number(), ipAddress(), name(), clientId(), workstation(),
    started(), lastCommand(), commandNumber(), processId(), state() {
}

QList<IrbisProcessInfo> IrbisProcessInfo::parse(ServerResponse &response) {
    QList<IrbisProcessInfo> result;
    int processCount = response.readInt32();
    int linesPerProcess = response.readInt32();
    if (processCount == 0 || linesPerProcess == 0) {
        return result;
    }

    for (int i = 0; i < processCount; i++) {
        QStringList lines = response.readAnsi(linesPerProcess + 1);
        if (lines.isEmpty()) {
            break;
        }

        IrbisProcessInfo process;
        process.number = itemAt(lines, 0);
        process.ipAddress = itemAt(lines, 1);
        process.name = itemAt(lines, 2);
        process.clientId = itemAt(lines, 3);
        process.workstation = itemAt(lines, 4); //-V112
        process.started = itemAt(lines, 5);
        process.lastCommand = itemAt(lines, 6);
        process.commandNumber = itemAt(lines, 7);
        process.processId = itemAt(lines, 8);
        process.state = itemAt(lines, 9);

        result.append(process);
    }

    return result;
}
