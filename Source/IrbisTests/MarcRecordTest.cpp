#include "pch.h"

#include <sstream>

MarcRecordTest::MarcRecordTest() {
}

MarcRecordTest::~MarcRecordTest() {
}

void MarcRecordTest::constructor_1() {
    MarcRecord record;
    QVERIFY(record.mfn == 0);
    QVERIFY(record.status == 0);
    QVERIFY(record.version == 0);
    QVERIFY(record.fields.size() == 0);
}

void MarcRecordTest::constructor_2() {
    MarcRecord source;
    source.database = "IBIS";
    source.mfn = 123;
    source.status = 234;
    source.version = 345;
    source.add(100, "Field100").add(200, "Field200");
    MarcRecord target(source);
    QVERIFY(source.database == target.database);
    QVERIFY(source.mfn == target.mfn);
    QVERIFY(source.status == target.status);
    QVERIFY(source.version == target.version);
    QVERIFY(source.fields.size() == target.fields.size());
}

void MarcRecordTest::add_1() {
    MarcRecord record;
    QVERIFY(record.fields.size() == 0);
    record.add(100).add(200);
    QVERIFY(record.fields.size() == 2);
    QVERIFY(record.fields[0].tag == 100);
    QVERIFY(record.fields[1].tag == 200);
}

void MarcRecordTest::add_2() {
    MarcRecord record;
    QVERIFY(record.fields.size() == 0);
    record.add(100, "Field100").add(200, "Field200");
    QVERIFY(record.fields.size() == 2);
    QVERIFY(record.fields[0].tag == 100);
    QVERIFY(record.fields[0].value == "Field100");
    QVERIFY(record.fields[1].tag == 200);
    QVERIFY(record.fields[1].value == "Field200");
}

void MarcRecordTest::clear_1() {
    MarcRecord record;
    QVERIFY(record.fields.size() == 0);
    record.add(100, "Field100").add(200, "Field200");
    QVERIFY(record.fields.size() == 2);
    record.clear();
    QVERIFY(record.fields.size() == 0);
}

void MarcRecordTest::fm_1() {
    MarcRecord record;
    record.add(100, "Field100").add(200, "Field200");
    QVERIFY(record.fm(100) == "Field100");
    QVERIFY(record.fm(200) == "Field200");
    QVERIFY(record.fm(300).isNull());
}

void MarcRecordTest::fm_2() {
    MarcRecord record;
    RecordField field100(100);
    field100.add('a', "SubA").add('b', "SubB");
    record.fields.append(field100);
    RecordField field200(200);
    field200.add('c', "SubC").add('d', "SubD");
    record.fields.append(field200);
    QVERIFY(record.fm(100, 'a') == "SubA");
    QVERIFY(record.fm(100, 'b') == "SubB");
    QVERIFY(record.fm(200, 'c') == "SubC");
    QVERIFY(record.fm(200, 'd') == "SubD");
    QVERIFY(record.fm(100, 'z').isNull());
    QVERIFY(record.fm(300, 'q').isNull());
}

void MarcRecordTest::fma_1() {
    MarcRecord record;
    record.add(100, "Field100/1").add(100, "Field100/2")
        .add(200, "Field200/1").add(200, "Field200/2");
}

void MarcRecordTest::fma_2() {
    MarcRecord record;
    RecordField field100(100);
    field100.add('a', "SubA").add('b', "SubB");
    record.fields.append(field100);
    RecordField field200(200);
    field200.add('c', "SubC").add('d', "SubD");
    record.fields.append(field200);
    QVERIFY(record.fma(100, 'a').size() == 1);
    QVERIFY(record.fma(100, 'b').size() == 1);
    QVERIFY(record.fma(200, 'c').size() == 1);
    QVERIFY(record.fma(200, 'd').size() == 1);
    QVERIFY(record.fma(200, 'z').size() == 0);
    QVERIFY(record.fma(300, 'z').size() == 0);
}

void MarcRecordTest::getFirstField_1() {
    MarcRecord record;
    record.add(100, "Field100");
    record.add(200, "Field200");
    QVERIFY(record.getFirstField(100)->tag == 100);
    QVERIFY(record.getFirstField(200)->tag == 200);
    QVERIFY(!record.getFirstField(300));
}

void MarcRecordTest::isDeleted_1() {
    MarcRecord record;
    QVERIFY(!record.isDeleted());
    record.status = RecordStatus::LogicallyDeleted;
    QVERIFY(record.isDeleted());
    record.status = RecordStatus::PhysicallyDeleted;
    QVERIFY(record.isDeleted());
}


void MarcRecordTest::stream_1() {
    MarcRecord record;
    record.mfn = 123;
    record.status = RecordStatus::Last;
    record.version = 321;
    RecordField field100(100);
    field100.add('a', "SubA").add('b', "SubB");
    record.fields.append(field100);
    RecordField field200(200);
    field200.add('c', "SubC").add('d', "SubD");
    record.fields.append(field200);
    std::ostringstream stream;
    stream << record;
    QVERIFY(stream.str() == "123#32\n0#321\n100#^aSubA^bSubB\n200#^cSubC^dSubD\n");
}

