#include "QtIrbis.h"

//=========================================================

const QString MenuFile::StopMarker = "*****";

MenuFile::MenuFile() : fileName(), entries() {
}

MenuFile& MenuFile::add(QString &code, QString &comment) {
    MenuEntry *entry = new MenuEntry(code, comment);
    entries.append(entry);

    return *this;
}

MenuEntry* MenuFile::getEntry(QString &code) {
    for (MenuEntry *entry : entries) {
        if (sameString(entry->code, code)) {
            return entry;
        }
    }

    QString trimmed = code.trimmed();
    for (MenuEntry *entry : entries) {
        if (sameString(entry->code, trimmed)) {
            return entry;
        }
    }

    // TODO implement trimCode()

    return nullptr;
}

QString* MenuFile::getValue(QString &code) {
    MenuEntry *entry = getEntry(code);
    QString *result = entry ? &entry->comment : nullptr;

    return result;
}

QString& MenuFile::getValue(QString &code, QString &defaultValue) {
    QString *value = getValue(code);

    return value ? *value : defaultValue;
}

MenuFile MenuFile::parse(QTextStream &stream) {
    MenuFile result;
    // TODO implement

    return result;
}

