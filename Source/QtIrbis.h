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

// Forward declaration

class ClientInfo;
class ClientQuery;
class CommandCode;
class DatabaseInfo;
class EmbeddedField;
class FileSpecification;
class FoundLine;
class IniFile;
class IniLine;
class IniSection;
class IrbisConnection;
class IrbisDate;
class IrbisEncoding;
class IrbisException;
class IrbisFormat;
class IrbisProcessInfo;
class IrbisText;
class IrbisVersion;
class MarcRecord;
class MenuEntry;
class MenuFile;
class PostingParameters;
class ProtocolText;
class RawRecord;
class RecordField;
class SearchParameters;
class SearchScenario;
class ServerStat;
class ServerResponse;
class SubField;
class TableDefinition;
class TermInfo;
class TermParameters;
class TermPosting;
class TextNavigator;
class UserInfo;

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

    ClientInfo();

    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT ClientQuery
{
private:
    IrbisConnection *connection;
    QBuffer buffer;

public:
    ClientQuery(IrbisConnection *connection, const QString &commandCode);

    ClientQuery& add(int value);
    ClientQuery& add(const FileSpecification &specification);
    ClientQuery& add(const MarcRecord &record);
    ClientQuery& add(const RawRecord &record);
    ClientQuery& addAnsi(const QString &text);
    ClientQuery& addAnsiNoLf(const QString &text);
    ClientQuery& addLineFeed();
    ClientQuery& addUtf(const QString &text);
    QByteArray encode();
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

class QTIRBIS_EXPORT DatabaseInfo
{
public:
    QString name;
    QString description;
    qint32 maxMfn;
    QList<int> logicallyDeletedRecords;
    QList<int> physicallyDeletedRecords;
    QList<int> nonActualizedRecords;
    QList<int> lockedRecords;
    bool databaseLocked;
    bool readOnly;

    DatabaseInfo();

    static DatabaseInfo parse(ServerResponse &response);
    static QList<DatabaseInfo> parse(MenuFile &menu);
    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT EmbeddedField {
public:
    const static QChar DefaultCode;

    static QList<RecordField> getEmbeddedFields(const RecordField &field, QChar sign = DefaultCode);
};

//=========================================================

class QTIRBIS_EXPORT FileSpecification
{
public:
    bool binaryFile;
    qint32 path;
    QString database;
    QString filename;
    QString content;

    FileSpecification();
    FileSpecification(int path, const QString &filename);
    FileSpecification(int path, const QString &database, const QString &filename);

    static FileSpecification parse(const QString &text);
    bool verify(bool throwException) const;

    QString toString() const;
};

bool operator == (const FileSpecification &first, const FileSpecification &second);
bool operator != (const FileSpecification &first, const FileSpecification &second);

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

class QTIRBIS_EXPORT IniFile {
public:
    QList<IniSection> sections;

    IniFile();

    IniFile& clear();
    bool containsSection (const QString &name) const;
    IniSection& createSection(const QString &name);
    bool isModified() const;
    void notModified();
    int getIndex(const QString &name) const;
    IniSection* getSection(const QString &name) const;
    const QString& getValue(const QString &sectionName, const QString &keyName, const QString &defaultValue) const;
    void parse(QTextStream &stream);
    IniFile& removeSection(const QString &sectionName);
    IniFile& removeValue(const QString &sectionName, const QString &keyName);
    IniFile& setValue(const QString &sectionName, const QString &keyName, const QString &value);
    void write(const QString &filename, QTextCodec *encoding) const;
    void writeModifiedOnly(QTextStream &stream) const;
};

QTextStream& operator << (QTextStream &stream, const IniFile &ini);

//=========================================================

class QTIRBIS_EXPORT IniLine {
private:
    bool modified;

public:
    QString key;
    QString value;

    IniLine(const QString &key="", const QString &line="");

    bool isModified() const;
    void notModified();
    void setKey(const QString &newKey);
    void setValue(const QString &newValue);
    QString toString() const;
};


QTextStream& operator << (QTextStream &stream, const IniLine &line);

//=========================================================

class QTIRBIS_EXPORT IniSection {
public:
    QString name;
    QList<IniLine> lines;

    IniSection(const QString &name="");

    IniSection& clear();
    bool containsKey(const QString &key) const;
    int getIndex(const QString &key) const;
    IniLine* getLine(const QString &key) const;
    const QString& getValue(const QString &key, const QString &defaultValue) const;
    bool isModified() const;
    void notModified();
    IniSection& removeValue(const QString &key);
    IniSection& setValue(const QString &key, const QString &value);
    QString toString() const;

    const QString& operator[] (const QString &index) const;
};

QTextStream& operator << (QTextStream &stream, const IniSection &section);

//=========================================================

class QTIRBIS_EXPORT IrbisConnection
{
public:
    static const qint32 MaxPacket = 32758;
    static const QString AdministratorDatabaseList;
    static const QString CatalogerDatabaseList;
    static const QString ReaderDatabaseList;
    static const qint32 ReadRecordCodes[];
    static const qint32 ReadTermsCodes[];

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

    void actualizeRecord(const QString database, int mfn);
    void connect();
    void createDatabase(const QString databaseName, const QString description, bool readerAccess);
    void createDictionary(const QString databaseName);
    void deleteDatabase(const QString databaseName);
    void deleteRecord(int mfn);
    void disconnect();
    ServerResponse execute(ClientQuery &query);
    void executeAndForget(ClientQuery &query);
    void executeAnsi(const QString &code);
    void executeAnsi(const QString &code, const QString &arg1);
    QString formatRecord(const QString &format, int mfn);
    QString formatRecord(const QString &format, MarcRecord &record);
    QStringList formatRecords(const QString &format, const QList<int> &mfns);
    DatabaseInfo getDatabaseInfo(const QString &databaseName);
    int getMaxMfn(const QString &databaseName);
    ServerStat getServerStat();
    IrbisVersion getServerVersion();
    QList<UserInfo> getUserList();
    QList<DatabaseInfo> listDatabases(const IniFile &iniFile, const QString &defaultFileName);
    QList<DatabaseInfo> listDatabases(const FileSpecification &specification);
    QStringList listFiles(const FileSpecification &specification);
    QStringList listFiles(const QList<FileSpecification> &specifications);
    QList<IrbisProcessInfo> listProcesses();
    QString monitorOperation(const QString &operation);
    void noOp();
    void parseConnectionString(const QString &connectionString);
    QString popDatabase();
    QString printTable(const TableDefinition &definition);
    QString pushDatabase(const QString &newDatabase);
    QByteArray readBinaryFile(const FileSpecification &specification);
    IniFile readIniFile(const FileSpecification &specification);
    MenuFile readMenuFile(const FileSpecification &specification);
    QList<TermPosting> readPostings(const PostingParameters &parameters);
    RawRecord readRawRecord(const QString &databaseName, qint32 mfn);
    MarcRecord readRecord(qint32 mfn);
    MarcRecord readRecord(const QString &databaseName, qint32 mfn);
    MarcRecord readRecord(const QString &databaseName, qint32 mfn, qint32 version);
    QList<SearchScenario> readSearchScenario(const FileSpecification &specification);
    QList<TermInfo> readTerms(const TermParameters &parameters);
    QString readTextFile(const FileSpecification &specification);
    QStringList readTextFiles(QList<FileSpecification> specifications);
    void reloadDictionary(const QString &databaseName);
    void reloadMasterFile(const QString &databaseName);
    void restartServer();
    QList<int> search(const QString &expression);
    QList<int> search(const SearchParameters &parameters);
    QString toConnectionString();
    void truncateDatabase(const QString &databaseName);
    void unlockDatabase(const QString &databaseName);
    void unlockRecords(const QString &databaseName, const QList<int> &mfnList);
    void updateIniFile(QStringList &lines);
    qint32 writeRecord(MarcRecord &record, bool lockFlag, bool actualize, bool dontParseResponse);
    void writeTextFile(const FileSpecification &specification);
};

//=========================================================

class QTIRBIS_EXPORT IrbisDate
{
public:
    QString text;
    QDateTime date;

    IrbisDate(const QString &text);
    IrbisDate(QDateTime date);

    static QDateTime convert(const QString &text);
    static QString convert(QDateTime date);
    static QString convert(QDate date);
    static QString today();
    static IrbisDate* safeParse(const QString &text);
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

class QTIRBIS_EXPORT IrbisException
        : public QException
{
public:
    qint32 code;

    IrbisException() : code(0) {}
    IrbisException(qint32 c) : code(c) {}
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

class QTIRBIS_EXPORT IrbisText {
public:
    const static char CrLf[];
    const static char Lf[];
    const static QString IrbisDelimiter;
    const static QString ShortDelimiter;
    const static QString MsDosDelimiter;
    const static QString UnixDelimiter;
    const static QString SearchDelimiter;

    static QString fromIrbisToDos(QString &text);
    static QString fromDosToIrbis(QString &text);
    static QString fromDosToUnix(QString &text);
    static QStringList fromFullDelimiter (const QString &text);
    static QStringList fromShortDelimiter (const QString &text);
    static QString readAllAnsi(const QString &filename);
    static QString readAllUtf(const QString &filename);
    static QStringList readAnsiLines(const QString &filename);
    static QStringList readUtfLines(const QString &filename);
};

//=========================================================

// информация о версии ИРБИС-сервера
class QTIRBIS_EXPORT IrbisVersion
{
public:
    QString organization; // на кого приобретен
    QString version; // собственно версия, например, 64.2008.1
    int maxClients; // максимальное количество подключений
    int connectedClients; // текущее количество подключений

    IrbisVersion();

    static IrbisVersion parse (ServerResponse &response);

    QString toString() const;
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

    MarcRecord();

    MarcRecord& add(qint32 tag);
    MarcRecord& add(qint32 tag, const QString &value);
    MarcRecord& clear();
    MarcRecord* clone() const;
    QString fm(qint32 tag) const;
    QString fm(qint32 tag, QChar code) const;
    QStringList fma(qint32 tag) const;
    QStringList fma(qint32 tag, QChar code) const;
    RecordField *getFirstField(qint32 tag) const;
    bool isDeleted() const;
    void parseSingle(QStringList &lines);

    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT MenuEntry {
public:
    QString code;
    QString comment;

    MenuEntry(const QString &code = "", const QString &comment = "");

    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT MenuFile {
public:
    const static QString StopMarker;
    const static QChar Separators[];

    QString fileName;
    QList<MenuEntry> entries;

    MenuFile();

    MenuFile& add(const QString &code, const QString &comment);
    MenuEntry* getEntry(const QString &code) const;
    MenuEntry* getEntrySensitive(const QString &code) const;
    QString* getValue(const QString &code) const;
    QString* getValueSensitive(const QString &code) const;
    const QString& getValue(const QString &code, const QString &defaultValue) const;
    const QString& getValueSensitive(const QString &code, const QString &defaultValue) const;
    static MenuFile parse(QTextStream &stream);
    static MenuFile parseLocalFile(const QString &filename, const QTextCodec *encoding);
};

//=========================================================

class QTIRBIS_EXPORT ProtocolText {
public:

    static const QString Delimiter;

    static void encode(QTextStream &stream, const SubField &subField);
    static void encode(QTextStream &stream, const RecordField &field);
    static void encode(QTextStream &stream, const MarcRecord &record);
    static QString encode(const MarcRecord &record);
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

    QString encode(const QString &delimiter) const;
    void parseSingle(const QStringList &lines);
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

    RecordField& add(QChar code, const QString &value);
    RecordField& clear();
    RecordField* clone() const;
    SubField* getFirstSubField(QChar code) const;
    QString getFirstSubFieldValue(QChar code) const;
    QList<SubField*> getSubField(QChar code) const;

    static RecordField* parse(const QString &line);

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

    static QList<SearchScenario> parse(const IniFile &iniFile);
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
    void checkReturnCode(const QVector<int> &allowed);
    void checkReturnCode(const qint32 *allowed);
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

class QTIRBIS_EXPORT ServerStat {
public:
    QList<ClientInfo> runningClients;
    qint32 clientCount;
    qint32 totalCommandCount;

    ServerStat();
    static ServerStat parse(ServerResponse &response);
};

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

    static QList<TermPosting> parse(ServerResponse &response);
    QString toString() const;
};

//=========================================================

class QTIRBIS_EXPORT TextNavigator {
private:
    qint32 _column, _length, _line, _position;
    const QString &_text;

public:

    const static QChar EOT;

    TextNavigator(const QString &text);
    TextNavigator(const TextNavigator &other);

    qint32 column() { return _column; }
    qint32 line() { return _line; }
    qint32 length() { return _length; }
    qint32 position() { return _position; }
    bool eot() const { return _position >= _length; }

    QChar charAt(qint32 position) const;
    QChar peekChar() const;
    QChar readChar();
    QString readLine();
    bool isControl() const;
    bool isDigit() const;
    bool isLetter() const;
    bool isWhitespace() const;
    QString readTo(QChar stopChar);
    QString readUntil(QChar stopChar);
    QString remainingText() const;
};

//=========================================================

class QTIRBIS_EXPORT UserInfo {
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

// Utilities

bool sameChar(QChar first, QChar second);
bool sameString(const QString &first, const QString &second);

qint32 fastParse32(const QString &text);
qint32 fastParse32(const char *text);
qint32 fastParse32(const char *text, qint32 length);

QString fastToString(qint32 value);

const QString& iif(const QString &s1, const QString &s2);
const QString& iif(const QString &s1, const QString &s2, const QString &s3);

QString itemAt(const QStringList &list, qint32 index);

QStringList maxSplit(const QString &text, QChar separator, qint32 count);
QStringList split(const QString &text, const QChar *separators);

//=========================================================

#endif // QTIRBIS_H
