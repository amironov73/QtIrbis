// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::read64bit;

//=========================================================

XrfFile64::XrfFile64(const QString &fileName)
    : _fileName(fileName), _file(fileName), _stream(), _mutex() {
}

qint64 XrfFile64::_getOffset(qint32 mfn) {
    return static_cast<qint64>(XrfRecord64::RecordSize) * static_cast<qint64>(mfn - 1);
}

bool XrfFile64::open() {
    bool result = _file.open(QIODevice::ReadOnly);
    if (result) {
        _stream.setDevice(&_file);
        _stream.setByteOrder(QDataStream::BigEndian);
    }

    return result;
}

XrfRecord64 XrfFile64::readRecord(qint32 mfn) {
    QMutexLocker locker(&_mutex);

    qint64 offset = _getOffset(mfn);
    _file.seek(offset);
    XrfRecord64 result;
    result.mfn = mfn;
    result.offset = read64bit(_stream);
    _stream >> result.status;

    return result;
}

