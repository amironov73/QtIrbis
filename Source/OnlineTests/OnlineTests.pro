QT += network
QT -= gui

CONFIG += c++14 qt console warn_on depend_includepath
CONFIG -= app_bundle

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtIrbis/release/ -lQtIrbis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtIrbis/debug/ -lQtIrbis
else:unix:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QtIrbis/ -lQtIrbis
else:unix:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QtIrbis/ -lQtIrbis

INCLUDEPATH += $$PWD/../QtIrbis
DEPENDPATH += $$PWD/../QtIrbis
