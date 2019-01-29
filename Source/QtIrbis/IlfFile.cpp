// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::itemAt;
using irbis::maxSplit;
using irbis::readString;

//=========================================================

const QString IlfFile::MagicString = "IRBIS_LIBRARY_01"; // 16 bytes

IlfFile::IlfFile()
    : entries(), unknown1(0), slotCount(0), entryCount(0),
      writeCount(0), deleteCount(0) {
}

void IlfFile::readLocalFile(const QString &fileName) {
    QTextCodec *ansi = IrbisEncoding::ansi();
    entries.clear();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        throw IrbisException();
    }
    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);
    QString magic = readString(stream, 16, ansi);
    if (magic != MagicString) {
        throw IrbisException();
    }

    stream >> unknown1 >> slotCount >> entryCount >> writeCount >> deleteCount;

    for (qint32 i = 0; i < entryCount; ++i) {
        IlfEntry entry;
        double someDouble;
        qint16 deleted;
        stream >> entry.position >> someDouble >> deleted;
        entry.deleted = deleted != 0;
        entry.name = readString(stream, 24, ansi);
        entries.append(entry);
    }

    for(IlfEntry &entry : entries) {
        file.seek(entry.position);
        stream >> entry.number >> entry.dataLength >> entry.flags;
        QString data = readString(stream, entry.dataLength, ansi);
        data = data.replace("\r", "");
        QStringList list = maxSplit(data, '\n', 2);
        entry.description = itemAt(list, 0);
        entry.data = itemAt(list, 1);
    }
}

