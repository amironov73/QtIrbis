CONFIG += c++14

QT += network xml
QT -= gui widgets

TARGET = QtIrbis

TEMPLATE = lib

DEFINES += QTIRBIS_LIBRARY

SOURCES += QtIrbis.cpp \
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
    RecordSerializer.cpp

HEADERS += QtIrbis.h

PRECOMPILED_HEADER = QtIrbis.h
