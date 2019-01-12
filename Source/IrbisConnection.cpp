#include "QtIrbis.h"

//=========================================================

const QString IrbisConnection::AdministratorDatabaseList = "dbnam1.mnu";
const QString IrbisConnection::CatalogerDatabaseList = "dbnam2.mnu";
const QString IrbisConnection::ReaderDatabaseList = "dbnam3.mnu";

const qint32 IrbisConnection::ReadRecordCodes[] = { -201, -600, -602, -603, 0 };
const qint32 IrbisConnection::ReadTermsCodes[] = { -202, -203, -204, 0 };

IrbisConnection::IrbisConnection() :host("localhost"), port(6666),
    username(), password(), database("IBIS"), workstation('C'),
    clientId(0), queryId(0), isConnected(false), databaseStack() {
}

void IrbisConnection::actualizeRecord(QString database, int mfn) {
    ClientQuery query (this, CommandCode::ActualizeRecord);
    query.addAnsi(database);
    query.add(mfn);

    ServerResponse response = execute(query);
    response.checkReturnCode();
}

void IrbisConnection::connect() {
    if (isConnected) {
        return;
    }

    queryId = 0;
    clientId = 100000 + (rand() % 800000);
    ClientQuery query (this, CommandCode::RegisterClient);
    query.addAnsi(username);
    query.addAnsiNoLf(password);
    ServerResponse response = execute(query);
    response.checkReturnCode();
    isConnected = true;
}

void IrbisConnection::createDatabase(QString databaseName, QString description, bool readerAccess) {
    ClientQuery query (this, CommandCode::CreateDatabase);
    query.addAnsi(databaseName);
    query.addAnsi(description);
    query.add(readerAccess);

    ServerResponse response = execute(query);
    response.checkReturnCode();
}

void IrbisConnection::createDictionary(QString databaseName) {
    ClientQuery query (this, CommandCode::CreateDictionary);
    query.addAnsi(databaseName);

    ServerResponse response = execute(query);
    response.checkReturnCode();
}

void IrbisConnection::deleteDatabase(QString databaseName) {
    ClientQuery query (this, CommandCode::DeleteDatabase);
    query.addAnsi(databaseName);

    ServerResponse response = execute(query);
    response.checkReturnCode();
}

void IrbisConnection::deleteRecord(int mfn) {
    MarcRecord record = readRecord(mfn);
    if (!record.isDeleted()) {
        record.status |= RecordStatus::LogicallyDeleted;
        writeRecord(record, false, true, true);
    }
}

void IrbisConnection::disconnect() {
    if (!isConnected) {
        return;
    }

    ClientQuery query (this, CommandCode::UnregisterClient);
    query.addAnsiNoLf(username);
    executeAndForget(query);
}

ServerResponse IrbisConnection::execute(ClientQuery &query) {
    QTcpSocket *socket = new QTcpSocket;
    socket->connectToHost(host, port);
    socket->waitForConnected();
    socket->write(query.encode());
    ServerResponse result = ServerResponse(socket);

    return result;
}

void IrbisConnection::executeAndForget(ClientQuery &query) {
    execute(query).close();
}

void IrbisConnection::executeAnsi(QString code) {
    ClientQuery query (this, code);
    executeAndForget(query);
}

void IrbisConnection::executeAnsi(QString code, QString &arg1) {
    ClientQuery query (this, code);
    query.addAnsi(arg1);
    executeAndForget(query);
}

QString IrbisConnection::formatRecord(QString &format, int mfn) {
    ClientQuery query (this, CommandCode::FormatRecord);
    query.addAnsi(database)
        .addAnsi(format)
        .add(1)
        .add(mfn);

    ServerResponse response = execute(query);
    response.checkReturnCode();
    QString result = response.readRemainingUtfText();

    return result;
}

QString IrbisConnection::formatRecord(QString &format, MarcRecord &record) {
    QString prepared = IrbisFormat::prepareFormat(format);

    ClientQuery query (this, CommandCode::FormatRecord);
    query.addAnsi(database)
        .addAnsi(prepared)
        .add(-2)
        .add(record);

    ServerResponse response = execute(query);
    response.checkReturnCode();
    QString result = response.readRemainingUtfText();

    return result;
}

