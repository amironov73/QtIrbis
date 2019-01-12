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

