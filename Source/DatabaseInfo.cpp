#include "QtIrbis.h"

//=========================================================

DatabaseInfo::DatabaseInfo()
    : name(), description(), maxMfn(0), logicallyDeletedRecords(),
    physicallyDeletedRecords(), nonActualizedRecords(), lockedRecords(),
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

    // TODO implement

    return result;
}

QString DatabaseInfo::toString() const {
    if (description.isEmpty()) {
        return name;
    }

    return name + " - " + description;
}
