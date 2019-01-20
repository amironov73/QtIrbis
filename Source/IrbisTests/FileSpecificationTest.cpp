#include "QtIrbis.h"
#include "IrbisTests.h"

FileSpecificationTest::FileSpecificationTest() {
}

FileSpecificationTest::~FileSpecificationTest() {
}

void FileSpecificationTest::constructor_1() {
    FileSpecification spec (IrbisPath::MasterFile, "IBIS", "brief.pft");
    QVERIFY(spec.path == 2);
    QVERIFY(spec.database == "IBIS");
    QVERIFY(spec.filename == "brief.pft");
}

void FileSpecificationTest::toString_1() {
    FileSpecification spec (IrbisPath::MasterFile, "IBIS", "brief.pft");
    QVERIFY(spec.toString() == "2.IBIS.brief.pft");
}

void FileSpecificationTest::toString_2() {
    FileSpecification spec (IrbisPath::Data, "", "dbnam1.mnu");
    QVERIFY(spec.toString() == "1..dbnam1.mnu");
}
