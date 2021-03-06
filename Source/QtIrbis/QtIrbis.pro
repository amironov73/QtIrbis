CONFIG += c++14

QT += network xml
QT -= gui widgets

TARGET = QtIrbis

TEMPLATE = lib

DEFINES += QTIRBIS_LIBRARY

SOURCES += QtIrbis.cpp \
    Builder.cpp \
    SubField.cpp \
    RecordField.cpp \
    MarcRecord.cpp \
    ClientQuery.cpp \
    IrbisConnection.cpp \
    ServerResponse.cpp \
    FileSpecification.cpp \
    ClientInfo.cpp \
    IrbisProcessInfo.cpp \
    DatabaseInfo.cpp \
    IrbisEncoding.cpp \
    IrbisFormat.cpp \
    CommandCode.cpp \
    UserInfo.cpp \
    ServerStat.cpp \
    MenuFile.cpp \
    FoundLine.cpp \
    PostingParameters.cpp \
    SearchParameters.cpp \
    SearchScenario.cpp \
    TermInfo.cpp \
    TermParameters.cpp \
    TermPosting.cpp \
    MenuEntry.cpp \
    RawRecord.cpp \
    IniFile.cpp \
    IrbisVersion.cpp \
    IrbisText.cpp \
    EmbeddedField.cpp \
    TextNavigator.cpp \
    ProtocolText.cpp \
    IrbisDate.cpp \
    Iso2709.cpp \
    IrbisException.cpp \
    IrbisTreeFile.cpp \
    IrbisTreeNode.cpp \
    StopWords.cpp \
    NumberChunk.cpp \
    NumberText.cpp \
    RecordSerializer.cpp \
    ConnectionFactory.cpp \
    IlfEntry.cpp \
    IlfFile.cpp \
    ChunkedBuffer.cpp \
    MemoryChunk.cpp \
    XrfRecord64.cpp \
    XrfFile64.cpp \
    MstRecord64.cpp \
    MstRecordLeader64.cpp \
    MstDictionaryEntry64.cpp \
    MstFile64.cpp \
    MstControlRecord64.cpp \
    DirectAccess64.cpp \
    AlphabetTable.cpp \
    IrbisFileNotFoundException.cpp \
    IrbisResource.cpp \
    ResourceDictionary.cpp

HEADERS += QtIrbis.h

PRECOMPILED_HEADER = QtIrbis.h
