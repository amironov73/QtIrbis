// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::fastParse32;

//=========================================================

// Преамбула двоичного файла
char ServerResponse::preamble[] = {
    0x49, 0x52, 0x42, 0x49, 0x53, 0x5F, 0x42, 0x49, 0x4E, 0x41, 0x52,
    0x59, 0x5F, 0x44, 0x41, 0x54, 0x41
};

ServerResponse::ServerResponse(QTcpSocket *socket) {
    this->socket = socket;
    data = socket->readAll();
    length = data.size();
    position = 0;
    closed = false;
    savedSymbol = 0;

    command = readAnsi();
    clientId = readInt32();
    queryId = readInt32();
    returnCode = 0;
    for (int i = 0; i < 7; i++) {
        readAnsi();
    }
}

ServerResponse::~ServerResponse() {
    close();
    if (socket != nullptr) {
        delete socket;
        socket = nullptr;
    }
}

int ServerResponse::read() {
    if (position >= length) {
        return -1;
    }

    int result = data.at(position++);

    return result;
}

void ServerResponse::checkReturnCode() {
    qint32 rc = getReturnCode();
    if (rc < 0) {
        throw IrbisException(rc);
    }
}

void ServerResponse::checkReturnCode(qint32 allowed) {
    qint32 rc = getReturnCode();
    if ((rc < 0) && (rc != allowed)) {
        throw IrbisException(rc);
    }
}

void ServerResponse::checkReturnCode(const QVector<qint32> &allowed) {
    qint32 rc = getReturnCode();
    if ((rc < 0) && !allowed.contains(rc)) {
        throw IrbisException(rc);
    }
}

void ServerResponse::checkReturnCode(const qint32 *allowed) {
    qint32 rc = getReturnCode();
    if (rc < 0) {
        while (*allowed != rc) {
            if (*allowed == 0) {
                break;
            }
            allowed++;
        }
    }
}

void ServerResponse::close() {
    if (!closed) {
        socket->close();
        closed = true;
    }
}

QByteArray ServerResponse::getBinaryFile() {
    qint32 index = data.indexOf(preamble, preambleLength);
    if (index < 0) {
        return QByteArray();
    }

    const char *ptr = data.constData() + index;
    int count = length - index;
    QByteArray result (ptr, count);

    return result;
}

QByteArray ServerResponse::getLine() {
    QByteArray result;

    while (true) {
        int one;

        if (savedSymbol >= 0) {
            one = savedSymbol;
            savedSymbol = -1;
        } else {
            one = read();
        }

        if (one == 0x0D) {
            one = read();
            if (one == 0x0A) {
                break;
            } else {
                savedSymbol = one;
            }
        } else {
            result.append(static_cast<char>(one));
        }
    }

    return result;
}

int ServerResponse::getReturnCode() {
    returnCode = readInt32();

    return returnCode;
}

QString ServerResponse::readAnsi() {
    QByteArray line = getLine();
    QString result = IrbisEncoding::ansi()->toUnicode(line);

    return result;
}

QStringList ServerResponse::readAnsi(qint32 count) {
    QStringList result;
    for (int i = 0; i < count; ++i) {
        QString line = readAnsi();
        if (line.isEmpty()) {
            return QStringList();
        }

        result.append(line);
    }

    return result;
}

qint32 ServerResponse::readInt32() {
    QString text = readAnsi();
    qint32 result = fastParse32(text);

    return result;
}

QStringList ServerResponse::readRemainingAnsiLines() {
    QStringList result;
    while (true) {
        QString line = readAnsi();
        if (line.isEmpty()){
            break;
        }

        result.append(line);
    }

    return result;
}

QString ServerResponse::readRemainingAnsiText() {
    int count = length - position;
    const char *ptr = data.constData();
    QString result = IrbisEncoding::ansi()->toUnicode(ptr, count);

    return result;
}

QStringList ServerResponse::readRemainingUtfLines() {
    QStringList result;
    while (true) {
        QString line = readUtf();
        if (line.isEmpty()){
            break;
        }

        result.append(line);
    }

    return result;
}

QString ServerResponse::readRemainingUtfText() {
    int count = length - position;
    const char *ptr = data.constData();
    QString result = IrbisEncoding::utf()->toUnicode(ptr, count);

    return result;
}

QString ServerResponse::readUtf() {
    QByteArray line = getLine();
    QString result = IrbisEncoding::utf()->toUnicode(line);

    return result;
}

QStringList ServerResponse::readUtf(int count) {
    QStringList result;
    for (int i = 0; i < count; ++i) {
        QString line = readAnsi();
        if (line.isEmpty()) {
            return QStringList();
        }

        result.append(line);
    }

    return result;
}


