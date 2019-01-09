#ifndef QTIRBIS_H
#define QTIRBIS_H

#include <QtCore>

#if defined(QTIRBIS_LIBRARY)
#define QTIRBIS_EXPORT Q_DECL_EXPORT
#else
#define QTIRBIS_EXPORT Q_DECL_IMPORT
#endif

//=========================================================

class QTIRBIS_EXPORT SubField
{
public:
    QChar code;
    QString value;

    SubField() : code('\0'), value() {}
    SubField(QChar code);
    SubField(QChar code, QString value);

    bool isEmpty() const;

    SubField* clone() const;

    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT RecordField
{
public:
    qint32 tag;
    QString value;
    QList<SubField*> subfields;

    RecordField() : tag(0), value(), subfields() {}
    RecordField(qint32 tag);
    RecordField(qint32 tag, QString value);

    bool isEmpty() const;

    RecordField& add(QChar code, QString value);
    RecordField& clear();
    RecordField* clone() const;
    SubField* getFirstSubField(QChar code) const;
    QString getFirstSubFieldValue(QChar code) const;
    QList<SubField*> getSubField(QChar code) const;

    static RecordField* parse(QString line);

    QString toString() const;
};

//=========================================================

enum RecordStatus
{
    LogicallyDeleted = 1,
    PhysicallyDeleted = 2,
    Deleted = LogicallyDeleted | PhysicallyDeleted,
    Absent = 4,
    NonActualized = 8,
    Last = 32,
    Locked = 64
};

//=========================================================

class QTIRBIS_EXPORT MarcRecord
{
public:
    QString database;
    qint32 mfn;
    qint32 status;
    qint32 version;
    QList<RecordField*> fields;

    MarcRecord() : database(), mfn(0), status(0), version(0), fields() {}

    MarcRecord& add(qint32 tag);
    MarcRecord& add(quint32 tag, QString value);
    MarcRecord& clear();
    MarcRecord* clone() const;
    QString fm(qint32 tag) const;
    QString fm(qint32 tag, QChar code) const;
    QStringList fma(qint32 tag) const;
    QStringList fma(qint32 tag, QChar code) const;
    RecordField *getFirstField(qint32 tag) const;
    bool isDeleted() const { return (status & RecordStatus::Deleted) != 0; }

    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT IrbisEncoding
{
private:
    static QTextCodec *_ansi;
    static QTextCodec *_utf;

public:
    static QTextCodec* ansi();
    static QTextCodec* utf();
};

//=========================================================

class QTIRBIS_EXPORT IrbisFormat
{
public:
    static QString removeComments(QString text);
    static QString prepareFormat(QString text);
};

//=========================================================

enum IrbisPath
{
    System = 0,
    Data = 1,
    MasterFile = 2,
    InvertedFile = 3,
    ParameterFile = 10,
    FullText = 11,
    InternalResource = 12
};

//=========================================================

class QTIRBIS_EXPORT FileSpecification
{
public:
    int path;
    QString database;
    QString filename;
    QString content;

    FileSpecification(): path(), database(), filename(), content() {}
    FileSpecification(int path, QString database, QString filename);

    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT IrbisVersion
{
public:
    QString organization;
    QString version;
    int maxClients;
    int connectedClients;
};

//=========================================================

class QTIRBIS_EXPORT IrbisProcessInfo
{
public:
    QString number;
    QString ipAddress;
    QString name;
    QString clientId;
    QString workstation;
    QString started;
    QString lastCommand;
    QString commandNumber;
    QString processId;
    QString state;
};

//=========================================================

class QTIRBIS_EXPORT ClientInfo
{
public:
    QString number;
    QString ipAddress;
    QString port;
    QString name;
    QString id;
    QString workstation;
    QString registered;
    QString acknowledged;
    QString lastCommand;
    QString commandNumber;
};

//=========================================================

class QTIRBIS_EXPORT DatabaseInfo
{
public:
    QString name;
    QString description;
};

//=========================================================

class QTIRBIS_EXPORT IrbisConnection
{
public:
    QString host;
    int port;
    QString username;
    QString password;
    QString database;
    char workstation;
    int clientId;
    int queryId;

    IrbisConnection();
    void actualizeRecord(QString database, int mfn);
    void connect();
    void createDatabase(QString databaseName, QString description, bool readerAccess);
    void createDictionary(QString databaseName);
    void deleteDatabase(QString databaseName);
    void deleteRecord(int mfn);
    void disconnect();
};

//=========================================================

class ClientQuery
{
private:
    IrbisConnection *connection;
    QBuffer buffer;

public:
    ClientQuery(IrbisConnection *connection, QString commandCode);

    ClientQuery& add(int value);
    ClientQuery& addAnsi(QString text);
    ClientQuery& addLineFeed();
    ClientQuery& addUtf(QString text);
    char* encode();
};

//=========================================================

class ServerResponse
{
public:
    QString command;
    int clientId;
    int queryId;
    int returnCode;

    ServerResponse();

    void close();
};

//=========================================================

// Utilities

bool sameChar(QChar first, QChar second);
bool sameString(QString first, QString second);

//=========================================================

#endif // QTIRBIS_H
