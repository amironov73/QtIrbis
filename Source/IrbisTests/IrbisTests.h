#ifndef IRBISTESTS_H
#define IRBISTESTS_H

#include <QtCore>
#include <QtTest>

class CommonTest : public QObject
{
    Q_OBJECT

public:
    QDir testData();
    QDir irbis64root();
    QDir irbis64datai();
    QDir irbis64ibis();
    QDir irbis64deposit();
};

class SubFieldTest : public QObject
{
    Q_OBJECT

public:
    SubFieldTest();
    ~SubFieldTest();

private slots:

    void constructor_1();
    void constructor_2();
    void constructor_3();
    void clone_1();
    void stream_1();
};

class RecordFieldTest : public QObject
{
    Q_OBJECT

public:
    RecordFieldTest();
    ~RecordFieldTest();

private slots:

    void constructor_1();
    void constructor_2();
    void constructor_3();
    void constructor_4();
    void add_1();
    void getFirstSubField_1();
    void getFirstSubfieldValue_1();
    void getSubField_1();
    void stream_1();
};

class MarcRecordTest : public QObject
{
    Q_OBJECT

public:
    MarcRecordTest();
    ~MarcRecordTest();

private slots:

    void constructor_1();
    void constructor_2();
    void add_1();
    void add_2();
    void clear_1();
    void fm_1();
    void fm_2();
    void fma_1();
    void fma_2();
    void getFirstField_1();
    void isDeleted_1();
    void stream_1();
};

class IrbisEncodingTest : public QObject
{
    Q_OBJECT

public:
    IrbisEncodingTest();
    ~IrbisEncodingTest();

private slots:

    void ansi_1();
    void utf_1();

};

class IrbisFormatTest : public QObject
{
    Q_OBJECT

public:
    IrbisFormatTest();
    ~IrbisFormatTest();

private slots:

    void removeComments_1();
    void prepareFormat_1();

};

class IrbisDateTest : public QObject
{
    Q_OBJECT

public:
    IrbisDateTest();
    ~IrbisDateTest();

private slots:

    void constructor_1();
    void constructor_2();
    void convert_1();
    void convert_2();
    void convert_3();
    void safeParse_1();
    void today_1();

};

class FileSpecificationTest : public QObject
{
    Q_OBJECT

public:
    FileSpecificationTest();
    ~FileSpecificationTest();

private slots:

    void constructor_1();
    void toString_1();
    void toString_2();

};

class ClientQueryTest : public QObject
{
    Q_OBJECT

public:
    ClientQueryTest();
    ~ClientQueryTest();

private slots:

    void encode_1();

};

class TextNavigatorTest : public QObject
{
    Q_OBJECT

public:
    TextNavigatorTest();
    ~TextNavigatorTest();

private slots:

    void constructor_1();
    void constructor_2();
    void charAt_1();
    void peekChar_1();
    void readChar_1();
    void readLine_1();
    void readTo_1();
    void readTo_2();
    void readUntil_1();
    void remainingText_1();

};

class StopWordsTest : public CommonTest
{
    Q_OBJECT

public:
    StopWordsTest();
    ~StopWordsTest();

private slots:

    void parse_1();

};

class NumberTextTest : public QObject
{
    Q_OBJECT

public:
    NumberTextTest();
    ~NumberTextTest();

private slots:

    void constructor_1();
    void increment_1();
    void parse_1();
    void toString_1();
};

class RecordSerializerTest : public QObject
{
    Q_OBJECT

public:
    RecordSerializerTest();
    ~RecordSerializerTest();

private slots:

    void roundtrip_1();
};

class IlfFileTest : public CommonTest
{
    Q_OBJECT

public:
    IlfFileTest();
    ~IlfFileTest();

private slots:

    void readLocalFile_1();
};

class IrbisTreeFileTest : public CommonTest
{
    Q_OBJECT

public:
    IrbisTreeFileTest();
    ~IrbisTreeFileTest();

private slots:

    void readLocalFile_1();
};

class Iso2709Test : public CommonTest
{
    Q_OBJECT

public:
    Iso2709Test();
    ~Iso2709Test();

private slots:

    void readLocalFile_1();
};

class XrfFile64Test : public CommonTest
{
    Q_OBJECT

public:
    XrfFile64Test();
    ~XrfFile64Test();

private slots:

    void readRecord_1();
};

#endif

