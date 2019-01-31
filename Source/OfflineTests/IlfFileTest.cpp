#include "pch.h"

IlfFileTest::IlfFileTest() {
}

IlfFileTest::~IlfFileTest() {
}

void IlfFileTest::readLocalFile_1() {
    QDir dir = testData();
    QString fileName = dir.filePath("MARS_WSS.ILF");
    IlfFile file;
    file.readLocalFile(fileName);
    QVERIFY(file.entries.size() == 190);
}
