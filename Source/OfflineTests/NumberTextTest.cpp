#include "pch.h"

NumberTextTest::NumberTextTest() {
}

NumberTextTest::~NumberTextTest() {
}

void NumberTextTest::constructor_1() {
    NumberText number;
    QVERIFY(number.size() == 0);
}

void NumberTextTest::increment_1() {
    NumberText number("hello001world002");
    number.increment();
    QVERIFY(number.size() == 2);
    QVERIFY(number.getPrefix(0) == "hello");
    QVERIFY(number.getPrefix(1) == "world");
    QVERIFY(number.getValue(0) == 1);
    QVERIFY(number.getValue(1) == 3);
}

void NumberTextTest::parse_1() {
    NumberText number;
    number.parse("hello001world002");
    QVERIFY(number.size() == 2);
    QVERIFY(number.getPrefix(0) == "hello");
    QVERIFY(number.getPrefix(1) == "world");
    QVERIFY(number.getValue(0) == 1);
    QVERIFY(number.getValue(1) == 2);
}

void NumberTextTest::toString_1() {
    NumberText number;
    number.append("hello", true, 1).append("world", true, 2);
    QString text = number.toString();
    QVERIFY(text == "hello1world2");
}
