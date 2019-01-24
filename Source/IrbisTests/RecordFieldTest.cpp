#include "pch.h"

#include <sstream>

RecordFieldTest::RecordFieldTest() {
}

RecordFieldTest::~RecordFieldTest() {
}

void RecordFieldTest::constructor_1() {
    RecordField field;
    QVERIFY(field.isEmpty());
}

void RecordFieldTest::constructor_2() {
    RecordField field(100);
    QVERIFY(field.isEmpty());
}

void RecordFieldTest::constructor_3() {
    RecordField field(100, "Value");
    QVERIFY(!field.isEmpty());
}

void RecordFieldTest::constructor_4() {
    RecordField source(100, "Value");
    source.add('a', "SubfieldA").add('b', "SubfieldB");
    RecordField target(source);
    QVERIFY(source.tag == target.tag);
    QVERIFY(source.value == target.value);
    QVERIFY(source.subfields.size() == target.subfields.size());
}

void RecordFieldTest::add_1() {
    RecordField field(100);
    QVERIFY(field.subfields.size() == 0);
    field.add('a', "SubfieldA")
        .add('b', "SubfieldB");
    QVERIFY(field.subfields.size() == 2);
    field.clear();
    QVERIFY(field.subfields.size() == 0);
}

void RecordFieldTest::getFirstSubField_1() {
    RecordField field(100);
    field.add('a', "SubfieldA").add('b', "SubfieldB");
    QVERIFY(field.getFirstSubField('a')->code == 'a');
    QVERIFY(field.getFirstSubField('b')->code == 'b');
    QVERIFY(!field.getFirstSubField('c'));
}

void RecordFieldTest::getFirstSubfieldValue_1() {
    RecordField field(100);
    field.add('a', "SubfieldA").add('b', "SubfieldB");
    QVERIFY(field.getFirstSubFieldValue('a') == "SubfieldA");
    QVERIFY(field.getFirstSubFieldValue('b') == "SubfieldB");
    QVERIFY(field.getFirstSubFieldValue('c').isNull());
}

void RecordFieldTest::getSubField_1() {
    RecordField field(100);
    field.add('a', "SubfieldA").add('b', "SubfieldB");
    QVERIFY(field.getSubField('a').size() == 1);
    QVERIFY(field.getSubField('b').size() == 1);
    QVERIFY(field.getSubField('c').size() == 0);
}

void RecordFieldTest::stream_1() {
    RecordField field(100);
    field.add('a', "SubfieldA").add('b', "SubfieldB");
    std::ostringstream stream;
    stream << field;
    QVERIFY(stream.str() == "100#^aSubfieldA^bSubfieldB");
}
