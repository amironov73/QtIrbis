#include "QtIrbis.h"

//=========================================================

SubField::SubField(char code)  : value() {
    this->code = code;
}

SubField::SubField(char code, QString value) {
    this->code = code;
    this->value = value;
}

bool SubField::isEmpty() const {
    return code == '\0' || value.isEmpty();
}

SubField* SubField::clone() const {
    return new SubField(code, value);
}

QString SubField::toString() const {
    return QString("^%1%2").arg(code).arg(value);
}

//=========================================================

RecordField::RecordField(int tag) : value(), subfields() {
    this->tag = tag;
}

RecordField::RecordField(int tag, QString value) : subfields() {
    this->tag = tag;
    this->value = value;
}

bool RecordField::isEmpty() const {
    return tag == 0 || (value.isEmpty() && subfields.isEmpty());
}

RecordField* RecordField::clone() const {
    RecordField *result = new RecordField(tag, value);
    foreach (const SubField *item, subfields) {
        result->subfields.append(item->clone());
    }

    return result;
}

QString RecordField::toString() const {
    QString result = QString("%1%2").arg(tag).arg(value);
    foreach (const SubField *item, subfields) {
        result.append(item->toString());
    }

    return result;
}

//=========================================================

MarcRecord* MarcRecord::clone() const {
    MarcRecord *result = new MarcRecord();
    result->mfn = mfn;
    foreach(const RecordField *item, fields) {
        result->fields.append(item->clone());
    }

    return result;
}

QString MarcRecord::toString() const {
    QString result;
    bool first = true;
    foreach (const RecordField *item, fields) {
        if (first) {
            result = item->toString();
            first = false;
        }
        else {
            result = result + "\n" + item->toString();
        }
    }

    return result;
}

//=========================================================

FileSpecification::FileSpecification(int path, QString database, QString filename) : content() {
    this->path = path;
    this->database = database;
    this->filename = filename;
}

//=========================================================

QString FileSpecification::toString() const {
    QString result = filename;

    switch (path) {
    case 0:
    case 1:
        result = QString("%1..").arg(path) + result;
        break;

    default:
        result = QString("%1.%2.").arg(path).arg(database) + result;
        break;
    }

    return result;
}

//=========================================================

IrbisConnection::IrbisConnection() :host("localhost"), port(6666),
    username(), password(), database("IBIS"), workstation('C'),
    clientId(0), queryId(0) {
}

void IrbisConnection::actualizeRecord(QString database, int mfn) {
    // TODO implement
}

void IrbisConnection::connect() {
    // TODO implement
}

void IrbisConnection::createDatabase(QString databaseName, QString description, bool readerAccess) {
    // TODO implement
}

void IrbisConnection::createDictionary(QString databaseName) {
    // TODO implement
}

void IrbisConnection::deleteDatabase(QString databaseName) {
    // TODO implement
}

void IrbisConnection::deleteRecord(int mfn) {
    // TODO implement
}

void IrbisConnection::disconnect() {
    // TODO implement
}

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
    return NULL;
}

//=========================================================

ServerResponse::ServerResponse() {
    // TODO implement
}

void ServerResponse::close() {
    // TODO implement
}

//=========================================================
