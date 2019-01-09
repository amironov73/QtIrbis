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
    IrbisFormat.cpp

HEADERS += QtIrbis.h
