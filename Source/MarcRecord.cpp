#include "QtIrbis.h"

//=========================================================

MarcRecord::MarcRecord() : database(), mfn(0), status(0), version(0), fields() {
}

MarcRecord& MarcRecord::add(qint32 tag) {
    fields.append(new RecordField(tag));

    return *this;
}

MarcRecord& MarcRecord::add(qint32 tag, const QString &value) {
    fields.append(new RecordField(tag, value));

    return *this;
}

MarcRecord& MarcRecord::clear() {
    fields.clear();

    return *this;
}

MarcRecord* MarcRecord::clone() const {
    MarcRecord *result = new MarcRecord();
    result->database = database;
    result->mfn = mfn;
    result->status = status;
    result->version = version;
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

bool MarcRecord::isDeleted() const {
    return (status & RecordStatus::Deleted) != 0;
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
    if (lines.isEmpty()) {
        return;
    }

    QString line = lines[0];
    QStringList parts = line.split("#");
    mfn = fastParse32(parts[0]);
    status = fastParse32(itemAt(parts, 1));

    line = lines[1];
    parts = line.split("#");
    version = fastParse32(parts[1]);

    fields.clear();
    qint32 length = lines.length();
    for (int i = 2; i < length; i++) {
        RecordField *field = RecordField::parse(lines[i]);
        fields.append(field);
    }
}
