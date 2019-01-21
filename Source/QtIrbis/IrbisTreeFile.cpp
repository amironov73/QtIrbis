// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

const QChar IrbisTreeFile::Indent = '\u0009';

IrbisTreeFile::IrbisTreeFile() : roots() {
}

static int arrangeLevel(QList<IrbisTreeNode> &list, int level, int index, int count) {
    int next = index + 1;
    int level2 = level + 1;

    IrbisTreeNode &parent = list[index];
    while (next < count) {
        IrbisTreeNode &child = list[next];
        if (child.level <= level) {
            break;
        }

        if (child.level == level2) {
            parent.children.append(child);
        }

        next++;
    }

    return next;
}

static void arrangeLevel(QList<IrbisTreeNode> &list, int level) {
    int count = list.size();
    int index = 0;

    while (index < count) {
        int next = arrangeLevel(list, level, index, count);
        index = next;
    }
}

static int countIndent(const QString &text) {
    int result = 0;
    for (int i = 0; i < text.length(); i++) {
        if (text.at(i) == IrbisTreeFile::Indent) {
            result++;
        } else {
            break;
        }
    }

    return result;
}

void IrbisTreeFile::write(std::ostream &stream) const {
    for (auto item : roots) {
        item.write(stream, 0);
    }
}
