// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::fastParse32;

//=========================================================

DatabaseInfo::DatabaseInfo()
    : logicallyDeletedRecords(), physicallyDeletedRecords(),
      nonActualizedRecords(), lockedRecords(),
      name(), description(), maxMfn(0),
      databaseLocked(false), readOnly(false) {
}

static QList<int> parseLine(const QString &line) {
    if (line.isEmpty()) {
        return QList<int>();
    }

    QList<int> result;
    QStringList items = line.split(IrbisText::ShortDelimiter);
    for (QString item : items) {
        qint32 mfn = fastParse32(item);
        result.append(mfn);
    }

    return result;
}

DatabaseInfo DatabaseInfo::parse(ServerResponse &response) {
    DatabaseInfo result;
    result.logicallyDeletedRecords = parseLine(response.readAnsi());
    result.physicallyDeletedRecords = parseLine(response.readAnsi());
    result.nonActualizedRecords = parseLine(response.readAnsi());
    result.lockedRecords = parseLine(response.readAnsi());
    result.maxMfn = fastParse32(response.readAnsi());
    result.databaseLocked = fastParse32(response.readAnsi()) != 0;

    return result;
}

QList<DatabaseInfo> DatabaseInfo::parse(MenuFile &menu) {
    QList<DatabaseInfo> result;
    for (MenuEntry entry: menu.entries) {
        QString name = entry.code;
        QString description = entry.comment;
        bool readOnly = false;
        if (name.startsWith("-")) {
            name = name.mid(1);
            readOnly = true;
        }

        DatabaseInfo info;
        info.name = name;
        info.description = description;
        info.readOnly = readOnly;
        result.append(info);
    }

    return result;
}

QString DatabaseInfo::toString() const {
    if (description.isEmpty()) {
        return name;
    }

    return name + " - " + description;
}
