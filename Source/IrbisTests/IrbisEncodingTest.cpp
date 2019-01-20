#include "QtIrbis.h"
#include "IrbisTests.h"

IrbisEncodingTest::IrbisEncodingTest() {
}

IrbisEncodingTest::~IrbisEncodingTest() {
}

void IrbisEncodingTest::ansi_1() {
    QTextCodec *ansi = IrbisEncoding::ansi();
    QVERIFY(ansi->name() == "windows-1251");
}

void IrbisEncodingTest::utf_1() {
    QTextCodec *utf = IrbisEncoding::utf();
    QVERIFY(utf->name() == "UTF-8");
}
