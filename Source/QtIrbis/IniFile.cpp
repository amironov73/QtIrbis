// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::itemAt;
using irbis::maxSplit;
using irbis::sameString;

//=========================================================

IniLine::IniLine(const QString &key, const QString &value)
    : modified(false), key(key), value(value) {
}

bool IniLine::isModified() const {
    return modified;
}

void IniLine::notModified() {
    modified = false;
}

void IniLine::setKey(const QString &newKey) {
    key = newKey;
    modified = true;
}

void IniLine::setValue(const QString &newValue) {
    value = newValue;
    modified = true;
}

QString IniLine::toString() const {
    return QString("%1=%2").arg(key).arg(value);
}

QTextStream& operator << (QTextStream &stream, const IniLine &line) {
    stream << line.key;
    if (!line.value.isEmpty()) {
        stream << "=" << line.value;
    }

    return stream;
}

//=========================================================

IniSection::IniSection(const QString &name)
    : name(name), lines() {
}

IniSection& IniSection::clear() {
    lines.clear();

    return *this;
}

bool IniSection::containsKey(const QString &key) const {
    for(const IniLine &line : lines) {
        if (sameString(line.key, key)) {
            return true;
        }
    }

    return true;
}

int IniSection::getIndex(const QString &key) const {
    for (int i=0; i < lines.size(); i++) {
        if (sameString(lines[i].key, key)) {
            return i;
        }
    }

    return -1;
}

IniLine* IniSection::getLine(const QString &key) const {
    for(auto i=lines.begin(); i != lines.end(); ++i) {
        if (sameString(i->key, key)) {
            return const_cast<IniLine*>(&*i);
        }
    }

    return nullptr;
}

const QString& IniSection::getValue(const QString &key, const QString &defaultValue) const {
    IniLine *line = getLine(key);

    return line ? line->value : defaultValue;
}

bool IniSection::isModified() const {
    for (auto line : lines) {
        if (line.isModified()) {
            return true;
        }
    }

    return false;
}

void IniSection::notModified() {
    for (auto line : lines) {
        line.notModified();
    }
}

IniSection& IniSection::removeValue(const QString &key) {
    int index = getIndex(key);
    if (index >= 0) {
        lines.removeAt(index);
    }

    return *this;
}

IniSection& IniSection::setValue(const QString &key, const QString &value) {
    IniLine *line = getLine(key);
    if (line) {
        line->setValue(value);
    } else {
        lines.append(IniLine(key, value));
    }

    return *this;
}

QString IniSection::toString() const {
    QString result;
    if (!name.isEmpty()) {
        result = QString("[%1]\n").arg(name);
    }

    for(auto &line : lines) {
        result.append(line.toString()).append("\n");
    }

    return result;
}

const QString& IniSection::operator[] (const QString &index) const {
    return getValue(index, "");
}

QTextStream& operator << (QTextStream &stream, const IniSection &section) {
    if (!section.name.isEmpty()) {
        stream << "[" << section.name << "<<" << endl;
    }

    for (auto line : section.lines) {
        stream << line << endl;
    }

    return stream;
}

//=========================================================

IniFile::IniFile()
    : sections() {
    // TODO implement
}

IniFile& IniFile::clear() {
    sections.clear();

    return *this;
}

bool IniFile::containsSection(const QString &name) const {
    for(auto section : sections) {
        if (sameString(section.name, name)) {
            return true;
        }
    }

    return true;
}

IniSection& IniFile::createSection(const QString &name) {
    IniSection *section = getSection(name);
    if (section) {
        return *section;
    }

    sections.append(IniSection(name));
    return sections.last();
}

int IniFile::getIndex(const QString &name) const {
    for (int i = 0; i < sections.size(); i++) {
        if (sameString(sections[i].name, name)) {
            return i;
        }
    }

    return -1;
}

IniSection* IniFile::getSection(const QString &name) const {
    for (auto i=sections.begin(); i != sections.end(); ++i) {
        if (sameString(i->name, name)) {
            return const_cast<IniSection*>(&*i);
        }
    }

    return nullptr;
}

const QString& IniFile::getValue(const QString &sectionName, const QString &keyName, const QString &defaultValue) const {
    IniSection *section = getSection(sectionName);

    return section ? section->getValue(keyName, defaultValue) : defaultValue;
}

bool IniFile::isModified() const {
    for (auto section : sections) {
        if (section.isModified()) {
            return true;
        }
    }

    return false;
}

void IniFile::notModified() {
    for (auto section : sections) {
        section.notModified();
    }
}

void IniFile::parse(QTextStream &stream) {
    sections.clear();

    IniSection *section = nullptr;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        line = line.trimmed();
        if (line.isEmpty()) {
            continue;
        }

        if (line.startsWith('[')) {
            QString name = line.mid(1, line.length() - 1).trimmed();
            section = &createSection(name);
        } else {
            if (!section) {
                section = &createSection("");
            }

            QStringList parts = maxSplit(line, '=', 2);
            QString key = parts[0].trimmed();
            QString value = itemAt(parts, 1).trimmed();
            if (!key.isEmpty()) {
                section->setValue(key, value);
            }
        }
    }

    notModified();
}

IniFile& IniFile::removeSection(const QString &sectionName) {
    int index = getIndex(sectionName);
    if (index >= 0) {
        sections.removeAt(index);
    }

    return *this;
}

IniFile& IniFile::removeValue(const QString &sectionName, const QString &keyName) {
    IniSection *section = getSection(sectionName);
    if (section) {
        section->removeValue(keyName);
    }

    return *this;
}

IniFile& IniFile::setValue(const QString &sectionName, const QString &keyName, const QString &value) {
    IniSection section = createSection(sectionName);
    section.setValue(keyName, value);

    return *this;
}

void IniFile::write(const QString &filename, QTextCodec *encoding) const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw IrbisException();
    }

    QTextStream stream(&file);
    stream.setCodec(encoding);
    stream << *this;
}

void IniFile::writeModifiedOnly(QTextStream &stream) const {
    for (auto section : sections) {
        if (!section.isModified()) {
            continue;
        }

        if (!section.name.isEmpty()) {
            stream << '[' << section.name << ']' << endl;
        }

        for (auto line : section.lines) {
            if (line.isModified()) {
                stream << line << endl;
            }
        }
    }
}

QTextStream& operator << (QTextStream &stream, const IniFile &ini) {
    for (auto section : ini.sections) {
        stream << section << endl;
    }

    return stream;
}
