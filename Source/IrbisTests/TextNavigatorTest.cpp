#include "QtIrbis.h"
#include "IrbisTests.h"

TextNavigatorTest::TextNavigatorTest() {
}

TextNavigatorTest::~TextNavigatorTest() {
}

void TextNavigatorTest::constructor_1() {
    QString hello = "Hello, world!";
    TextNavigator navigator(hello);
    QVERIFY(!navigator.eot());
    QVERIFY(navigator.line() == 1);
    QVERIFY(navigator.column() == 1);
    QVERIFY(navigator.position() == 0);
    QVERIFY(navigator.length() == 13);
}

void TextNavigatorTest::constructor_2() {
    QString hello = "Hello, world!";
    TextNavigator navigator1(hello);
    TextNavigator navigator2(navigator1);
    QVERIFY(navigator2.line() == 1);
    QVERIFY(navigator2.column() == 1);
    QVERIFY(navigator2.position() == 0);
    QVERIFY(navigator2.length() == 13);
}

void TextNavigatorTest::charAt_1() {
    QString hello = "Hello, world!";
    TextNavigator navigator(hello);
    QVERIFY(navigator.charAt(0) == 'H');
    QVERIFY(navigator.charAt(-1) == TextNavigator::EOT);
    QVERIFY(navigator.charAt(100) == TextNavigator::EOT);
    QVERIFY(navigator.charAt(1) == 'e');
    QVERIFY(navigator.charAt(12) == '!');
}

void TextNavigatorTest::peekChar_1() {
    QString hello = "Hello, world!";
    TextNavigator navigator(hello);
    QVERIFY(navigator.peekChar() == 'H');
    QVERIFY(navigator.peekChar() == 'H');
}

void TextNavigatorTest::readChar_1() {
    QString hello = "Hello, world!";
    TextNavigator navigator(hello);
    QVERIFY(navigator.readChar() == 'H');
    QVERIFY(navigator.readChar() == 'e');
    for (int i = 0; i < 100; ++i) {
        navigator.readChar();
    }
    QVERIFY(navigator.readChar() == TextNavigator::EOT);
}

void TextNavigatorTest::readLine_1() {
    QString hello = "Hello,\nworld!";
    TextNavigator navigator(hello);
    QVERIFY(navigator.readLine() == "Hello,");
    QVERIFY(navigator.readLine() == "world!");
    QVERIFY(navigator.readLine().isNull());
}

void TextNavigatorTest::readTo_1() {
    QString hello = "Hello, world!";
    TextNavigator navigator(hello);
    QVERIFY(navigator.readTo(',') == "Hello");
    QVERIFY(navigator.readTo('!') == " world");
    QVERIFY(navigator.readTo(',').isNull());
}

void TextNavigatorTest::readTo_2() {
    QString hello = "Hello, world!";
    TextNavigator navigator(hello);
    QVERIFY(navigator.readTo(' ') == "Hello,");
    QVERIFY(navigator.readTo(' ') == "world!");
    QVERIFY(navigator.readTo(' ').isNull());
}

void TextNavigatorTest::readUntil_1() {
    QString hello = "Hello, world!";
    TextNavigator navigator(hello);
    QVERIFY(navigator.readUntil(',') == "Hello");
    QVERIFY(navigator.readUntil('!') == ", world");
    QVERIFY(navigator.readUntil('!').isEmpty());
}

void TextNavigatorTest::remainingText_1() {
    QString hello = "Hello, world!";
    TextNavigator navigator(hello);
    QVERIFY(navigator.readChar() == 'H');
    QVERIFY(navigator.remainingText() == "ello, world!");
    QVERIFY(navigator.remainingText() == "ello, world!");
}

