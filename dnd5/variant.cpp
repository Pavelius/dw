#include "main.h"

template<> const char* getstr<variant>(variant e) {
	switch(e.type) {
	case Item: return getstr(e.item);
	case Feat: return getstr(e.feat);
	case Class: return getstr(e.classv);
	case Race: return getstr(e.race);
	case Pack: return getstr(e.pack);
	case Skill: return getstr(e.skill);
	case Spell: return getstr(e.spell);
	case Language: return getstr(e.language);
	default: return "Неизвестно";
	}
}