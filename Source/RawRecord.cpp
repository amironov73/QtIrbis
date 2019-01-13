#include "QtIrbis.h"

//=========================================================

RawRecord::RawRecord()
    : database(), mfn(), status(), version(), fields() {
}

QString RawRecord::encode(const QString &delimiter=IrbisText::IrbisDelimiter) const {
    QString result;
    QTextStream stream(&result);
    result.append(mfn).append('#').append(status).append(delimiter);
    result.append("0#").append(version).append(delimiter);

    for (auto field: fields) {
        result.append(field).append(delimiter);

    }

    return result;
}

void RawRecord::parseSingle(const QStringList &lines) {
    if (lines.isEmpty()) {
        return;
    }

    QStringList parts = maxSplit(lines[0], '#', 2);
    mfn = parts[0];
    status = "0";
    if (parts.length() == 2) {
        status = parts[1];
    }

    parts = maxSplit(lines[1], '#', 2);
    version = "0";
    if (parts.length() == 2) {
        version = parts[1];
    }

    fields.clear();
    for (int i = 2; i < lines.length(); i++) {
        fields.append(lines[i]);
    }
}

QString RawRecord::toString() const {
    return encode();
}
