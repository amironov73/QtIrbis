#include "QtIrbis.h"

//=========================================================

MenuEntry::MenuEntry(const QString &code, const QString &comment)
    : code(code), comment(comment) {
}

QString MenuEntry::toString() const {
    return code + " - " + comment;
}
