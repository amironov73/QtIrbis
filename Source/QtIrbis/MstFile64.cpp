// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

MstFile64::MstFile64(const QString &fileName)
    : _file(fileName), _stream(), _mutex(), control(), fileName(fileName) {
}

bool MstFile64::open() {
    bool result = _file.open(QIODevice::ReadOnly);
    if (result) {
        _stream.setDevice(&_file);
        _stream.setByteOrder(QDataStream::BigEndian);
        _stream >> control;
    }

    return result;
}

MstRecord64 MstFile64::readRecord(qint64 position) {
    QTextCodec *utf = IrbisEncoding::utf();
    QMutexLocker locker(&_mutex);
    _file.seek(position);
    MstRecord64 result;
    result.offset = position;
    _stream >> result.leader;
    for (qint32 i = 0; i < result.leader.nvf; ++i) {
        MstDictionaryEntry64 entry;
        _stream >> entry;
        result.dictionary.append(entry);
    }

    QByteArray array;
    for (MstDictionaryEntry64 &entry : result.dictionary) {
        qint32 length = entry.length;
        array.reserve(length);
        _file.seek(position + result.leader.base + entry.position);
        char *data = array.data();
        _file.read(data, length);
        entry.text = utf->toUnicode(data, length);
    }

    return result;
}
