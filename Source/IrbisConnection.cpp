#include "QtIrbis.h"

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