QStringList IrbisConnection::formatRecords(QString &format, QList<int> mfns) {
    if (mfns.isEmpty()) {
        return QStringList();
    }

    QString prepared = IrbisFormat::prepareFormat(format);

    ClientQuery query (this, CommandCode::FormatRecord);
    query.addAnsi(database)
        .addAnsi(prepared)
        .add(mfns.size());
    for (int mfn : mfns) {
        query.add(mfn);
    }

    ServerResponse response = execute(query);
    response.checkReturnCode();
    QStringList result = response.readRemainingUtfLines();

    return result;
}

DatabaseInfo IrbisConnection::getDatabaseInfo(QString &databaseName) {
    ClientQuery query(this, CommandCode::RecordList);
    query.addAnsi(databaseName);
    ServerResponse response = execute(query);
    response.checkReturnCode();
    DatabaseInfo result = DatabaseInfo::parse(response);

    return result;
}

int IrbisConnection::getMaxMfn(QString &databaseName) {
    ClientQuery query (this, CommandCode::GetMaxMfn);
    query.addAnsiNoLf(databaseName);
    ServerResponse response = execute(query);
    response.checkReturnCode();

    return response.returnCode;
}

ServerStat IrbisConnection::getServerStat() {
    ClientQuery query(this, CommandCode::GetServerStat);
    ServerResponse response = execute(query);
    response.checkReturnCode();
    ServerStat result = ServerStat::parse(response);

    return result;
}

IrbisVersion IrbisConnection::getServerVersion() {
    ClientQuery query(this, CommandCode::ServerInfo);

    ServerResponse response = execute(query);
    response.checkReturnCode();
    IrbisVersion result = IrbisVersion::parse(response);

    return result;
}

QList<UserInfo> IrbisConnection::getUserList() {
    ClientQuery query(this, CommandCode::GetUserList);

    ServerResponse response = execute(query);
    response.checkReturnCode();
    QList<UserInfo> result = UserInfo::parse(response);

    return result;
}

QList<DatabaseInfo> IrbisConnection::listDatabases(IniFile &iniFile, QString defaultFileName) {
    // TODO implement

    QList<DatabaseInfo> result;

    return result;
}

QList<DatabaseInfo> IrbisConnection::listDatabases(FileSpecification &specification) {
    MenuFile menuFile = readMenuFile(specification);
    QList<DatabaseInfo> result = DatabaseInfo::parse(menuFile);

    return result;
}

QStringList IrbisConnection::listFiles(FileSpecification &specification) {
    ClientQuery query(this, CommandCode::ListFiles);
    query.add(specification);

    ServerResponse response = execute(query);
    QStringList result = response.readRemainingAnsiLines();
    // TODO split from delimiters

    return result;
}

QStringList IrbisConnection::listFiles(QList<FileSpecification> specifications) {
    if (specifications.empty()) {
        return QStringList();
    }

    ClientQuery query (this, CommandCode::ListFiles);
    for (FileSpecification specification : specifications) {
        query.add(specification);
    }

    ServerResponse response = execute(query);
    QStringList result = response.readRemainingAnsiLines();

    return result;
}

QList<IrbisProcessInfo> IrbisConnection::listProcesses() {
    ClientQuery query (this, CommandCode::GetProcessList);

    ServerResponse response = execute(query);
    response.checkReturnCode();
    QList<IrbisProcessInfo> result = IrbisProcessInfo::parse(response);

    return result;
}

QString IrbisConnection::monitorOperation(QString operation) {
    QString clientId = fastToString(this->clientId);

    while (true) {
        bool found = false;
        QList<IrbisProcessInfo> processes = listProcesses();
        for (IrbisProcessInfo process : processes) {
            if (process.clientId == clientId
               && process.lastCommand == operation) {
                found = true;
            }
        }
        if (!found) {
            break;
        }
        QThread::sleep(1000);
    }

    QString filename = clientId + ".ibf";
    FileSpecification specification(IrbisPath::System, "", filename);
    QString result = readTextFile(specification);

    return result;
}

void IrbisConnection::noOp() {
    executeAnsi(CommandCode::Nop);
}

