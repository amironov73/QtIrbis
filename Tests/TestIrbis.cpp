#include <QtCore>
#include <QtTest>

#include "QtIrbis.h"

class TestIrbis: public QObject
{
    Q_OBJECT

private slots:

    void subfield_constructor_1() {
        SubField sf;
        QVERIFY(sf.isEmpty());
        QVERIFY(sf.code.unicode() == 0);
        QVERIFY(sf.value.isNull());
    }

    void subfield_constructor_2() {
        SubField sf('a');
        QVERIFY(sf.isEmpty());
        QVERIFY(sf.code == 'a');
        QVERIFY(sf.value.isNull());
        QVERIFY(sf.toString() == "^a");
    }

    void subfield_constructor_3() {
        SubField sf('a', "Value");
        QVERIFY(!sf.isEmpty());
        QVERIFY(sf.code == 'a');
        QVERIFY(!sf.value.isNull());
        QVERIFY(sf.toString() == "^aValue");
    }

    void subfield_clone_1() {
        SubField first('a', "Value");
        SubField *second = first.clone();
        QVERIFY(first.code == second->code);
        QVERIFY(first.value == second->value);
    }

    //=====================================================

    void recordField_constructor_1() {
        RecordField field;
        QVERIFY(field.isEmpty());
    }

    void recordField_constructor_2() {
        RecordField field(100);
        QVERIFY(field.isEmpty());
    }

    void recordField_constructor_3() {
        RecordField field(100, "Value");
        QVERIFY(!field.isEmpty());
    }

    void recordField_add_1() {
        RecordField field(100);
        QVERIFY(field.subfields.size() == 0);
        field.add('a', "SubfieldA")
            .add('b', "SubfieldB");
        QVERIFY(field.subfields.size() == 2);
        field.clear();
        QVERIFY(field.subfields.size() == 0);
    }

    void recordField_clone_1() {
        RecordField source(100, "Value");
        source.add('a', "SubfieldA").add('b', "SubfieldB");
        RecordField *target = source.clone();
        QVERIFY(source.tag == target->tag);
        QVERIFY(source.value == target->value);
        QVERIFY(source.subfields.size() == target->subfields.size());
    }

    void recordField_getFirstSubField_1() {
        RecordField field(100);
        field.add('a', "SubfieldA").add('b', "SubfieldB");
        QVERIFY(field.getFirstSubField('a')->code == 'a');
        QVERIFY(field.getFirstSubField('b')->code == 'b');
        QVERIFY(!field.getFirstSubField('c'));
    }

    void recordField_getFirstSubfieldValue_1() {
        RecordField field(100);
        field.add('a', "SubfieldA").add('b', "SubfieldB");
        QVERIFY(field.getFirstSubFieldValue('a') == "SubfieldA");
        QVERIFY(field.getFirstSubFieldValue('b') == "SubfieldB");
        QVERIFY(field.getFirstSubFieldValue('c').isNull());
    }

    void recordField_getSubField_1() {
        RecordField field(100);
        field.add('a', "SubfieldA").add('b', "SubfieldB");
        QVERIFY(field.getSubField('a').size() == 1);
        QVERIFY(field.getSubField('b').size() == 1);
        QVERIFY(field.getSubField('c').size() == 0);
    }

    //=====================================================

    void marcRecord_constructor_1() {
        MarcRecord record;
        QVERIFY(record.mfn == 0);
        QVERIFY(record.status == 0);
        QVERIFY(record.version == 0);
        QVERIFY(record.fields.size() == 0);
    }

    void marcRecord_add_1() {
        MarcRecord record;
        QVERIFY(record.fields.size() == 0);
        record.add(100).add(200);
        QVERIFY(record.fields.size() == 2);
        QVERIFY(record.fields[0]->tag == 100);
        QVERIFY(record.fields[1]->tag == 200);
    }

    void marcRecord_add_2() {
        MarcRecord record;
        QVERIFY(record.fields.size() == 0);
        record.add(100, "Field100").add(200, "Field200");
        QVERIFY(record.fields.size() == 2);
        QVERIFY(record.fields[0]->tag == 100);
        QVERIFY(record.fields[0]->value == "Field100");
        QVERIFY(record.fields[1]->tag == 200);
        QVERIFY(record.fields[1]->value == "Field200");
    }

    void marcRecord_clear_1() {
        MarcRecord record;
        QVERIFY(record.fields.size() == 0);
        record.add(100, "Field100").add(200, "Field200");
        QVERIFY(record.fields.size() == 2);
        record.clear();
        QVERIFY(record.fields.size() == 0);
    }

