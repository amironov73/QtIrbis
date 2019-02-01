// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::fastParse32;

//=========================================================

const QString AlphabetTable::FileName = "ISISACW.TAB";

AlphabetTable::AlphabetTable(const QByteArray &bytes, QTextCodec *encoding)
    : characters() {
    QString text = encoding->toUnicode(bytes);
    for (qint32 i = 0; i < text.length(); ++i) {
        characters << text.at(i);
    }
}

static unsigned char _bytes[] =
{
     38,  64,  65,  66,  67,  68,  69,  70,  71,  72,
     73,  74,  75,  76,  77,  78,  79,  80,  81,  82,
     83,  84,  85,  86,  87,  88,  89,  90,  97,  98,
     99, 100, 101, 102, 103, 104, 105, 106, 107, 108,
    109, 110, 111, 112, 113, 114, 115, 116, 117, 118,
    119, 120, 121, 122, 128, 129, 130, 131, 132, 133,
    134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
    144, 145, 146, 147, 148, 149, 150, 151, 152, 153,
    154, 155, 156, 157, 158, 159, 160, 161, 162, 163,
    164, 165, 166, 167, 168, 169, 170, 171, 172, 173,
    174, 175, 176, 177, 178, 179, 180, 181, 182, 183,
    184, 185, 186, 187, 188, 189, 190, 191, 192, 193,
    194, 195, 196, 197, 198, 199, 200, 201, 202, 203,
    204, 205, 206, 207, 208, 209, 210, 211, 212, 213,
    214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
    224, 225, 226, 227, 228, 229, 230, 231, 232, 233,
    234, 235, 236, 237, 238, 239, 240, 241, 242, 243,
    244, 245, 246, 247, 248, 249, 250, 251, 252, 253,
    254, 255
};

static AlphabetTable *_instance;

const AlphabetTable& AlphabetTable::instance() {
    if (!_instance) {
        QByteArray bytes(reinterpret_cast<char*>(_bytes), sizeof(_bytes));
        _instance = new AlphabetTable(bytes, IrbisEncoding::ansi());
    }

    return *_instance;
}

bool AlphabetTable::isAlpha(const QChar &value) const {
    return characters.contains(value);
}

QStringList AlphabetTable::splitWords(const QString &text) const {
    QStringList result;

    if (text.isEmpty()) {
        return result;
    }

    QString accumulator;
    for (const QChar &c : text) {
        if (isAlpha(c)) {
            accumulator.append(c);
        } else {
            if (!accumulator.isEmpty()) {
                result.append(accumulator);
                accumulator.clear();
            }
        }
    }

    if (!accumulator.isEmpty()) {
        result.append(accumulator);
    }

    return result;
}

QString AlphabetTable::trimText(const QString &text) const {
    if (text.isEmpty()) {
        return text;
    }

    if (isAlpha(text.at(0)) && isAlpha(text.at(text.size()-1))) {
        return text;
    }

    QString result = text;
    while (result.length() && !isAlpha(result.at(0))) {
        result.remove(0, 1);
    }

    while (result.length() && !isAlpha(result.at(result.size() - 1))) {
        result.remove(result.size() - 1, 1);
    }

    return result;
}

bool AlphabetTable::verify(bool throwOnError) const {
    bool result = !characters.isEmpty();
    if (!result && throwOnError) {
        throw IrbisException();
    }

    return result;
}

AlphabetTable AlphabetTable::parse(QTextStream &stream) {
    QByteArray bytes;
    QString text = stream.readAll();
    TextNavigator navigator(text);

    while (!navigator.eot()) {
        if (navigator.skipWhitespace().eot()) {
            break;
        }

        QString s = navigator.readInteger();
        if (s.isEmpty()) {
            throw IrbisException();
        }

        char c = static_cast<char>(fastParse32(s) & 0xFF);
        if (!c) {
            throw IrbisException();
        }
        bytes.append(c);
    }

    if (bytes.size() < 1) {
        throw IrbisException();
    }

    AlphabetTable result(bytes, IrbisEncoding::ansi());

    return result;
}

AlphabetTable AlphabetTable::readLocalFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        throw IrbisException();
    }

    QTextStream stream(&file);
    return parse(stream);
}

