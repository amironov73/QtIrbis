#include "pch.h"

IrbisTreeFileTest::IrbisTreeFileTest() {
}

IrbisTreeFileTest::~IrbisTreeFileTest() {
}

void IrbisTreeFileTest::readLocalFile_1() {
    QDir dir = testData();
    QString fileName = dir.filePath("test1.tre");
    IrbisTreeFile file;
    file.readLocalFile(fileName, IrbisEncoding::ansi());
    QVERIFY(file.roots.size() == 4);
}
