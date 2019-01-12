#include "QtIrbis.h"

//=========================================================

FileSpecification::FileSpecification(int path, const QString &filename) : database(), content() {
    this->path = path;
    this->filename = filename;
}

FileSpecification::FileSpecification(int path, const QString &database, const QString &filename) : content() {
    this->path = path;
    this->database = database;
    this->filename = filename;
}

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

