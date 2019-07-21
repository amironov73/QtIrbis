// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

IrbisResource::IrbisResource(const QString &name, const QString &content) : name(name), content(content) {
}

QTextStream& operator << (QTextStream &stream, const IrbisResource &resource) {
    stream << resource.name << ": " << resource.content;
    return stream;
}

