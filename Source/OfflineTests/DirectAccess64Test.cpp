#include "pch.h"

DirectAccess64Test::DirectAccess64Test() {
}

DirectAccess64Test::~DirectAccess64Test() {
}

void DirectAccess64Test::constructor_1() {
    QDir ibis = irbis64ibis();
    QString fileName = ibis.filePath("ibis.mst");
    DirectAccess64 access(fileName);
    QVERIFY(access.open());
    QVERIFY(access.database == "ibis");
}

void DirectAccess64Test::constructor_2() {
    QDir ibis = irbis64ibis();
    QString fileName = ibis.filePath("ibis");
    DirectAccess64 access(fileName);
    QVERIFY(access.open());
    QVERIFY(access.database == "ibis");
}

void DirectAccess64Test::constructor_3() {
    QDir ibis = irbis64ibis();
    QString fileName = ibis.path();
    DirectAccess64 access(fileName);
    QVERIFY(access.open());
    QVERIFY(access.database == "IBIS");
}

void DirectAccess64Test::readRawRecord_1() {
    DirectAccess64 access(irbis64ibis().path());
    QVERIFY(access.open());
    MstRecord64 record = access.readRawRecord(1);
    QVERIFY(record.dictionary.size() == 100);
}

void DirectAccess64Test::readRecord_1() {
    DirectAccess64 access(irbis64ibis().path());
    QVERIFY(access.open());
    MarcRecord record = access.readRecord(1);
    QVERIFY(record.fields.size() == 100);
}

