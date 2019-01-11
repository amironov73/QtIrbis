#include "QtIrbis.h"

//=========================================================

SearchParameters::SearchParameters()
    : database(), firstRecord(1), formatSpecification(),
    maxMfn(0), minMfn(0), numberOfRecords(0), searchExpression(),
    filterSpecification(), utfFormat(false), nestedCall(false) {
}
