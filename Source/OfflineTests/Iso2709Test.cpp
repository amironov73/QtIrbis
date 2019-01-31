#include "pch.h"

Iso2709Test::Iso2709Test() {
}

Iso2709Test::~Iso2709Test() {
}

void Iso2709Test::readLocalFile_1() {
    QDir dir = testData();
    QString fileName = dir.filePath("TEST1.ISO");
    QFile file(fileName);
    QVERIFY(file.open(QIODevice::ReadOnly));
    QTextCodec *encoding = IrbisEncoding::ansi();
    MarcRecord *record = Iso2709::readRecord(file, *encoding);
    QVERIFY(record->fields.size() == 16);
    delete record;
}
