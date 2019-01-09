#include "QtIrbis.h"

//=========================================================

ClientQuery::ClientQuery(IrbisConnection *connection, QString commandCode)
    : buffer() {
    this->connection = connection;
    addAnsi(commandCode);
    addAnsi(QString("%c").arg(connection->workstation));
    addAnsi(commandCode);
    add(connection->clientId);
    connection->queryId++;
    add(connection->queryId);
    addAnsi(connection->password);
    addAnsi(connection->username);
    addLineFeed();
    addLineFeed();
    addLineFeed();
}

ClientQuery& ClientQuery::add(int value) {
    return addAnsi(QString("%1").arg(value));
}

ClientQuery& ClientQuery::addAnsi(QString text) {
    // TODO implement
    return addLineFeed();
}

ClientQuery& ClientQuery::addLineFeed() {
    char data[] = { '\x0A' };
    buffer.write(data, 1);

    return *this;
}

ClientQuery& ClientQuery::addUtf(QString text) {
    // TODO implement
    return addLineFeed();
}

char* ClientQuery::encode() {
    // TODO implement
    return nullptr;
}


