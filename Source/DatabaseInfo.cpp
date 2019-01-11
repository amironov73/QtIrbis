#include "QtIrbis.h"

//=========================================================

DatabaseInfo::DatabaseInfo() : name(), description() {
}

DatabaseInfo DatabaseInfo::parse(ServerResponse &response) {
    DatabaseInfo result;

    // TODO implement

    return result;
}

QList<DatabaseInfo> DatabaseInfo::parse(MenuFile &menu) {
    QList<DatabaseInfo> result;

    // TODO implement

    return result;
}

