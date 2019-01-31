#include "pch.h"

using irbis::fastToString;

FunctionTest::FunctionTest() {
}

FunctionTest::~FunctionTest() {
}

void FunctionTest::fastToString_1() {
    QString value = fastToString(0);
    QVERIFY(value == "0");

    value = fastToString(1);
    QVERIFY(value == "1");

    value = fastToString(2);
    QVERIFY(value == "2");

    value = fastToString(12);
    QVERIFY(value == "12");

    value = fastToString(123456789);
    QVERIFY(value == "123456789");
}
