// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

IrbisTreeNode::IrbisTreeNode(const QString &value)
    : children(), value(value), level(0) {
}

IrbisTreeNode& IrbisTreeNode::add(const QString name) {
    IrbisTreeNode item(name);
    children.append(item);

    return children.last();
}

void IrbisTreeNode::write(std::ostream &stream, qint32 level) {
    for (qint32 i = 0; i < level; i++) {
        stream << IrbisTreeFile::Indent.toLatin1();
    }
    stream << value.toStdString();
    for (auto child : children) {
        child.write(stream, level + 1);
    }
}
