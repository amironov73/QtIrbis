// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

StopWords::StopWords() : mapping() {
}

bool StopWords::isStopWord(const QString &word) const {
    if (word.isEmpty()) {
        return true;
    }

    QString word2 = word.trimmed();
    if (word2.isEmpty()) {
        return true;
    }

    word2 = word2.toUpper();

    return mapping.contains(word2);
}

void StopWords::parse(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        throw IrbisException();
    }

    QTextStream stream(&file);
    stream.setCodec(IrbisEncoding::ansi());

    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        if (!line.isEmpty()) {
            line = line.toUpper();
            mapping.insert(line);
        }
    }
}
