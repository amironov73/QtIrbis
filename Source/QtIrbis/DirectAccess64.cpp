// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

static QString getExt(const QString &path, const QString &ext) {
    QFileInfo info(path);
    if (info.isDir()) {
        QDir dir(path);
        QString name = info.baseName();
        name = name.toLower(); // TODO some more smarter
        info.setFile(dir, name);
    }

    QString suffix = info.suffix();
    if (suffix.isEmpty()) {
        info.setFile(info.filePath() + '.' + ext);
    } else if (suffix != ext) {
        QString minusSuffix = path.mid(0, path.length() - suffix.length() - 1);
        info.setFile(minusSuffix + '.' + ext);
    }

    return info.absoluteFilePath();
}

static QString getMst(const QString &path) {
    return getExt(path, "mst");
}

static QString getXrf(const QString &path) {
    return getExt(path, "xrf");
}

DirectAccess64::DirectAccess64(const QString &path)
    : mst(getMst(path)), xrf(getXrf(path)),
      database(QFileInfo(mst.fileName).baseName()) {
}

bool DirectAccess64::open() {
    bool result = mst.open();
    if (result) {
        result = xrf.open();
    }

    return result;
}

MstRecord64 DirectAccess64::readRawRecord(qint32 mfn) {
    XrfRecord64 xrfRecord = xrf.readRecord(mfn);
    MstRecord64 result = mst.readRecord(xrfRecord.offset);

    return result;
}

MarcRecord DirectAccess64::readRecord(qint32 mfn) {
    MstRecord64 raw = readRawRecord(mfn);
    MarcRecord result = raw.toMarcRecord();
    result.database = database;
    result.mfn = mfn;

    return result;
}
