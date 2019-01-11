#include "QtIrbis.h"

//=========================================================

SearchScenario::SearchScenario()
    : name(), prefix(), dictionaryType(0), menuName(), oldFormat(),
    correction(), truncation(), hint(), modByDicAuto(), logic(),
    advance(), format() {
}

QList<SearchScenario> SearchScenario::parse(IniFile &iniFile) {
    QList<SearchScenario> result;
    // TODO implement

    return result;
}
