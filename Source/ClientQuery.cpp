#include "QtIrbis.h"

//=========================================================

ClientQuery::ClientQuery(IrbisConnection *connection, const QString &commandCode)
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

ClientQuery& ClientQuery::add(const FileSpecification &specification) {
    QString text = specification.toString();
    return addAnsi(text);
}

ClientQuery& ClientQuery::add(const MarcRecord &record) {
    QString text = record.toString();
    return addUtf(text);
}

ClientQuery& ClientQuery::add(const RawRecord &record) {
    QString text = record.toString();
    return addUtf(text);
}

ClientQuery& ClientQuery::addAnsi(const QString &text) {
    buffer.write(IrbisEncoding::ansi()->fromUnicode(text));
    return addLineFeed();
}

ClientQuery& ClientQuery::addAnsiNoLf(const QString &text) {
    buffer.write(IrbisEncoding::ansi()->fromUnicode(text));
    return *this;
}

ClientQuery& ClientQuery::addLineFeed() {
    char data[] = { '\x0A' };
    buffer.write(data, 1);

    return *this;
}

ClientQuery& ClientQuery::addUtf(const QString &text) {
    buffer.write(IrbisEncoding::utf()->fromUnicode(text));
    return addLineFeed();
}

QByteArray ClientQuery::encode() {
    QString prefixString = QString::number(buffer.size());
    QByteArray prefixArray = IrbisEncoding::ansi()->fromUnicode(prefixString);
    char data[] = { '\x0A' };
    prefixArray.append(data, 1);
    QByteArray result = buffer.buffer();
    result.prepend(prefixArray);

    return result;
}


