#include "QtIrbis.h"

//=========================================================

UserInfo::UserInfo()
    : number(), name(), password(), cataloger(), reader(),
    circulation(), acquisitions(), provision(), administrator() {
}

QString UserInfo::formatPair(QString prefix, QString &value, QString defaultValue) {
    if (sameString(value, defaultValue)) {
        return "";
    }

    return prefix + "=" + value + ";";
}

QString UserInfo::encode() {
    return name + "\r\n"
            + password + "\r\n"
            + formatPair("C", cataloger,     "irbisc.ini")
            + formatPair("R", reader,        "irbisr.ini")
            + formatPair("B", circulation,   "irbisb.ini")
            + formatPair("M", acquisitions,  "irbism.ini")
            + formatPair("K", provision,     "irbisk.ini")
            + formatPair("A", administrator, "irbisa.ini");
}

QList<UserInfo> UserInfo::parse (ServerResponse &response) {
    QList<UserInfo> result;

    int userCount = response.readInt32();
    int linesPerUser = response.readInt32();
    if (userCount == 0 || linesPerUser == 0) {
        return result;
    }

    for (int i = 0; i < userCount; i++) {
        QStringList lines = response.readAnsi(linesPerUser + 1);
        if (lines.isEmpty()) {
            break;
        }

        UserInfo user;
        qint32 length = lines.length();
        if (length != 0) {
            user.number = lines[0];
        }

        if (length > 1) {
            user.name = lines[1];
        }

        if (length > 2) {
            user.password = lines[2];
        }

        if (length > 3) {
            user.cataloger = lines[3];
        }

        if (length > 4) {
            user.reader = lines[4];
        }

        if (length > 5) {
            user.circulation = lines[5];
        }

        if (length > 6) {
            user.acquisitions = lines[6];
        }

        if (length > 7) {
            user.provision = lines[7];
        }

        if (length > 8) {
            user.administrator = lines[8];
        }

        result.append(user);
    }

    return result;
}

