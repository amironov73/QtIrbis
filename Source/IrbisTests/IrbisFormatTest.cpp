#include "QtIrbis.h"
#include "IrbisTests.h"

IrbisFormatTest::IrbisFormatTest() {
}

IrbisFormatTest::~IrbisFormatTest() {
}

void IrbisFormatTest::removeComments_1() {
    QVERIFY(IrbisFormat::removeComments(QString()) == QString());
    QVERIFY(IrbisFormat::removeComments("Hello") == "Hello");
    QVERIFY(IrbisFormat::removeComments("Hello/*comment") == "Hello");
}

void IrbisFormatTest::prepareFormat_1() {
    QVERIFY(IrbisFormat::prepareFormat(QString()) == QString());
    QVERIFY(IrbisFormat::prepareFormat("Hello") == "Hello");
    QVERIFY(IrbisFormat::prepareFormat("Hel\r\nlo") == "Hello");
}

