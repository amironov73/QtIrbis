#include "QtIrbis.h"
#include "IrbisTests.h"

ClientQueryTest::ClientQueryTest() {
}

ClientQueryTest::~ClientQueryTest() {
}

void ClientQueryTest::encode_1() {
    IrbisConnection connection;
    ClientQuery query(&connection, CommandCode::Nop);
    query.addAnsi("Hello, world");
    query.addUtf("Привет, мир!");
    QByteArray array = query.encode();
    QVERIFY(array.size() == 51);
}

