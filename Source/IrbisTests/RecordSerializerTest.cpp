#include "pch.h"

#include <sstream>

RecordSerializerTest::RecordSerializerTest() {
}

RecordSerializerTest::~RecordSerializerTest() {
}

void RecordSerializerTest::roundtrip_1() {
    QByteArray array;
    QDataStream stream1(&array, QIODevice::WriteOnly);
    RecordSerializer serializer1(stream1);
    MarcRecord record1;
    record1.add(100, "Field100");
    RecordField field200(200);
    field200.add('a', "SubA").add('b', "SubB");
    record1.fields.append(field200);
    serializer1.serialize(record1);

    QDataStream stream2(&array, QIODevice::ReadOnly);
    RecordSerializer serializer2(stream2);
    MarcRecord record2 = serializer2.deserialize();

    QVERIFY(record1.toString() == record2.toString());
}
