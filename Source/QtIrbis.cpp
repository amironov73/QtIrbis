#include "QtIrbis.h"

//=========================================================

bool sameChar(QChar first, QChar second) {
    return first.toUpper() == second.toUpper();
}

bool sameString(QString first, QString second) {
    return first.compare(second, Qt::CaseInsensitive) == 0;
}