void IrbisConnection::parseConnectionString(QString &connectionString) {
    QStringList items = connectionString.split(";");
    for (QString item : items) {
        QStringList parts = item.split("="); // TODO: 2
        if (parts.length() != 2) {
            throw IrbisException();
        }
        QString name = parts[0].trimmed().toLower();
        QString value = parts[1].trimmed();
        if (name.isEmpty() || value.isEmpty()) {
            throw IrbisException();
        }

        if (name == "host" || name == "server" || name == "address") {
            host = value;
        }
        else if (name == port) {
            port = static_cast<quint16>(fastParse32(value));
        }
        else if (name == "user" || name == "username"
                 || name == "name" || name == "login") {
            username = value;
        }
        else if (name == "pwd" || name == "password") {
            password = value;
        }
        else if (name == "db" || name == "catalog" || name == "database") {
            database = value;
        }
        else if (name == "arm" || name == "workstation") {
            workstation = value.at(0);
        }
        else {
            throw IrbisException();
        }
    }
}

QString IrbisConnection::popDatabase() {
    QString result = database;
    database = databaseStack.takeLast();

    return result;
}

QString IrbisConnection::printTable(TableDefinition &definition) {
    // TODO implement

    QString result;

    return result;
}

QString IrbisConnection::pushDatabase(QString newDatabase) {
    QString result = database;
    databaseStack.push_back(newDatabase);
    database = newDatabase;

    return result;
}

QByteArray IrbisConnection::readBinaryFile(FileSpecification &specification) {
    // TODO specification.isBinaryFile = true;
    ClientQuery query(this, CommandCode::ReadDocument);
    query.add(specification);
    ServerResponse response = execute(query);
    QByteArray result = response.getBinaryFile();

    return result;
}

IniFile IrbisConnection::readIniFile(FileSpecification &specification) {
    QString text = readTextFile(specification);
    QTextStream stream(&text);
    IniFile result = IniFile::parse(stream);

    return result;
}

MenuFile IrbisConnection::readMenuFile(FileSpecification &specification) {
    QString text = readTextFile(specification);
    QTextStream stream(&text);
    MenuFile result = MenuFile::parse(stream);

    return result;
}

QList<TermPosting> IrbisConnection::readPostings(PostingParameters &parameters) {
    // TODO implement

    QList<TermPosting> result;

    return result;
}

RawRecord IrbisConnection::readRawRecord(QString &databaseName, qint32 mfn) {
    // TODO implement

    RawRecord result;

    return result;
}

MarcRecord IrbisConnection::readRecord(qint32 mfn) {
    return readRecord(database, mfn);
}

MarcRecord IrbisConnection::readRecord(QString &databaseName, qint32 mfn) {
    ClientQuery query(this, CommandCode::ReadRecord);
    query.addAnsi(databaseName)
        .add(mfn);

    ServerResponse response = execute(query);
    response.checkReturnCode(); // TODO add allowed codes
    QStringList lines = response.readRemainingUtfLines();
    MarcRecord result;
    result.parseSingle(lines);
    result.database = databaseName;

    return result;
}

MarcRecord IrbisConnection::readRecord(QString &databaseName, qint32 mfn, qint32 version) {
    ClientQuery query(this, CommandCode::ReadRecord);
    query.addAnsi(databaseName)
        .add(mfn)
        .add(version);

    ServerResponse response = execute(query);
    response.checkReturnCode(); // TODO add allowed codes
    QStringList lines = response.readRemainingUtfLines();
    MarcRecord result;
    result.parseSingle(lines);
    result.database = databaseName;
    // TODO unlock the record

    return result;
}

QList<SearchScenario> IrbisConnection::readSearchScenario(FileSpecification &specification) {
    IniFile iniFile = readIniFile(specification);
    QList<SearchScenario> result = SearchScenario::parse(iniFile);

    return result;
}

QString IrbisConnection::readTextFile(FileSpecification &specification) {
    ClientQuery query(this, CommandCode::ReadDocument);
    query.add(specification);

    ServerResponse response = execute(query);
    QString result = response.readAnsi();
    // TODO result = IrbisText::fromIrbisToDos(result);

    return result;
}

