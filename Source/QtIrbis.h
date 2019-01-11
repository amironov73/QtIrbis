#ifndef QTIRBIS_H
#define QTIRBIS_H

#include <QtCore>
#include <QtNetwork>

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
    void parseSingle(QStringList &lines);

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

class ClientQuery;
class DatabaseInfo;
class FoundLine;
class IrbisException;
class MenuEntry;
class MenuFile;
class PostingParameters;
class RawRecord;
class SearchParameters;
class SearchScenario;
class ServerStat;
class ServerResponse;
class TableDefinition;
class TermInfo;
class TermParameters;
class TermPosting;
class UserInfo;

//=========================================================

class QTIRBIS_EXPORT IrbisDate
{
public:
    QString text;
    QDateTime date;

    IrbisDate(QString text);
    IrbisDate(QDateTime date);

    static QDateTime convert(QString text);
    static QString convert(QDateTime date);
    static QString convert(QDate date);
    static QString today();
    static IrbisDate* safeParse(QString text);
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

    IrbisVersion();

    static IrbisVersion parse (ServerResponse &response);
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

    IrbisProcessInfo();

    static QList<IrbisProcessInfo> parse(ServerResponse &response);
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

    DatabaseInfo();

    static DatabaseInfo parse(ServerResponse &response);
    static QList<DatabaseInfo> parse(MenuFile &menu);
};

//=========================================================

class QTIRBIS_EXPORT IniFile {
public:

    IniFile();

    static IniFile parse(QTextStream &stream);
};

//=========================================================

class QTIRBIS_EXPORT CommandCode
{
public:
    const static QString ExclusizeDatabaseLock;
    const static QString RecordList;
    const static QString ServerInfo;
    const static QString DatabaseStat;
    const static QString FormatIsoGroup;
    const static QString UnknownCommand4;
    const static QString GlobalConnection;
    const static QString SaveRecordGroup;
    const static QString Print;
    const static QString UpdateIniFile;
    const static QString ImportIso;
    const static QString RegisterClient;
    const static QString UnregisterClient;
    const static QString ReadRecord;
    const static QString UpdateRecord;
    const static QString UnlockRecord;
    const static QString ActualizeRecord;
    const static QString FormatRecord;
    const static QString ReadTerms;
    const static QString ReadPostings;
    const static QString CorrectVirtualRecord;
    const static QString Search;
    const static QString ReadDocument;
    const static QString Backup;
    const static QString Nop;
    const static QString GetMaxMfn;
    const static QString ReadTermsReverse;
    const static QString UnlockRecords;
    const static QString FullTextSearch;
    const static QString EmptyDatabase;
    const static QString CreateDatabase;
    const static QString UnlockDatabase;
    const static QString GetRecordPostings;
    const static QString DeleteDatabase;
    const static QString ReloadMasterFile;
    const static QString ReloadDictionary;
    const static QString CreateDictionary;
    const static QString GetServerStat;
    const static QString UnknownCommandPlus2;
    const static QString GetProcessList;
    const static QString UnknownCommandPlus4;
    const static QString UnknownCommandPlus5;
    const static QString UnknownCommandPlus6;
    const static QString SetUserList;
    const static QString RestartServer;
    const static QString GetUserList;
    const static QString ListFiles;
};

//=========================================================

class QTIRBIS_EXPORT IrbisConnection
{
public:
    QString host;
    quint16 port;
    QString username;
    QString password;
    QString database;
    QChar workstation;
    qint32 clientId;
    qint32 queryId;
    bool isConnected;
    QStringList databaseStack;

    IrbisConnection();

