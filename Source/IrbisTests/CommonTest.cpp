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

QDir CommonTest::irbis64root() {
    QDir result = testData();
    result.cd("Irbis64");

    return result;
}

QDir CommonTest::irbis64datai() {
    QDir result = irbis64root();
    result.cd("Datai");

    return result;
}

QDir CommonTest::irbis64ibis() {
    QDir result = irbis64datai();
    result.cd("IBIS");

    return result;
}

QDir CommonTest::irbis64deposit() {
    QDir result = irbis64datai();
    result.cd("Deposit");

    return result;
}

