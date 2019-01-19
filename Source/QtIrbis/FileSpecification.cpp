// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

FileSpecification::FileSpecification(): binaryFile(false), path() {
}

FileSpecification::FileSpecification(int path, const QString &filename) : binaryFile(false), path(path), filename(filename) {
}

FileSpecification::FileSpecification(int path, const QString &database, const QString &filename) : binaryFile(false), path(path), database(database), filename(filename) {
}

static bool compareDatabases(const QString &first, const QString &second) {
    if (first.isEmpty() && second.isEmpty()) {
        return true;
    }

    return sameString(first, second);
}

FileSpecification FileSpecification::parse(const QString &text) {
    TextNavigator navigator(text);
    int path = fastParse32(navigator.readTo('.'));
    QString database = navigator.readTo('.');
    QString fileName = navigator.remainingText();
    bool binaryFile = fileName.startsWith('@');
    if (binaryFile)
    {
        fileName = fileName.mid(1);
    }

    QString content;
    int position = fileName.indexOf('&');
    if (position >= 0)
    {
        content = fileName.mid(position + 1);
        fileName = fileName.mid(0, position);
    }

    FileSpecification result;
    result.binaryFile = binaryFile;
    result.path = path;
    result.database = database;
    result.filename = fileName;
    result.content = content;

    return result;
}

QString FileSpecification::toString() const {
    QString result = filename;

    if (binaryFile) {
        result = "@" + result;
    } else {
        if (!content.isEmpty()) {
            result = "&" + result;
        }
    }

    switch (path) {
    case 0:
    case 1:
        result = QString("%1..").arg(path) + result;
        break;

    default:
        result = QString("%1.%2.").arg(path).arg(database) + result;
        break;
    }

    if (!content.isEmpty()) {
        QString copy(content);
        IrbisText::fromDosToIrbis(copy);
        result = result + "&" + copy;
    }

    return result;
}

bool FileSpecification::verify(bool throwException) const {
    bool result = !filename.isEmpty();

    if ((path != IrbisPath::System) && (path != IrbisPath::Data)) {
        result = result && !database.isEmpty();
    }

    if (!result && throwException) {
        throw IrbisException();
    }

    return result;
}

bool operator == (const FileSpecification &first, const FileSpecification &second) {
    return (first.path == second.path)
            && compareDatabases(first.database, second.database)
            && sameString(first.filename, second.filename);
}

bool operator != (const FileSpecification &first, const FileSpecification &second) {
    return !(first == second);
}