    void actualizeRecord(QString database, int mfn);
    void connect();
    void createDatabase(QString databaseName, QString description, bool readerAccess);
    void createDictionary(QString databaseName);
    void deleteDatabase(QString databaseName);
    void deleteRecord(int mfn);
    void disconnect();
    ServerResponse execute(ClientQuery &query);
    void executeAndForget(ClientQuery &query);
    void executeAnsi(QString code);
    void executeAnsi(QString code, QString &arg1);
    QString formatRecord(QString &format, int mfn);
    QString formatRecord(QString &format, MarcRecord &record);
    QStringList formatRecords(QString &format, QList<int> mfns);
    DatabaseInfo getDatabaseInfo(QString &databaseName);
    int getMaxMfn(QString &databaseName);
    ServerStat getServerStat();
    IrbisVersion getServerVersion();
    QList<UserInfo> getUserList();
    QList<DatabaseInfo> listDatabases(IniFile &iniFile, QString defaultFileName);
    QList<DatabaseInfo> listDatabases(FileSpecification &specification);
    QStringList listFiles(FileSpecification &specification);
    QStringList listFiles(QList<FileSpecification> specifications);
    QList<IrbisProcessInfo> listProcesses();
    QString monitorOperation(QString operation);
    void noOp();
    void parseConnectionString(QString &connectionString);
    QString popDatabase();
    QString printTable(TableDefinition &definition);
    QString pushDatabase(QString newDatabase);
    QByteArray readBinaryFile(FileSpecification &specification);
    IniFile readIniFile(FileSpecification &specification);
    MenuFile readMenuFile(FileSpecification &specification);
    QList<TermPosting> readPostings(PostingParameters &parameters);
    RawRecord readRawRecord(QString &databaseName, qint32 mfn);
    MarcRecord readRecord(qint32 mfn);
    MarcRecord readRecord(QString &databaseName, qint32 mfn);
    MarcRecord readRecord(QString &databaseName, qint32 mfn, qint32 version);
    QList<SearchScenario> readSearchScenario(FileSpecification &specification);
    QList<TermInfo> readTerms(TermParameters &parameters);
    QString readTextFile(FileSpecification &specification);
    QStringList readTextFiles(QList<FileSpecification> specifications);
    void reloadDictionary(QString &databaseName);
    void reloadMasterFile(QString &databaseName);
    void restartServer();
    QList<int> search(QString &expression);
    QList<int> search(SearchParameters &parameters);
    QString toConnectionString();
    void truncateDatabase(QString &databaseName);
    void unlockDatabase(QString &databaseName);
    void unlockRecords(QString &databaseName, QList<int> mfnList);
    void updateIniFile(QStringList &lines);
    qint32 writeRecord(MarcRecord &record);
    qint32 writeRecord(MarcRecord &record, bool lockFlag, bool actualize, bool dontParseResponse);
    void writeTextFile(FileSpecification &specification);
};

//=========================================================

class QTIRBIS_EXPORT ClientQuery
{
private:
    IrbisConnection *connection;
    QBuffer buffer;

public:
    ClientQuery(IrbisConnection *connection, QString commandCode);

    ClientQuery& add(int value);
    ClientQuery& add(FileSpecification &specification);
    ClientQuery& add(MarcRecord &record);
    ClientQuery& add(RawRecord &record);
    ClientQuery& addAnsi(QString &text);
    ClientQuery& addAnsiNoLf(QString &text);
    ClientQuery& addLineFeed();
    ClientQuery& addUtf(QString &text);
    QByteArray encode();
};

//=========================================================

class QTIRBIS_EXPORT ServerResponse
{
private:
    QTcpSocket *socket;
    QByteArray data;
    qint32 length;
    qint32 position;
    bool closed;
    int savedSymbol;

    static char preamble[];
    static const qint32 preambleLength = 17;

    int read();

public:
    QString command;
    int clientId;
    int queryId;
    int returnCode;

    ServerResponse(QTcpSocket *socket);
    ServerResponse(const ServerResponse &other);
    ServerResponse& operator= (const ServerResponse &other);
    ~ServerResponse();

    void checkReturnCode();
    void checkReturnCode(qint32 allowed);
    void checkReturnCode(QVector<qint32> &allowed);
    void close();
    QByteArray getBinaryFile();
    QByteArray getLine();
    int getReturnCode();
    QString readAnsi();
    QStringList readAnsi(qint32 count);
    qint32 readInt32();
    QStringList readRemainingAnsiLines();
    QString readRemainingAnsiText();
    QStringList readRemainingUtfLines();
    QString readRemainingUtfText();
    QString readUtf();
    QStringList readUtf(int count);
};

//=========================================================

