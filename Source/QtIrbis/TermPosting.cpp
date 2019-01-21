// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::fastParse32;
using irbis::maxSplit;

//=========================================================

QList<TermPosting> TermPosting::parse(ServerResponse &response) {
    QList<TermPosting> result;
    while (true) {
        QString line = response.readUtf();
        if (line.isEmpty()) {
            break;
        }

        QStringList parts = maxSplit(line, '#', 5);
        if (parts.length() < 4) { //-V112
            break;
        }

        TermPosting item;
        item.mfn = fastParse32(parts[0]);
        item.tag = fastParse32(parts[1]);
        item.occurrence = fastParse32(parts[2]);
        item.count = fastParse32(parts[3]);
        if (parts.length() > 4) { //-V112
            item.text = parts[4];
        }
        result.append(item);
    }

    return result;

}

QString TermPosting::toString() const {
    return QString("mfn=") + QString::number(mfn) +
            ", tag=" + QString::number(tag) +
            ", occurrence=" + QString::number(occurrence) +
            ", count=" + QString::number(count) +
            ", text=" + text;
}
