#include "pch.h"

QDir CommonTest::testData() {
    QDir candidate = QDir::current();

    while (true) {
        if (candidate.exists("TestData")) {
            candidate.cd("TestData");
            return candidate;
        }

        if (candidate.isRoot()) {
            throw IrbisException();
        }

        candidate.cdUp();
    }
}

