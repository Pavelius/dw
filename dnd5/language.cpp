#include "main.h"

languagei bsmeta<languagei>::elements[] = {{"Common", "Всеобщий", ModernLanguage},
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

language_typei bsmeta<language_typei>::elements[] = {{"Any", "Любой"},
{"Modern", "Современный"},
{"Ancient", "Древний"},
};
assert_enum(language_type, AncientLanguage);

static void select(adat<variant, 32>& elements, language_type_s type) {
	for(auto i = 0; i < sizeof(bsmeta<languagei>::elements) / sizeof(bsmeta<languagei>::elements[0]); i++) {
		if(type == AnyLanguage || bsmeta<languagei>::elements[i].type == type)
			elements.add(variant(Language, i));
	}
}

void creature::choose_languages(class_s type, bool interactive) {
	char temp[260];
	adat<variant, 32> elements;	elements.clear();
	set(LanguageCommon);
	auto count = bsmeta<racei>::elements[getrace()].extra_languages;
	count += bsmeta<racei>::elements[getsubrace()].extra_languages;
	count += bsmeta<backgroundi>::elements[background].extra_languages;
	stringbuilder sb(temp);
	sb.add("Выберите [%1] язык", getstr(ModernLanguage));
	select(elements, ModernLanguage);
	apply(elements, temp, count, interactive);
}