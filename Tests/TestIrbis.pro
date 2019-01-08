QT += widgets testlib

INCLUDEPATH += ../Source

SOURCES += TestIrbis.cpp

LIBS += -L../Source/release -lQtIrbis
