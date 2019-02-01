#include "pch.h"

AlphabetTableTest::AlphabetTableTest() {
}

AlphabetTableTest::~AlphabetTableTest() {
}

void AlphabetTableTest::parse_1() {
    QString text = "001 002 003";
    QTextStream stream(&text);
    AlphabetTable table = AlphabetTable::parse(stream);
    QVERIFY(table.characters.size() == 3);
    QVERIFY(!table.isAlpha('\1'));
    QVERIFY(!table.isAlpha('\2'));
    QVERIFY(!table.isAlpha('\3'));
    QVERIFY(table.isAlpha('\4'));
}

void AlphabetTableTest::instance_1() {
    const AlphabetTable &table = AlphabetTable::instance();
    QVERIFY(table.characters.size() == 182);
    QVERIFY(table.isAlpha('a'));
    QVERIFY(!table.isAlpha('!'));
    QStringList words = table.splitWords("Съешь ещё этих мягких французских булок, да выпей чаю");
    QVERIFY(words.length() == 9);
}

void AlphabetTableTest::readLocalFile_1() {
    QDir dir = testData();
    QString fileName = dir.filePath(AlphabetTable::FileName);
    AlphabetTable table = AlphabetTable::readLocalFile(fileName);
    QVERIFY(table.characters.size() == 182);
    QVERIFY(table.isAlpha('a'));
    QVERIFY(!table.isAlpha('!'));
}

void AlphabetTableTest::trimText_1() {
    const AlphabetTable &table = AlphabetTable::instance();
    QVERIFY(table.trimText("") == "");
    QVERIFY(table.trimText("  ") == "");
    QVERIFY(table.trimText("!?!") == "");
    QVERIFY(table.trimText("Hello") == "Hello");
    QVERIFY(table.trimText("(Hello)") == "Hello");
    QVERIFY(table.trimText("Привет") == "Привет");
    QVERIFY(table.trimText("(Привет)") == "Привет");
    QVERIFY(table.trimText("Happy New Year") == "Happy New Year");
    QVERIFY(table.trimText("Happy New Year!") == "Happy New Year");
}

