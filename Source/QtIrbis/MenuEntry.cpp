// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

MenuEntry::MenuEntry(const QString &code, const QString &comment)
    : code(code), comment(comment) {
}

QString MenuEntry::toString() const {
    return code + " - " + comment;
}
