// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "QtIrbis.h"

using irbis::fastParse32;

//=========================================================

SearchScenario::SearchScenario()
    : name(), prefix(), dictionaryType(0), menuName(), oldFormat(),
    correction(), truncation(), hint(), modByDicAuto(), logic(),
    advance(), format() {
}

static const QString& get(const IniSection *section, const QString &name, qint32 index) {
    QString fullName = QString("Item%1%2").arg(name).arg(index);
    return section->getValue(fullName, "");
}

QList<SearchScenario> SearchScenario::parse(const IniFile &iniFile) {
    QList<SearchScenario> result;
    const IniSection *section = iniFile.getSection("SEARCH");
    if (section) {
        QString itemNumb = section->getValue("ItemNumb", "0");
        qint32 count = fastParse32(itemNumb);
        for (qint32 i = 0; i < count; i++) {
            SearchScenario scenario;
            scenario.name = get(section, "Name", i);
            scenario.prefix = get(section, "Pref", i);
            scenario.dictionaryType = fastParse32(get(section, "DictionType", i));
            scenario.menuName = get(section, "Menu", i);
            scenario.oldFormat = nullptr;
            scenario.correction = get(section, "ModByDic", i);
            scenario.truncation = get(section, "Tranc", i);
            scenario.hint = get(section, "Hint", i);
            scenario.modByDicAuto = get(section, "ModByDicAuto", i);
            scenario.logic = get(section, "Logic", i);
            scenario.advance = get(section, "Adv", i);
            scenario.format = get(section, "Pft", i);

            result.append(scenario);
        }
    }

    return result;
}
