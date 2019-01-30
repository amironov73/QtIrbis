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

static void arrangeLevel(QList<IrbisTreeNode> &list, qint32 level) {
    qint32 count = list.size();
    qint32 index = 0;

    while (index < count) {
        qint32 next = arrangeLevel(list, level, index, count);
        index = next;
    }
}

static qint32 countIndent(const QString &text) {
    qint32 result = 0;
    for (qint32 i = 0; i < text.length(); i++) {
        if (text.at(i) == IrbisTreeFile::Indent) {
            result++;
        } else {
            break;
        }
    }

    return result;
}

void IrbisTreeFile::parse(QTextStream &stream) {
    roots.clear();
    QList<IrbisTreeNode> list;
    QString line = stream.readLine();
    if (line.isEmpty()) {
        return;
    }

    if (countIndent(line) != 0) {
        throw IrbisException();
    }

    list.append(IrbisTreeNode(line));
    qint32 currentLevel = 0;
    while (true) {
        line = stream.readLine();
        if (line.isEmpty()) {
            break;
        }

        qint32 level = countIndent(line);
        if (level > (currentLevel + 1)) {
            throw IrbisException();
        }

        currentLevel = level;
        line = line.trimmed(); // TODO: trimStart()
        IrbisTreeNode node(line);
        node.level = level;
        list.append(node);
    }

    qint32 maxLevel = list[0].level;
    for (auto node : list) {
        if (node.level > maxLevel) {
            maxLevel = node.level;
        }
    }

    for (qint32 level = 0; level < maxLevel; ++level) {
        arrangeLevel(list, level);
    }

    for (auto node : list) {
        if (node.level == 0) {
            roots.append(node);
        }
    }
}

void IrbisTreeFile::readLocalFile(const QString &fileName, QTextCodec *encoding) {
    roots.clear();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        throw IrbisException();
    }

    QTextStream stream(&file);
    stream.setCodec(encoding);
    parse(stream);
}

void IrbisTreeFile::write(QTextStream &stream) const {
    for (auto item : roots) {
        item.write(stream, 0);
    }
}
