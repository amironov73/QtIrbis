#include "QtIrbis.h"

//=========================================================

MarcRecord& MarcRecord::add(qint32 tag) {
    fields.append(new RecordField(tag));

    return *this;
}

MarcRecord& MarcRecord::add(quint32 tag, QString value) {
    fields.append(new RecordField(tag, value));

    return *this;
}

MarcRecord& MarcRecord::clear() {
    fields.clear();

    return *this;
}

MarcRecord* MarcRecord::clone() const {
    MarcRecord *result = new MarcRecord();
    result->mfn = mfn;
    foreach(const RecordField *item, fields) {
        result->fields.append(item->clone());
    }

    return result;
}

QString MarcRecord::fm(qint32 tag) const {
    foreach(const RecordField *item, fields) {
        if (item->tag == tag) {
            return item->value;
        }
    }

    return QString();
}

QString MarcRecord::fm(qint32 tag, QChar code) const {
    foreach(const RecordField *item, fields) {
        if (item->tag == tag) {
            return item->getFirstSubFieldValue(code);
        }
    }

    return QString();
}

QStringList MarcRecord::fma(qint32 tag) const {
    QStringList result;
    foreach(const RecordField *item, fields) {
        if (item->tag == tag && !item->value.isEmpty()) {
            result.append(item->value);
        }
    }

    return result;
}

QStringList MarcRecord::fma(qint32 tag, QChar code) const {
    QStringList result;
    foreach (const RecordField *item, fields) {
        if (item->tag == tag) {
            QString value = item->getFirstSubFieldValue(code);
            if (!value.isEmpty()) {
                result.append(value);
            }
        }
    }

    return result;
}

RecordField* MarcRecord::getFirstField(qint32 tag) const {
    foreach (RecordField *item, fields) {
        if (item->tag == tag) {
            return item;
        }
    }

    return nullptr;
}

QString MarcRecord::toString() const {
    QString result;
    bool first = true;
    foreach (const RecordField *item, fields) {
        if (first) {
            result = item->toString();
            first = false;
        }
        else {
            result = result + "\n" + item->toString();
        }
    }

    return result;
}

void MarcRecord::parseSingle(QStringList &lines) {
    // TODO implement
}