    void marcRecord_clone_1() {
        MarcRecord source;
        source.database = "IBIS";
        source.mfn = 123;
        source.status = 234;
        source.version = 345;
        source.add(100, "Field100").add(200, "Field200");
        MarcRecord *target = source.clone();
        QVERIFY(source.database == target->database);
        QVERIFY(source.mfn == target->mfn);
        QVERIFY(source.status == target->status);
        QVERIFY(source.version == target->version);
        QVERIFY(source.fields.size() == target->fields.size());
    }

    void marcRecord_fm_1() {
        MarcRecord record;
        record.add(100, "Field100").add(200, "Field200");
        QVERIFY(record.fm(100) == "Field100");
        QVERIFY(record.fm(200) == "Field200");
        QVERIFY(record.fm(300).isNull());
    }

    void marcRecord_fm_2() {
        MarcRecord record;
        RecordField field100(100);
        field100.add('a', "SubA").add('b', "SubB");
        record.fields.append(&field100);
        RecordField field200(200);
        field200.add('c', "SubC").add('d', "SubD");
        record.fields.append(&field200);
        QVERIFY(record.fm(100, 'a') == "SubA");
        QVERIFY(record.fm(100, 'b') == "SubB");
        QVERIFY(record.fm(200, 'c') == "SubC");
        QVERIFY(record.fm(200, 'd') == "SubD");
        QVERIFY(record.fm(100, 'z').isNull());
        QVERIFY(record.fm(300, 'q').isNull());
    }

    void marcRecord_fma_1() {
        MarcRecord record;
        record.add(100, "Field100/1").add(100, "Field100/2")
            .add(200, "Field200/1").add(200, "Field200/2");
    }

    void marcRecord_fma_2() {
        MarcRecord record;
        RecordField field100(100);
        field100.add('a', "SubA").add('b', "SubB");
        record.fields.append(&field100);
        RecordField field200(200);
        field200.add('c', "SubC").add('d', "SubD");
        record.fields.append(&field200);
        QVERIFY(record.fma(100, 'a').size() == 1);
        QVERIFY(record.fma(100, 'b').size() == 1);
        QVERIFY(record.fma(200, 'c').size() == 1);
        QVERIFY(record.fma(200, 'd').size() == 1);
        QVERIFY(record.fma(200, 'z').size() == 0);
        QVERIFY(record.fma(300, 'z').size() == 0);
    }

    void marcRecord_getFirstField_1() {
        MarcRecord record;
        record.add(100, "Field100");
        record.add(200, "Field200");
        QVERIFY(record.getFirstField(100)->tag == 100);
        QVERIFY(record.getFirstField(200)->tag == 200);
        QVERIFY(!record.getFirstField(300));
    }

    void marcRecord_isDeleted_1() {
        MarcRecord record;
        QVERIFY(!record.isDeleted());
        record.status = RecordStatus::LogicallyDeleted;
        QVERIFY(record.isDeleted());
        record.status = RecordStatus::PhysicallyDeleted;
        QVERIFY(record.isDeleted());
    }

    //=====================================================

    void irbisEncoding_ansi_1() {
        QTextCodec *ansi = IrbisEncoding::ansi();
        QVERIFY(ansi->name() == "windows-1251");
    }

    void irbisEncoding_utf_1() {
        QTextCodec *utf = IrbisEncoding::utf();
        QVERIFY(utf->name() == "UTF-8");
    }

    //=====================================================

    void irbisFormat_removeComments_1() {
        QVERIFY(IrbisFormat::removeComments(QString()) == QString());
        QVERIFY(IrbisFormat::removeComments("Hello") == "Hello");
        QVERIFY(IrbisFormat::removeComments("Hello/*comment") == "Hello");
    }

    void irbisFormat_prepareFormat_1() {
        QVERIFY(IrbisFormat::prepareFormat(QString()) == QString());
        QVERIFY(IrbisFormat::prepareFormat("Hello") == "Hello");
        QVERIFY(IrbisFormat::prepareFormat("Hel\r\nlo") == "Hello");
    }

    //=====================================================

    void irbisDate_constructor_1() {
        IrbisDate date("20180203");
        QVERIFY(date.text == "20180203");
        QDate qDate(2018, 2, 3);
        QVERIFY(date.date == QDateTime(qDate));
    }

    void irbisDate_constructor_2() {
        QDateTime qDate(QDate(2018, 2, 3));
        IrbisDate date(qDate);
        QVERIFY(date.date == qDate);
        QVERIFY(date.text == "20180203");
    }

    void irbisDate_convert_1() {
        QVERIFY(IrbisDate::convert("20180203") == QDateTime(QDate(2018, 2, 3)));
    }

    void irbisDate_convert_2() {
        QVERIFY(IrbisDate::convert(QDateTime(QDate(2018, 2, 3))) == "20180203");
    }

    void irbisDate_convert_3() {
        QVERIFY(IrbisDate::convert(QDate(2018, 2, 3)) == "20180203");
    }

