// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

const int ChunkedBuffer::DefaultChunkSize = 2048;

ChunkedBuffer::ChunkedBuffer(qint32 chunkSize)
    : _first(nullptr), _current(nullptr), _last(nullptr),
      _chunkSize(chunkSize), _position(0), _read(0) {
}

ChunkedBuffer::~ChunkedBuffer() {
    MemoryChunk *chunk = _first;
    while (chunk) {
        MemoryChunk *next = chunk->next;
        chunk->~MemoryChunk();
        chunk = next;
    }
}

bool ChunkedBuffer::_advance() {
    if (_current == _last) {
        return false;
    }

    _current = _current->next;
    _read = 0;

    return true;
}

void ChunkedBuffer::_appendChunk() {
    MemoryChunk *newChunk = new MemoryChunk(_chunkSize);
    if (_first) {
        _last->next = newChunk;
    } else {
        _first = newChunk;
        _current = newChunk;
    }

    _last = newChunk;
    _position = 0;
}

bool ChunkedBuffer::eof() const {
    if (!_current) {
        return true;
    }

    if (_current == _last) {
        return _read >= _position;
    }

    return false;
}

qint32 ChunkedBuffer::peek() {
    if (!_current) {
        return -1;
    }

    if (_current == _last) {
        if (_read >= _position) {
            return -1;
        }
    } else {
        if (_read >= _chunkSize) {
            _advance();
        }
    }

    return _current->data[_read];
}

qint32 ChunkedBuffer::read(char *buffer, qint32 offset, qint32 count) {
    if (count <= 0) {
        return 0;
    }

    if (!_current) {
        return 0;
    }

    qint32 total = 0;
    do {
        qint32 remaining = _current == _last
                ? _position - _read
                : _chunkSize - _read;

        if (remaining <= 0) {
            if (!_advance()) {
                break;
            }
        }

        qint32 portion = qMin(count, remaining);
        memcpy(buffer + offset, _current->data + _read, static_cast<size_t>(portion));
        _read += portion;
        count -= portion;
        total += portion;
    } while (count > 0);

    return total;
}

qint32 ChunkedBuffer::readByte() {
    if (!_current) {
        return -1;
    }

    if (_current == _last) {
        if (_read >= _position) {
            return -1;
        }
    } else {
        if (_read >= _chunkSize) {
            _advance();
        }
    }

    return _current->data[_read++];
}

QString ChunkedBuffer::readLine(QTextCodec *codec) {
    if (eof()) {
        return QString::null;
    }

    QByteArray array;
    char found = 0;
    while (found == 0) {
        char *buffer = reinterpret_cast<char*>(_current->data);
        qint32 stop = _current == _last ? _position : _chunkSize;
        qint32 head = _read;
        for (; head < stop; head++) {
            char c = buffer[head];
            if ((c == '\r') || (c == '\n')) {
                found = c;
                break;
            }
        }

        array.append(buffer + _read, head - _read);
        _read = head;

        if (found != 0) {
            _read++;
        }
        else {
            if (!_advance()) {
                break;
            }
        }
    }

    if (found == '\r') {
        if (peek() == '\n') {
            readByte();
        }
    }

    return codec->toUnicode(array);
}

void ChunkedBuffer::rewind() {
    _current = _first;
    _read = 0;
}

void ChunkedBuffer::write(const char *buffer, qint32 offset, qint32 count) {
    if (count <= 0) {
        return;
    }

    if (!_first) {
        _appendChunk();
    }

    do {
         qint32 free = _chunkSize - _position;
         if (!free) {
             _appendChunk();
             free = _chunkSize;
         }

         qint32 portion = qMin(count, free);
         memcpy(_last->data + _position, buffer + offset, static_cast<size_t>(portion));
         _position += portion;
         count -= portion;
         offset += portion;
    } while (count > 0);
}

void ChunkedBuffer::write(const QString &text, QTextCodec *codec) {
    QByteArray bytes = codec->fromUnicode(text);
    write(bytes.data(), 0, bytes.length());
}

void ChunkedBuffer::writeByte(quint8 value) {
    if (!_first) {
        _appendChunk();
    }

    if (_position >= _chunkSize) {
        _appendChunk();
    }

    _last->data[_position++] = value;
}

