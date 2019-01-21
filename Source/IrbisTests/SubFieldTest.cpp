#include "QtIrbis.h"
#include "IrbisTests.h"

SubFieldTest::SubFieldTest() {
}

SubFieldTest::~SubFieldTest() {
}

void SubFieldTest::constructor_1() {
    SubField sf;
    QVERIFY(sf.isEmpty());
    QVERIFY(sf.code.unicode() == 0);
    QVERIFY(sf.value.isEmpty());
}

void SubFieldTest::constructor_2() {
    SubField sf('a');
    QVERIFY(sf.isEmpty());
    QVERIFY(sf.code == 'a');
    QVERIFY(sf.value.isEmpty());
    QVERIFY(sf.toString() == "^a");
}

void SubFieldTest::constructor_3() {
    SubField sf('a', "Value");
    QVERIFY(!sf.isEmpty());
    QVERIFY(sf.code == 'a');
    QVERIFY(!sf.value.isNull());
    QVERIFY(sf.toString() == "^aValue");
}

void SubFieldTest::clone_1() {
    SubField first('a', "Value");
    SubField second(first);
    QVERIFY(first.code == second.code);
    QVERIFY(first.value == second.value);
}

