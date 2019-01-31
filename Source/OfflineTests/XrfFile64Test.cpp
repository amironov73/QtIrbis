#include "pch.h"

XrfFile64Test::XrfFile64Test() {
}

XrfFile64Test::~XrfFile64Test() {
}

void XrfFile64Test::readRecord_1() {
    QDir ibis = irbis64ibis();
    QString fileName = ibis.filePath("ibis.xrf");
    XrfFile64 file(fileName);
    file.open();

    XrfRecord64 record = file.readRecord(1);
    QVERIFY(record.offset == 22951100);
    QVERIFY(record.status == 0);

    record = file.readRecord(2);
    QVERIFY(record.offset == 44260851);
    QVERIFY(record.status == 0);
}
