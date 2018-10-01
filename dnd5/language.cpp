#include "main.h"

struct language_info {
	const char*			id;
	const char*			name;
	language_type_s		type;
} language_data[] = {{"Common", "��������", ModernLanguage},
{"Dwarvish", "������", ModernLanguage},
{"Elvish", "����������", ModernLanguage},
{"Giant", "���������", ModernLanguage},
{"Goblin", "����������", ModernLanguage},
{"Orc", "�����", ModernLanguage},
{"Abysal", "���������", AncientLanguage},
{"Celestial", "��������", AncientLanguage},
{"Draconic", "��������", AncientLanguage},
{"Deep Speech", "������� �������", AncientLanguage},
{"Infernal", "������", AncientLanguage},
};
assert_enum(language, LanguageInfernal);
getstr_enum(language);

struct language_type_info {
	const char*			id;
	const char*			name;
} language_type_data[] = {{"Any", "�����"},
{"Modern", "�����������"},
{"Ancient", "�������"},
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
	adat<variant, 32> elements;
	set(LanguageCommon);
	for(auto lt = ModernLanguage; lt <= AncientLanguage; lt = (language_type_s)(lt + 1)) {
		elements.clear();
		auto count = race_data[race].extra_languages[lt-1];
		if(race_data[race].basic)
			count += race_data[race_data[race].basic].extra_languages[lt - 1];
		if(count) {
			char temp[260]; szprints(temp, zendof(temp), "�������� [%1] ����", getstr(lt));
			select(elements, lt);
			apply(elements, temp, count, interactive);
		}
	}
}