class QTIRBIS_EXPORT FoundLine {
public:
    bool materialized;
    qint32 serialNumber;
    qint32 mfn;
    QObject icon;
    bool selected;
    QString description;
    QString sort;
};

//=========================================================

class QTIRBIS_EXPORT MenuEntry {
public:
    QString code;
    QString comment;

    MenuEntry(QString &code, QString &comment);

    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT MenuFile {
public:
    const static QString StopMarker;

    QString fileName;
    QList<MenuEntry*> entries;

    MenuFile();

    MenuFile& add(QString &code, QString &comment);
    MenuEntry* getEntry(QString &code);
    QString* getValue(QString &code);
    QString& getValue(QString &code, QString &defaultValue);
    static MenuFile parse(QTextStream &stream);
};

//=========================================================

class QTIRBIS_EXPORT PostingParameters {
public:
    QString database;
    qint32 firstPosting;
    QString format;
    qint32 numberOfPostings;
    QString term;
    QStringList listOfTerms;

    PostingParameters();
};

//=========================================================

class QTIRBIS_EXPORT RawRecord {
public:
    QString database;
    QString mfn;
    QString status;
    QString version;
    QStringList fields;

    RawRecord();

    QString toString();
};

//=========================================================

class QTIRBIS_EXPORT SearchParameters {
public:
    QString database;
    qint32 firstRecord;
    QString formatSpecification;
    qint32 maxMfn;
    qint32 minMfn;
    qint32 numberOfRecords;
    QString searchExpression;
    QString sequentialSpecification;
    QString filterSpecification;
    bool utfFormat;
    bool nestedCall;

    SearchParameters();
};

//=========================================================

class QTIRBIS_EXPORT SearchScenario {
public:
    QString name;
    QString prefix;
    qint32 dictionaryType;
    QString menuName;
    QString oldFormat;
    QString correction;
    QString truncation;
    QString hint;
    QString modByDicAuto;
    QString logic;
    QString advance;
    QString format;

    SearchScenario();

    static QList<SearchScenario> parse(IniFile &iniFile);
};

//=========================================================

class QTIRBIS_EXPORT ServerStat {
public:
    QList<ClientInfo> runningClients;
    qint32 clientCount;
    qint32 totalCommandCount;

    ServerStat();
    static ServerStat parse(ServerResponse &response);
};

//=========================================================

class QTIRBIS_EXPORT TableDefinition {
public:
    QString database;
    QString table;
    QStringList headers;
    QString mode;
    QString searchQuery;
    qint32 minMfn;
    qint32 maxMfn;
    QString sequentialQuery;
    QList<int> mfnList;
};

//=========================================================

class QTIRBIS_EXPORT TermInfo {
public:
    qint32 count;
    QString text;
};

//=========================================================

class QTIRBIS_EXPORT TermParameters {
public:
    QString database;
    qint32 numberOfTerms;
    bool reverseOrder;
    QString startTerm;
    QString format;
};

//=========================================================

class QTIRBIS_EXPORT TermPosting {
public:
    qint32 mfn;
    qint32 tag;
    qint32 occurrence;
    qint32 count;
    QString text;
};

//=========================================================

class QTIRBIS_EXPORT UserInfo {
private:
    QString formatPair(QString prefix, QString &value, QString defaultValue);

public:
    QString number;
    QString name;
    QString password;
    QString cataloger;
    QString reader;
    QString circulation;
    QString acquisitions;
    QString provision;
    QString administrator;

    UserInfo();

    QString encode();
    static QList<UserInfo> parse (ServerResponse &response);
};

//=========================================================

class QTIRBIS_EXPORT IrbisException
        : public QException
{
public:
    qint32 code;

    IrbisException() : code(0) {}
    IrbisException(qint32 c) : code(c) {}
};

//=========================================================

// Utilities

bool sameChar(QChar first, QChar second);
bool sameString(QString first, QString second);

qint32 fastParse32(QString &text);
qint32 fastParse32(const char *text);
qint32 fastParse32(const char *text, qint32 length);

QString fastToString(qint32 value);

QString& iif(QString &s1, QString &s2);
QString& iif(QString &s1, QString &s2, QString &s3);

//=========================================================

#endif // QTIRBIS_H