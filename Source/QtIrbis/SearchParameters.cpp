// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

//=========================================================

SearchParameters::SearchParameters()
    : database(), firstRecord(1), formatSpecification(),
    maxMfn(0), minMfn(0), numberOfRecords(0), searchExpression(),
    filterSpecification(), utfFormat(false), nestedCall(false) {
}
