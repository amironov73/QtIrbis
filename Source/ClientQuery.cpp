#include "QtIrbis.h"

//=========================================================

ClientQuery::ClientQuery(IrbisConnection *connection, QString commandCode)
    : buffer() {
    this->connection = connection;
    buffer.open(QIODevice::WriteOnly);
    addAnsi(commandCode);
    addAnsi(QString("%1").arg(connection->workstation));
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
    buffer.write(IrbisEncoding::ansi()->fromUnicode(text));
    return addLineFeed();
}

ClientQuery& ClientQuery::addLineFeed() {
    char data[] = { '\x0A' };
    buffer.write(data, 1);

    return *this;
}

ClientQuery& ClientQuery::addUtf(QString text) {
    buffer.write(IrbisEncoding::utf()->fromUnicode(text));
    return addLineFeed();
}

QByteArray& ClientQuery::encode() {
    return buffer.buffer();
}


