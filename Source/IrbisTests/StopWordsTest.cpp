#include "pch.h"

StopWordsTest::StopWordsTest() {
}

StopWordsTest::~StopWordsTest() {
}

void StopWordsTest::parse_1() {
    QDir dir = testData();
    QString fileName = dir.filePath("IBIS.STW");
    StopWords words;
    words.parse(fileName);
    QVERIFY(words.mapping.count() == 225);
    QVERIFY(words.isStopWord("О"));
}

