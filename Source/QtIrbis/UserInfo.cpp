// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::itemAt;
using irbis::sameString;

//=========================================================

UserInfo::UserInfo()
    : number(), name(), password(), cataloger(), reader(),
    circulation(), acquisitions(), provision(), administrator() {
}

static QString formatPair(QString prefix, const QString &value, QString defaultValue) {
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
        user.number = itemAt(lines, 0);
        user.name = itemAt(lines, 1);
        user.password = itemAt(lines, 2);
        user.cataloger = itemAt(lines, 3);
        user.reader = itemAt(lines, 4); //-V112
        user.circulation = itemAt(lines, 5);
        user.acquisitions = itemAt(lines, 6);
        user.provision = itemAt(lines, 7);
        user.administrator = itemAt(lines, 8);

        result.append(user);
    }

    return result;
}

