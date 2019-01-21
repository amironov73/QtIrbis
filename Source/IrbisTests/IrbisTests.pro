QT += network widgets testlib

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  AllTests.cpp \
    SubFieldTest.cpp \
    RecordFieldTest.cpp \
    MarcRecordTest.cpp \
    ClientQueryTest.cpp \
    FileSpecificationTest.cpp \
    IrbisDateTest.cpp \
    IrbisEncodingTest.cpp \
    IrbisFormatTest.cpp \
    TextNavigatorTest.cpp \
    StopWordsTest.cpp \
    CommonTest.cpp

HEADERS += IrbisTests.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtIrbis/release/ -lQtIrbis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtIrbis/debug/ -lQtIrbis

INCLUDEPATH += $$PWD/../QtIrbis
DEPENDPATH += $$PWD/../QtIrbis
