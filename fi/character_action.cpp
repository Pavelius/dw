#include "main.h"

struct action_info {
	const char*	id;
	const char*	name;
	used_s		type;
	variant		use;
};
static action_info action_data[] = {{"Hike", "Путишествовать"},
{"LeadTheWay", "Вести"},
{"KeepWatch", "Сторожить"},
{"Forage", "Найти"},
{"Hunt", "Охотиться"},
{"Fish", "Рыбачить"},
{"MakeCamp", "Разбить лагерь"},
{"Rest", "Отдыхать"},
{"Sleep", "Спать"},
{"Explore", "Исследовать"},
{"Slash", "Рубануть", ActionSlow, Melee},
{"Stab", "Ткнуть", ActionSlow, Melee},
{"Punch", "Ударить", ActionSlow, Melee},
{"Kick", "Пнуть", ActionSlow, Melee},
{"Bite", "Укусить", ActionSlow, Melee},
{"Grapple", "Схватить", ActionSlow, Melee},
{"BreakFree", "Вырваться", ActionSlow, Melee},
{"Run", "Пробежка", ActionFast, Move},
{"Flee", "Бежать", ActionSlow, Move},
{"Dodge", "Уклониться", ActionDodge, Move},
{"Parry", "Парировать", ActionParry, Melee},
{"DrawWeapon", "Достать оружие", ActionFast},
{"SwingWeapon", "Ударить с размаха", ActionFast},
{"GetUp", "Подняться", ActionFast},
{"Shove", "Толкнуть", ActionFast, Melee},
{"Disarm", "Обезоружить", ActionFast, Melee},
{"Feint", "Обманный прием", ActionFast},
{"Retreat", "Отступать", ActionFast, Move},
{"ReadyWeapon", "Подготовить оружие", ActionFast},
{"Aim", "Прицелиться", ActionFast},
{"Shoot", "Выстрелить", ActionSlow, Marksmanship},
{"Persuade", "Убедить", ActionSlow, Manipulation},
{"Taunt", "Глумиться", ActionSlow, Manipulation},
};
assert_enum(action, Taunt);
getstr_enum(action);

int character::getuse(action_s id) const {
	auto au = action_data[id].type;
	switch(au) {
	case ActionFast: return used[ActionFast] + used[ActionSlow];
	case ActionDodge: return used[ActionDodge] + used[ActionFast] + used[ActionSlow];
	case ActionParry: return used[ActionParry] + used[ActionFast] + used[ActionSlow];
	case ActionSlow: return used[ActionSlow];
	default: return 0;
	}
}

range_s	character::getrange(action_s id) const {
	switch(id) {
	case Feint: return Arm;
	case Stab: case Slash: return Arm;
	case Punch: case Kick: case Bite: return Arm;
	default: return Near;
	}
}

bool character::react(action_s a, character* opponent, bool run) {
	if(isbroken() || getuse(a) == 0)
		return false;
	auto& weapon = wears[Hand];
	switch(a) {
	case Dodge:
		break;
	case Parry:
		if(!weapon && !isshield())
			return false;
		break;
	default:
		return false;
	}
	return true;
}

bool character::activity(action_s a, character* opponent, bool run) {
	if(isbroken() || getuse(a) == 0)
		return false;
	auto& weapon = wears[Hand];
	switch(a) {
	case Slash:
		if(!isstance())
			return false;
		if(!weapon.is(Blunt) && !weapon.is(Edged))
			return false;
		break;
	case Stab:
		if(!isstance())
			return false;
		if(!weapon.is(Pointed))
			return false;
		break;
	case Disarm:
		if(!opponent || !opponent->wears[Hand])
			return false;
		break;
	case Punch: case Kick:
		if(!isstance() || weapon)
			return false;
		break;
	case Grapple:
		if(!isstance() || weapon)
			return false;
		break;
	case GetUp:
		if(!is(Prone))
			return false;
		break;
	case Retreat:
		break;
	default:
		return false;
	}
	return true;
}