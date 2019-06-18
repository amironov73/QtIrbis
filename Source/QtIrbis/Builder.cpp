// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

Search Search::all() {
    Search result;
    result._buffer = "I=$";

    return result;
}

Search& Search::and_(const QString &text) {
    _buffer = QString("(") + _buffer + QString(" * ")
            + wrap(text) + QString(")");
    return *this;
}

Search& Search::and_(const QString &text1, const QString &text2) {
    _buffer = QString("(") + _buffer + QString(" * ")
            + wrap(text1) + QString(" * ") + wrap(text2) + QString(")");
    return *this;
}

Search& Search::and_(const QString &text1, const QString &text2, const QString &text3) {
    _buffer = QString("(") + _buffer + QString(" * ")
            + wrap(text1) + QString(" * ") + wrap(text2) + QString(" * ")
            + wrap(text3) + QString(")");
    return *this;
}

Search& Search::and_(const Search &item) {
    return and_(item.toString());
}

Search& Search::and_(const Search &item1, const Search &item2) {
    return and_(item1.toString(), item2.toString());
}

Search& Search::and_(const Search &item1, const Search &item2, const Search &item3) {
    return and_(item1.toString(), item2.toString(), item3.toString());
}

Search Search::equals(const QString &prefix, const QString &text) {
    Search result;
    result._buffer = wrap(prefix + text);
    return result;
}

Search Search::equals(const QString &prefix, const QString &text1, const QString &text2) {
    Search result;
    result._buffer = QString("(") + wrap(prefix + text1)
            + QString(" + ") + wrap(prefix + text2) + QString(")");
    return result;

}

Search Search::equals(const QString &prefix, const QString &text1, const QString &text2, const QString &text3) {
    Search result;
    result._buffer = QString("(") + wrap(prefix + text1)
            + QString(" + ") + wrap(prefix + text2) + QString(" + ")
            + wrap(prefix + text3) + QString(")");
    return result;

}

bool Search::needWrap(const QString &text) {
    if (text.isNull() || text.isEmpty()) {
        return true;
    }
    QChar c = text.at(0);
    if (c == '"' || c == '(') {
        return false;
    }

    if (text.contains(' ')
        || text.contains('+')
        || text.contains('*')
        || text.contains('^')
        || text.contains('#')
        || text.contains('(')
        || text.contains(')')
            || text.contains('"')) {
        return true;
    }
    return false;
}

Search& Search::not_(const QString &text) {
    _buffer = QString("(") + _buffer + QString(" ^ ")
            + wrap(text) + QString(")");
    return *this;
}

Search& Search::not_(const Search &item) {
    return not_(item.toString());
}

Search& Search::or_(const QString &text) {
    _buffer = QString("(") + _buffer + QString(" + ")
            + wrap(text) + QString(")");
    return *this;
}

Search& Search::or_(const QString &text1, const QString &text2) {
    _buffer = QString("(") + _buffer + QString(" * ")
            + wrap(text1) + QString(" * ") + wrap(text2) + QString(")");
    return *this;
}

Search& Search::or_(const QString &text1, const QString &text2, const QString &text3) {
    _buffer = QString("(") + _buffer + QString(" + ")
            + wrap(text1) + QString(" * ") + wrap(text2) + QString(" + ")
            + wrap(text3) + QString(")");
    return *this;
}

Search& Search::or_(const Search &item) {
    return or_(item.toString());
}

Search& Search::or_(const Search &item1, const Search &item2) {
    return or_(item1.toString(), item2.toString());
}

Search& Search::or_(const Search &item1, const Search &item2, const Search &item3) {
    return or_(item1.toString(), item2.toString(), item3.toString());
}

Search& Search::sameField(const QString &text) {
    _buffer = QString("(") + _buffer + QString(" (G) ")
            + wrap(text) + QString(")");
    return *this;
}

Search& Search::sameRepeat(const QString &text) {
    _buffer = QString("(") + _buffer + QString(" (F) ")
            + wrap(text) + QString(")");
    return *this;
}

QString Search::toString() const {
    return _buffer;
}

QString Search::wrap(const QString &text) {
    if (needWrap(text)) {
        return QString("\"") + text + QString("\"");
    }

    return text;
}

QString Search::wrap(const Search &item) {
    return wrap (item.toString());
}

Search keyword(const QString &value1) {
    return Search::equals("K=", value1);
}
Search author(const QString &value1) {
    return Search::equals("A=", value1);
}

Search title(const QString &value1) {
    return Search::equals("T=", value1);
}

Search publisher(const QString &value1) {
    return Search::equals("O=", value1);
}

Search place(const QString &value1) {
    return Search::equals("MI=", value1);
}

Search subject(const QString &value1) {
    return Search::equals("S=", value1);
}

Search language(const QString &value1) {
    return Search::equals("J=", value1);
}

Search year(const QString &value1) {
    return Search::equals("G=", value1);
}

Search magazine(const QString &value1) {
    return Search::equals("TJ=", value1);
}

Search documentKind(const QString &value1) {
    return Search::equals("V=", value1);
}

Search udc(const QString &value1) {
    return Search::equals("U=", value1);
}

Search bbk(const QString &value1) {
    return Search::equals("BBK=", value1);
}

Search rzn(const QString &value1) {
    return Search::equals("RZN=", value1);
}

Search mhr(const QString &value1) {
    return Search::equals("MHR=", value1);
}
