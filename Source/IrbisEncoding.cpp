#include "QtIrbis.h"

//=========================================================

QTextCodec* IrbisEncoding::_ansi = nullptr;
QTextCodec* IrbisEncoding::_utf = nullptr;

QTextCodec* IrbisEncoding::ansi() {
    if (!_ansi) {
        _ansi = QTextCodec::codecForName("Windows-1251");
    }

    return _ansi;
}

QTextCodec* IrbisEncoding::utf() {
    if (!_utf) {
        _utf = QTextCodec::codecForName("UTF-8");
    }

    return _utf;
}
