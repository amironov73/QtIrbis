#include "QtIrbis.h"

//=========================================================

ClientQuery::ClientQuery(IrbisConnection *connection, QString commandCode)
    : buffer() {
    this->connection = connection;
    buffer.open(QIODevice::WriteOnly);
    addAnsi(commandCode);
    QString workstation = QString("%1").arg(connection->workstation);
    addAnsi(workstation);
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
    QString text = fastToString(value);
    return addAnsi(text);
}

ClientQuery& ClientQuery::add(FileSpecification &specification) {
    QString text = specification.toString();
    return addAnsi(text);
}

ClientQuery& ClientQuery::add(MarcRecord &record) {
    QString text = record.toString();
    return addUtf(text);
}

ClientQuery& ClientQuery::add(RawRecord &record) {
    QString text = record.toString();
    return addUtf(text);
}

ClientQuery& ClientQuery::addAnsi(QString &text) {
    buffer.write(IrbisEncoding::ansi()->fromUnicode(text));
    return addLineFeed();
}

ClientQuery& ClientQuery::addAnsiNoLf(QString &text) {
    buffer.write(IrbisEncoding::ansi()->fromUnicode(text));
    return *this;
}

ClientQuery& ClientQuery::addLineFeed() {
    char data[] = { '\x0A' };
    buffer.write(data, 1);

    return *this;
}

ClientQuery& ClientQuery::addUtf(QString &text) {
    buffer.write(IrbisEncoding::utf()->fromUnicode(text));
    return addLineFeed();
}

QByteArray ClientQuery::encode() {
    qint64 length = buffer.size();
    QString prefixString = QString("%1\n").arg(length);
    QByteArray prefixArray = IrbisEncoding::ansi()->fromUnicode(prefixString);
    QByteArray result = buffer.buffer();
    result.prepend(prefixArray);

    return result;
}


