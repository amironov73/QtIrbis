// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

NumberText::NumberText() : _chunks() {
}

NumberText::NumberText(const NumberText &other) : _chunks(other._chunks) {
}

NumberText::NumberText(const QString &text) : NumberText() {
    parse(text);
}

NumberChunk* NumberText::at(int index) const {
    if (index < 0) {
        return nullptr;
    }

    auto iter = _chunks.begin();
    while (index > 0) {
        if (iter == _chunks.end()) {
            return nullptr;
        }

        --index;
        ++iter;
    }

    return const_cast<NumberChunk*>(&*iter);
}

NumberChunk* NumberText::lastChunk() const {
    if (_chunks.isEmpty()) {
        return nullptr;
    }

    return const_cast<NumberChunk*>(&_chunks.last());
}

NumberText& NumberText::append(const QString &prefix, bool haveValue, qint64 value, qint32 length) {
    NumberChunk chunk;
    chunk.prefix = prefix;
    chunk.value = value;
    chunk.haveValue = haveValue;
    chunk.length = length;
    _chunks.append(chunk);

    return *this;
}

QString NumberText::getPrefix(int index) const {
    auto chunk = at(index);

    return chunk ? chunk->prefix : QString();
}

qint64 NumberText::getValue(int index) const {
    auto chunk = at(index);

    return chunk ? chunk->value : 0;
}

NumberText& NumberText::increment(int delta) {
    auto chunk = lastChunk();
    if (chunk) {
        chunk->value += delta;
    }

    return *this;
}

NumberText& NumberText::increment(int index, int delta) {
    auto chunk = at(index);
    if (chunk) {
        chunk->value += delta;
    }

    return *this;
}

NumberText& NumberText::parse(const QString &text) {
    _chunks.clear();
    if (text.isEmpty()) {
        return *this;
    }

    TextNavigator navigator(text);
    _chunks.append(NumberChunk());
    bool textPart(true);
    QString str, number;
    while (!navigator.eot())
    {
        QChar c = navigator.readChar();
        if (textPart)
        {
            if (c.isDigit())
            {
                number.append(c);
                textPart = false;
            }
            else
            {
                str.append(c);
            }
        }
        else
        {
            if (c.isDigit())
            {
                number.append(c);
            }
            else
            {
                NumberChunk &chunk = _chunks.last();
                chunk.setUp(str, number);
                _chunks.append(NumberChunk());
                str.clear();
                str.append(c);
                number.clear();
                textPart = true;
            }
        }
    }

    NumberChunk &chunk = _chunks.last();
    if (!chunk.setUp(str, number))
    {
        _chunks.removeLast();
    }

    return *this;
}

qint32 NumberText::size() const {
    return _chunks.size();
}

QString NumberText::toString() const {
    QString result;
    for(const NumberChunk &chunk : _chunks) {
        result += chunk.toString();
    }

    return result;
}

