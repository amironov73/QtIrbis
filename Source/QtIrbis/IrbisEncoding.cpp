// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

QTextCodec* IrbisEncoding::_ansi = nullptr;
QTextCodec* IrbisEncoding::_utf = nullptr;

QTextCodec* IrbisEncoding::ansi() {
    if (!_ansi) {
        _ansi = QTextCodec::codecForName("windows-1251");
    }

    return _ansi;
}

QString IrbisEncoding::fromAnsi(const QByteArray &bytes) {
    return ansi()->toUnicode(bytes);
}

QString IrbisEncoding::fromUtf(const QByteArray &bytes) {
    return utf()->toUnicode(bytes);
}

QByteArray IrbisEncoding::toAnsi(const QString &text) {
    return ansi()->fromUnicode(text);
}

QByteArray IrbisEncoding::toUtf(const QString &text) {
    return utf()->fromUnicode(text);
}

QTextCodec* IrbisEncoding::utf() {
    if (!_utf) {
        _utf = QTextCodec::codecForName("UTF-8");
    }

    return _utf;
}

