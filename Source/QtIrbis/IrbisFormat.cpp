// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

QString IrbisFormat::removeComments(QString text) {
    if (text.isEmpty()) {
        return text;
    }

    if (!text.contains("/*")) {
        return text;
    }

    QString result;
    ushort state = 0;
    int index = 0, length = text.length();
    while (index < length) {
        ushort c = text[index].unicode();

        switch(state) {
        case '\'':
        case '"':
        case '|':
            if (c == state) {
                state = 0;
            }
            result.append(c);
            break;

        default:
            if (c == '/') {
                if (index + 1 < length && text[index + 1] == '*') {
                    while (index < length) {
                        c = text[index].unicode();
                        if (c == '\r' || c == '\n') {
                            result.append(c);
                            break;
                        }

                        index++;
                    }
                }
                else {
                    result.append(c);
                }
            }
            else if (c == '\'' || c == '"' || c == '|') {
                state = c;
                result.append(c);
            }
            else {
                result.append(c);
            }

            break;
        }

        index++;
    }

    return result;
}

QString IrbisFormat::prepareFormat(QString text) {
    text = removeComments(text);
    int length = text.length();
    if (length == 0) {
        return text;
    }

    bool flag = false;
    for (int i = 0; i  < length; i++) {
        if (text[i] < ' ') {
            flag = true;
            break;
        }
    }

    if (!flag) {
        return text;
    }

    QString result;
    for (int i = 0; i < length; i++) {
        ushort c = text[i].unicode();
        if (c >= ' ') {
            result.append(c);
        }
    }

    return result;
}
