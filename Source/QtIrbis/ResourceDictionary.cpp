// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

ResourceDictionary::ResourceDictionary() : _dictionary() {
}

ResourceDictionary& ResourceDictionary::add(const QString &name, const QString content) {
    IrbisResource resouce(name, content);
    _dictionary.insert(name, resouce);
    return *this;
}

ResourceDictionary& ResourceDictionary::clear() {
    _dictionary.clear();
    return *this;
}

qint32 ResourceDictionary::count() const {
    return _dictionary.count();
}

const QString* ResourceDictionary::get(const QString &name) const {
    auto resource = _dictionary.constFind(name);
    if (resource != _dictionary.end()) {
        return &resource.value().content;
    }

    return nullptr;
}

bool ResourceDictionary::have(const QString &name) const {
    return _dictionary.contains(name);
}

ResourceDictionary& ResourceDictionary::put(const QString &name, const QString content) {
    IrbisResource resouce(name, content);
    _dictionary.insert(name, resouce);
    return *this;
}

ResourceDictionary& ResourceDictionary::remove(const QString &name) {
    _dictionary.remove(name);
    return *this;
}

QList<IrbisResource> ResourceDictionary::toList() const {
    QList<IrbisResource> result;
    for (auto ptr = _dictionary.constBegin(); ptr != _dictionary.constEnd(); ptr++) {
        result.push_back(ptr.value());
    }
    return result;
}
