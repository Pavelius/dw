#include "main.h"

template<> const char* getstr<tag>(tag id) {
	switch(id.type) {
	case Ability: return getstr((ability_s)id.value);
	case Alignment: return getstr((alignment_s)id.value);
	case Class: return getstr((class_s)id.value);
	case Item: return getstr((item_s)id.value);
	case Monster: return getstr((monster_s)id.value);
	case Skill: return getstr((skill_s)id.value);
	default: return "[[tag]]";
	}
}