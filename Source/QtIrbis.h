#ifndef QTIRBIS_H
#define QTIRBIS_H

#include <QtCore>

#if defined(QTIRBIS_LIBRARY)
#define QTIRBIS_EXPORT Q_DECL_EXPORT
#else
#define QTIRBIS_EXPORT Q_DECL_IMPORT
#endif

//=========================================================

class QTIRBIS_EXPORT SubField
{
public:
    char code;
    QString value;

    SubField() : code('\0'), value()
    {
    }
};

//=========================================================

class QTIRBIS_EXPORT RecordField
{
public:
    int tag;
    QString value;

    RecordField() : tag(0), value()
    {
    }
};

//=========================================================

class QTIRBIS_EXPORT MarcRecord
{
public:
    int mfn;

    MarcRecord() : mfn(0)
    {
    }
};

#endif // QTIRBIS_H
