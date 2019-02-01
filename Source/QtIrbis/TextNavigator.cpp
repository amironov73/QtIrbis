// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

const QChar TextNavigator::EOT = '\0';

TextNavigator::TextNavigator(const QString &text)
    : _text(text) {
    _position = 0;
    _length = _text.length();
    _line = 1;
    _column = 1;
}

TextNavigator::TextNavigator(const TextNavigator &other)
    : _text(other._text) {
    _position = other._position;
    _length = other._length;
    _line = other._line;
    _column = other._column;
}

QChar TextNavigator::charAt(qint32 position) const {
    return (position >= 0) && (position < _length) ? _text[position] : EOT;
}

QChar TextNavigator::peekChar() const {
    return _position >= _length ? EOT : _text[_position];
}

QChar TextNavigator::readChar() {
    if (_position >= _length) {
        return EOT;
    }

    QChar result = _text[_position++];
    if (result == '\n') {
        _line++;
        _column = 1;
    } else {
        _column++;
    }

    return result;
}

QString TextNavigator::readLine() {
    QString result;
    if (_position >= _length) {
        return result;
    }

    int start = _position;
    while (_position < _length) {
        QChar c = _text[_position];
        if (c == '\r' || c == '\n') {
            break;
        }

        readChar();
    }

    result = _text.mid(start, _position - start);
    if (_position < _length) {
        QChar c = _text[_position];
        if (c == '\r') {
            readChar();
            c = peekChar();
        }

        if (c == '\n') {
            readChar();
        }
    }

    return result;
}

bool TextNavigator::isControl() const {
    QChar c = peekChar();

    return (c.unicode() > 0) && (c < ' ');
}

bool TextNavigator::isDigit() const {
    return peekChar().isDigit();
}

bool TextNavigator::isLetter() const {
    return peekChar().isLetter();
}

bool TextNavigator::isWhitespace() const {
    return peekChar().isSpace();
}

// Считывание вплоть до указанного символа
// (не включая его, однако, символ считывается).
QString TextNavigator::readTo(QChar stopChar) {
    QString result;

    if (eot()) {
        return result;
    }

    int start = _position, end = _position;
    while (true) {
        QChar c = readChar();
        if ((c == EOT) || (c == stopChar)) {
            break;
        }
        end = _position;
    }

    result = _text.mid(start, end - start);

    return result;
}

// Считывание вплоть до указанного символа
// (сам символ остается несчитанным).
QString TextNavigator::readUntil(QChar stopChar) {
    QString result;

    if (eot()) {
        return result;
    }

    int start = _position;
    while (true) {
        QChar c = peekChar();
        if ((c == EOT) || (c == stopChar)) {
            break;
        }

        readChar();
    }

    result = _text.mid(start, _position - start);

    return result;
}

QString TextNavigator::remainingText() const {
    if (eot()) {
        return QString();
    }

    return _text.mid(_position);
}

QChar TextNavigator::lookAhead(qint32 distance) const {
    qint32 newPosition = _position + distance;

    return charAt(newPosition);
}

QChar TextNavigator::lookBehind(qint32 distance) const {
    qint32 newPosition = _position - distance;

    return charAt(newPosition);
}

TextNavigator& TextNavigator::move(qint32 distance) {
    // TODO Some checks

    _position += distance;
    _column += distance;

    return *this;
}

QString TextNavigator::peekString(qint32 length) {
    QString result;

    if (eot()) {
        return result;
    }

    qint32 savePosition = _position, saveColumn = _column, saveLine = _line;
    for (qint32 i = 0; i < length; ++i) {
        QChar c = readChar();
        if ((c == EOF) || (c == '\r') || (c == '\n')) {
            break;
        }

        result.append(c);
    }

    _position = savePosition;
    _column = saveColumn;
    _line = saveLine;

    return result;
}

QString TextNavigator::peekTo(QChar stopChar) {
    QString result;

    if (eot()) {
        return result;
    }

    qint32 savePosition = _position, saveColumn = _column, saveLine = _line;
    result = readTo(stopChar);
    _position = savePosition;
    _column = saveColumn;
    _line = saveLine;

    return result;
}

QString TextNavigator::peekUntil(QChar stopChar) {
    QString result;

    if (eot()) {
        return result;
    }

    qint32 savePosition = _position, saveColumn = _column, saveLine = _line;
    result = readUntil(stopChar);
    _position = savePosition;
    _column = saveColumn;
    _line = saveLine;

    return result;
}

QString TextNavigator::readInteger() {
    QString result;

    if (isDigit()) {
        while (isDigit()) {
            result.append(readChar());
        }
    }

    return result;
}

QString TextNavigator::readString(qint32 length) {
    QString result;

    if (eot()) {
        return result;
    }

    result.reserve(length);
    for (qint32 i = 0; i < length; ++i) {
        QChar c = readChar();
        if (c == EOT) {
            break;
        }

        result.append(c);
    }

    return result;
}

QString TextNavigator::readWhile(QChar goodChar) {
    QString result;

    while (true) {
        QChar c = peekChar();
        if ((c == EOT) || (c != goodChar)) {
            break;
        }

        result.append(readChar());
    }

    return result;
}

QString TextNavigator::readWord() {
    QString result;

    while (true) {
        QChar c = peekChar();
        if ((c == EOT) || !c.isLetterOrNumber()) {
            break;
        }

        result.append(readChar());
    }

    return result;
}

QString TextNavigator::recentText(qint32 length) const {
    qint32 start = _position - length;
    if (start < 0) {
        length += start;
        start = 0;
    }

    if (start >= _length) {
        start = 0;
        length = 0;
    }

    if (length < 0) {
        length = 0;
    }

    return _text.mid(start, length);
}

TextNavigator& TextNavigator::skipWhitespace() {
    while (true) {
        QChar c = peekChar();
        if (!c.isSpace()) {
            break;
        }
        readChar();
    }

    return *this;
}

TextNavigator& TextNavigator::skipPunctuation() {
    while (true) {
        QChar c = peekChar();
        if (!c.isPunct()) {
            break;
        }
        readChar();
    }

    return *this;
}

QString TextNavigator::mid(qint32 offset, qint32 length) const {
    return _text.mid(offset, length);
}

