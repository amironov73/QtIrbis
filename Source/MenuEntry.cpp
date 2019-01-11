#include "QtIrbis.h"

//=========================================================

MenuEntry::MenuEntry(QString &code, QString &comment)
    : code(code), comment(comment) {
}

QString MenuEntry::toString() const {
    return code + " - " + comment;
}
