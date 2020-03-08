#include "main.h"

template<> const char* getstr<variant>(variant e) {
	switch(e.type) {
	case Item: return bsmeta<itemi>::elements[e.value].name;
	case Feat: return bsmeta<feati>::elements[e.value].name;
	case Class: return bsmeta<classi>::elements[e.value].name;
	case Race: return bsmeta<racei>::elements[e.value].name;
	case Pack: return bsmeta<packi>::elements[e.value].name;
	case Skill: return bsmeta<skilli>::elements[e.value].name;
	case Spell: return bsmeta<spelli>::elements[e.value].name;
	case Language: return bsmeta<languagei>::elements[e.value].name;
	default: return "Неизвестно";
	}
}

const char* variant::getinfo() const {
	switch(type) {
	case Race: return bsmeta<racei>::elements[value].text;
	case Feat: return bsmeta<feati>::elements[value].description;
	default: return "";
	}
}