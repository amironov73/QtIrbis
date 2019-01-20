#include "QtIrbis.h"
#include "IrbisTests.h"

IrbisDateTest::IrbisDateTest() {
}

IrbisDateTest::~IrbisDateTest() {
}

void IrbisDateTest::constructor_1() {
    IrbisDate date("20180203");
    QVERIFY(date.text == "20180203");
    QDate qDate(2018, 2, 3);
    QVERIFY(date.date == QDateTime(qDate));
}

void IrbisDateTest::constructor_2() {
    QDateTime qDate(QDate(2018, 2, 3));
    IrbisDate date(qDate);
    QVERIFY(date.date == qDate);
    QVERIFY(date.text == "20180203");
}

void IrbisDateTest::convert_1() {
    QVERIFY(IrbisDate::convert("20180203") == QDateTime(QDate(2018, 2, 3)));
}

void IrbisDateTest::convert_2() {
    QVERIFY(IrbisDate::convert(QDateTime(QDate(2018, 2, 3))) == "20180203");
}

void IrbisDateTest::convert_3() {
    QVERIFY(IrbisDate::convert(QDate(2018, 2, 3)) == "20180203");
}

void IrbisDateTest::safeParse_1() {
    QVERIFY(IrbisDate::safeParse(QString()) == nullptr);
    QVERIFY(IrbisDate::safeParse("20180203")->date == QDateTime(QDate(2018, 2, 3)));
}

void IrbisDateTest::today_1() {
    QVERIFY(IrbisDate::today().length() == 8);
}

