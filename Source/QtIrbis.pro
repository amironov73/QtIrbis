QT += network xml

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
    IrbisDate.cpp

HEADERS += QtIrbis.h
