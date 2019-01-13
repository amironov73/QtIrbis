#include "QtIrbis.h"

//=========================================================

const QString MenuFile::StopMarker = "*****";
const QChar MenuFile::Separators[] = { ' ', '-', '=', ':', 0 };

MenuFile::MenuFile() : fileName(), entries() {
}

MenuFile& MenuFile::add(const QString &code, const QString &comment) {
    MenuEntry entry(code, comment);
    entries.append(entry);

    return *this;
}

static QString trimCode(const QString &code) {
    QString result = code;
    QStringList parts = split(result, MenuFile::Separators);
    if (!parts.isEmpty()) {
        result = parts[0].trimmed();
    }

    return result;
}

MenuEntry* MenuFile::getEntry(const QString &code) const {
    for(auto i = entries.begin(); i != entries.end(); i++) {
        if (sameString(i->code, code)) {
            return const_cast<MenuEntry*>(&*i);
        }
    }

    QString trimmed = code.trimmed();
    for(auto i = entries.begin(); i != entries.end(); i++) {
        if (sameString(i->code, trimmed)) {
            return const_cast<MenuEntry*>(&*i);
        }
    }

    trimmed = trimCode(trimmed);
    for(auto i = entries.begin(); i != entries.end(); i++) {
        if (sameString(i->code, trimmed)) {
            return const_cast<MenuEntry*>(&*i);
        }
    }

    return nullptr;
}

MenuEntry* MenuFile::getEntrySensitive(const QString &code) const {
    for(auto i = entries.begin(); i != entries.end(); i++) {
        if (i->code == code) {
            return const_cast<MenuEntry*>(&*i);
        }
    }

    QString trimmed = code.trimmed();
    for(auto i = entries.begin(); i != entries.end(); i++) {
        if (i->code == trimmed) {
            return const_cast<MenuEntry*>(&*i);
        }
    }

    trimmed = trimCode(trimmed);
    for(auto i = entries.begin(); i != entries.end(); i++) {
        if (i->code == trimmed) {
            return const_cast<MenuEntry*>(&*i);
        }
    }

    return nullptr;
}

QString* MenuFile::getValue(const QString &code) const {
    MenuEntry *entry = getEntry(code);
    QString *result = entry ? &entry->comment : nullptr;

    return result;
}

QString* MenuFile::getValueSensitive(const QString &code) const {
    MenuEntry *entry = getEntrySensitive(code);
    QString *result = entry ? &entry->comment : nullptr;

    return result;
}

const QString& MenuFile::getValue(const QString &code, const QString &defaultValue) const {
    QString *value = getValue(code);

    return value ? *value : defaultValue;
}

const QString& MenuFile::getValueSensitive(const QString &code, const QString &defaultValue) const {
    QString *value = getValueSensitive(code);

    return value ? *value : defaultValue;
}

MenuFile MenuFile::parse(QTextStream &stream) {
    MenuFile result;
    while (true)
    {
        QString code = stream.readLine();
        if (code.isEmpty())
        {
            break;
        }

        if (code.startsWith(StopMarker))
        {
            break;
        }

        QString comment = stream.readLine();
        result.add(code, comment);
    }

    return result;
}

MenuFile MenuFile::parseLocalFile(const QString &filename, const QTextCodec *encoding) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw IrbisException();
    }

    QTextStream stream(&file);
    stream.setCodec(const_cast<QTextCodec*>(encoding));

    return parse(stream);
}