QStringList IrbisConnection::readTextFiles(QList<FileSpecification> specifications) {
    ClientQuery query(this, CommandCode::ReadDocument);
    for (FileSpecification specification : specifications) {
        query.add(specification);
    }

    ServerResponse response = execute(query);
    QStringList result;
    while (true) {
        // TODO FIX ME!

        QString text = response.readAnsi();
        if (text.isEmpty()) {
            break;
        }

        // TODO text = IrbisText::fromIrbisToDos(text);
        result.append(text);
    }

    return result;
}

void IrbisConnection::reloadDictionary(QString &databaseName) {
    executeAnsi(CommandCode::ReloadDictionary, databaseName);
}

void IrbisConnection::reloadMasterFile(QString &databaseName) {
    executeAnsi(CommandCode::ReloadMasterFile, databaseName);
}

void IrbisConnection::restartServer() {
    executeAnsi(CommandCode::RestartServer);
}

QList<int> IrbisConnection::search(QString &expression) {
    SearchParameters parameters;
    parameters.database = database;
    parameters.searchExpression = expression;
    parameters.numberOfRecords = 0;
    parameters.firstRecord = 1;

    return search(parameters);
}

QList<int> IrbisConnection::search(SearchParameters &parameters) {
    QString &databaseName = iif(parameters.database, database);
    ClientQuery query (this, CommandCode::Search);
    query.addAnsi(databaseName);
    query.addUtf(parameters.searchExpression);
    query.add(parameters.numberOfRecords);
    query.add(parameters.firstRecord);
    query.addAnsi(parameters.formatSpecification);
    query.add(parameters.minMfn);
    query.add(parameters.maxMfn);
    query.addAnsi(parameters.sequentialSpecification);

    ServerResponse response = execute(query);
    response.checkReturnCode();
    int expected = response.readInt32();
    int batchSize = qMin(expected, 32000); // MAXPACKET
    QList<int> result;
    for (int i = 0; i < batchSize; i++) {
        QString line = response.readAnsi();
        QStringList parts = line.split("#"); // 2
        qint32 mfn = fastParse32(parts[0]);
        result.append(mfn);
    }

    return result;
}

QString IrbisConnection::toConnectionString() {
    return QString("host=") + host
           + ";port=" + fastToString(port)
           + ";username=" + username
           + ";password=" + password
           + ";database" + database
           + ";arm=" + workstation
           + ";";
}


void IrbisConnection::truncateDatabase(QString &databaseName) {
    executeAnsi(CommandCode::EmptyDatabase, databaseName);
}

void IrbisConnection::unlockDatabase(QString &databaseName) {
    executeAnsi(CommandCode::UnlockDatabase, databaseName);
}

void IrbisConnection::unlockRecords(QString &databaseName, QList<int> mfnList) {
    if (mfnList.empty()) {
        return;
    }

    ClientQuery query (this, CommandCode::UnlockRecords);
    query.addAnsi(databaseName);
    for (int mfn : mfnList) {
        query.add(mfn);
    }

    executeAndForget(query);
}

void IrbisConnection::updateIniFile(QStringList &lines) {
    if (lines.empty()) {
        return;
    }

    ClientQuery query(this, CommandCode::UpdateIniFile);
    for (QString &line : lines) {
        query.addAnsi(line);
    }

    executeAndForget(query);
}

qint32 IrbisConnection::writeRecord(MarcRecord &record) {
    return writeRecord(record, false, true, false);
}

qint32 IrbisConnection::writeRecord(MarcRecord &record, bool lockFlag, bool actualize, bool dontParseResponse) {
    QString databaseName = iif(record.database, database);
    ClientQuery query(this, CommandCode::UpdateRecord);
    query.addAnsi(databaseName)
        .add(lockFlag)
        .add(actualize)
        .add(record);

    ServerResponse response = execute(query);
    response.checkReturnCode();

    if (!dontParseResponse) {
        record.fields.clear();

        // TODO implement
    }

    return response.returnCode;
}

void IrbisConnection::writeTextFile(FileSpecification &specification) {
    ClientQuery query(this, CommandCode::ReadDocument);
    query.add(specification);
    executeAndForget(query);
}

