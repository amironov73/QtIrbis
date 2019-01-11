#include "QtIrbis.h"

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
        int length = lines.size();
        if (length != 0) {
            process.number = lines[0];
        }

        if (length > 1) {
            process.ipAddress = lines[1];
        }

        if (length > 2) {
            process.name = lines[2];
        }

        if (length > 3) {
            process.clientId = lines[3];
        }

        if (length > 4) {
            process.workstation = lines[4];
        }

        if (length > 5) {
            process.started = lines[5];
        }

        if (length > 6) {
            process.lastCommand = lines[6];
        }

        if (length > 7) {
            process.commandNumber = lines[7];
        }

        if (length > 8) {
            process.processId = lines[8];
        }

        if (length > 9) {
            process.state = lines[9];
        }

        result.append(process);
    }

    return result;
}