    void irbisDate_safeParse_1() {
        QVERIFY(IrbisDate::safeParse(QString()) == nullptr);
        QVERIFY(IrbisDate::safeParse("20180203")->date == QDateTime(QDate(2018, 2, 3)));
    }

    void irbisDate_today_1() {
        QVERIFY(IrbisDate::today().length() == 8);
    }

    //=====================================================

    void fileSpecification_constructor_1() {
        FileSpecification spec (IrbisPath::MasterFile, "IBIS", "brief.pft");
        QVERIFY(spec.path == 2);
        QVERIFY(spec.database == "IBIS");
        QVERIFY(spec.filename == "brief.pft");
    }

    void fileSpecification_toString_1() {
        FileSpecification spec (IrbisPath::MasterFile, "IBIS", "brief.pft");
        QVERIFY(spec.toString() == "2.IBIS.brief.pft");
    }

    void fileSpecification_toString_2() {
        FileSpecification spec (IrbisPath::Data, "", "dbnam1.mnu");
        QVERIFY(spec.toString() == "1..dbnam1.mnu");
    }

    //=====================================================

    void clientQuery_1() {
        IrbisConnection connection;
        ClientQuery query(&connection, CommandCode::Nop);
        query.addAnsi("Hello, world");
        query.addUtf("Привет, мир!");
        QByteArray array = query.encode();
        QVERIFY(array.size() == 51);
    }

    //=====================================================

    void textNavigator_constructor_1() {
        QString hello = "Hello, world!";
        TextNavigator navigator(hello);
        QVERIFY(!navigator.eot());
        QVERIFY(navigator.line() == 1);
        QVERIFY(navigator.column() == 1);
        QVERIFY(navigator.position() == 0);
        QVERIFY(navigator.length() == 13);
    }

    void textNavigator_constructor_2() {
        QString hello = "Hello, world!";
        TextNavigator navigator1(hello);
        TextNavigator navigator2(navigator1);
        QVERIFY(navigator2.line() == 1);
        QVERIFY(navigator2.column() == 1);
        QVERIFY(navigator2.position() == 0);
        QVERIFY(navigator2.length() == 13);
    }

    void textNavigator_charAt_1() {
        QString hello = "Hello, world!";
        TextNavigator navigator(hello);
        QVERIFY(navigator.charAt(0) == 'H');
        QVERIFY(navigator.charAt(-1) == TextNavigator::EOT);
        QVERIFY(navigator.charAt(100) == TextNavigator::EOT);
        QVERIFY(navigator.charAt(1) == 'e');
        QVERIFY(navigator.charAt(12) == '!');
    }

    void textNavigator_peekChar_1() {
        QString hello = "Hello, world!";
        TextNavigator navigator(hello);
        QVERIFY(navigator.peekChar() == 'H');
        QVERIFY(navigator.peekChar() == 'H');
    }

    void textNavigator_readChar_1() {
        QString hello = "Hello, world!";
        TextNavigator navigator(hello);
        QVERIFY(navigator.readChar() == 'H');
        QVERIFY(navigator.readChar() == 'e');
        for (int i = 0; i < 100; ++i) {
            navigator.readChar();
        }
        QVERIFY(navigator.readChar() == TextNavigator::EOT);
    }

    void textNavigator_readLine_1() {
        QString hello = "Hello,\nworld!";
        TextNavigator navigator(hello);
        QVERIFY(navigator.readLine() == "Hello,");
        QVERIFY(navigator.readLine() == "world!");
        QVERIFY(navigator.readLine().isNull());
    }

    void textNavigator_readTo_1() {
        QString hello = "Hello, world!";
        TextNavigator navigator(hello);
        QVERIFY(navigator.readTo(',') == "Hello");
        QVERIFY(navigator.readTo('!') == " world");
        QVERIFY(navigator.readTo(',').isNull());
    }

    void textNavigator_readTo_2() {
        QString hello = "Hello, world!";
        TextNavigator navigator(hello);
        QVERIFY(navigator.readTo(' ') == "Hello,");
        QVERIFY(navigator.readTo(' ') == "world!");
        QVERIFY(navigator.readTo(' ').isNull());
    }

    void textNavigator_readUntil_1() {
        QString hello = "Hello, world!";
        TextNavigator navigator(hello);
        QVERIFY(navigator.readUntil(',') == "Hello");
        QVERIFY(navigator.readUntil('!') == ", world");
        QVERIFY(navigator.readUntil('!').isEmpty());
    }

    void textNavigator_remainingText_1() {
        QString hello = "Hello, world!";
        TextNavigator navigator(hello);
        QVERIFY(navigator.readChar() == 'H');
        QVERIFY(navigator.remainingText() == "ello, world!");
        QVERIFY(navigator.remainingText() == "ello, world!");
    }
};

QTEST_MAIN(TestIrbis);
#include "TestIrbis.moc"
