#include "main.h"

struct action_info {
	const char*		id;
	const char*		name;
	used_s			type;
	variant			use;
};
static action_info action_data[] = {{"Hike", "Путишествовать"},
{"LeadTheWay", "Вести"},
{"KeepWatch", "Сторожить"},
{"Forage", "Найти"},
{"Hunt", "Охотиться"},
{"Fish", "Рыбачить"},
{"MakeCamp", "Сделать привал"},
{"Rest", "Отдыхать"},
{"Sleep", "Спать"},
{"Explore", "Исследовать"},
{"Slash", "Рубануть", ActionSlow, Melee},
{"Stab", "Ткнуть", ActionSlow, Melee},
{"Punch", "Ударить", ActionSlow, Melee},
{"Kick", "Пнуть", ActionSlow, Melee},
{"Bite", "Укусить", ActionSlow, Melee},
{"Grapple", "Схватить", ActionSlow},
{"Run", "Бежать"},
{"Flee", "Отступать"},
{"Dodge", "Уклониться", ActionFast},
{"Parry", "Парировать", ActionFast},
{"DrawWeapon", "Достать оружие", ActionFast},
{"SwingWeapon", "Ударить с размаха", ActionFast},
{"StandUp", "Подняться", ActionFast},
{"Shove", "Толкнуть"},
{"Disarm", "Обезоружить"},
{"Feint", "Обманный прием"},
{"Retreat", "Бежать из боя"},
{"ReadyWeapon", "Подготовить оружие"},
{"Aim", "Прицелиться"},
{"Shoot", "Выстрелить"},
};
assert_enum(action, Shoot);
getstr_enum(action);

bool character::apply(action_s a, character* opponent, bool run) {
	auto& weapon = wears[Hand];
	switch(a) {
	case Slash:
		if(!weapon.is(Blunt) && !weapon.is(Edged))
			return false;
		break;
	case Stab:
		if(!weapon.is(Pointed))
			return false;
		break;
	case Punch: case Kick: case Bite:
		if(weapon)
			return false;
		break;
	}
	return true;
}