#include "main.h"

struct language_info {
	const char*			id;
	const char*			name;
	language_type_s		type;
} language_data[] = {{"Common", "Всеобщий", ModernLanguage},
{"Dwarvish", "Гномий", ModernLanguage},
{"Elvish", "Эльфийский", ModernLanguage},
{"Giant", "Гиганский", ModernLanguage},
{"Goblin", "Гоблинский", ModernLanguage},
{"Orc", "Орчий", ModernLanguage},
{"Abysal", "Демонский", AncientLanguage},
{"Celestial", "Небесный", AncientLanguage},
{"Draconic", "Драконий", AncientLanguage},
{"Deep Speech", "Наречье глубины", AncientLanguage},
{"Infernal", "Адский", AncientLanguage},
};
assert_enum(language, LanguageInfernal);
getstr_enum(language);

struct language_type_info {
	const char*			id;
	const char*			name;
} language_type_data[] = {{"Any", "Любой"},
{"Modern", "Современный"},
{"Ancient", "Древний"},
};
assert_enum(language_type, AncientLanguage);
getstr_enum(language_type);

static void select(adat<variant, 32>& elements, language_type_s type) {
	for(auto i = 0; i < sizeof(language_data) / sizeof(language_data[0]); i++) {
		if(type == AnyLanguage || language_data[i].type == type)
			elements.add(variant(Language, i));
	}
}

void creature::choose_languages(class_s type, bool interactive) {
	char temp[260];
	adat<variant, 32> elements;	elements.clear();
	set(LanguageCommon);
	auto count = race_data[race].extra_languages;
	if(race_data[race].basic)
		count += race_data[race_data[race].basic].extra_languages;
	count += background_data[background].extra_languages;
	szprints(temp, zendof(temp), "Выберите [%1] язык", getstr(ModernLanguage));
	select(elements, ModernLanguage);
	apply(elements, temp, count, interactive);
}