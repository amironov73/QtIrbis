#include <QtCore>
#include <QtTest>

#include "QtIrbis.h"

class TestIrbis: public QObject
{
    Q_OBJECT

private slots:

    void dummyTest() {
        QVERIFY(QString("Hello") == "Hello");
    }

    void subfield_1() {
        SubField sf;
        QVERIFY(sf.isEmpty());
        QVERIFY(sf.code == '\0');
        QVERIFY(sf.value.isNull());
    }

    void subfield_2() {
        SubField sf('a');
        QVERIFY(sf.isEmpty());
        QVERIFY(sf.code == 'a');
        QVERIFY(sf.value.isNull());
        QVERIFY(sf.toString() == "^a");
    }

    void subfield_3() {
        SubField sf('a', "Value");
        QVERIFY(!sf.isEmpty());
        QVERIFY(sf.code == 'a');
        QVERIFY(!sf.value.isNull());
        QVERIFY(sf.toString() == "^aValue");
    }

    void subfield_4() {
        SubField first('a', "Value");
        SubField *second = first.clone();
        QVERIFY(first.code == second->code);
        QVERIFY(first.value == second->value);
    }

    void recordField_1() {
        RecordField field;
        QVERIFY(field.isEmpty());
    }

    void recordField_2() {
        RecordField field(100);
        QVERIFY(field.isEmpty());
    }

    void recordField_3() {
        RecordField field(100, "Value");
        QVERIFY(!field.isEmpty());
    }
};

QTEST_MAIN(TestIrbis);
#include "TestIrbis.moc"
