#include "pch.h"

MstFile64Test::MstFile64Test() {
}

MstFile64Test::~MstFile64Test() {
}

void MstFile64Test::readRecord_1() {
    QDir ibis = irbis64ibis();
    QString fileName = ibis.filePath("ibis.mst");
    MstFile64 file(fileName);
    file.open();
    QVERIFY(file.control.nextMfn == 333);

    MstRecord64 record = file.readRecord(22951100L);
    QVERIFY(record.offset == 22951100L);
    QVERIFY(record.leader.status == 32);
    QVERIFY(record.dictionary.size() == 100);
    QVERIFY(record.dictionary[87].text == "^AКуда пойти учиться?^EИнформ. - реклам. справ^FЗ. М. Акулова, А. М. Бабич ; ред. А. С. Павловский [и др.]");
}
