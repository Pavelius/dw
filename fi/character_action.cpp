#include "main.h"

struct action_info {
	const char*		id;
	const char*		name;
	used_s			type;
	variant			use;
};
static action_info action_data[] = {{"Hike", "��������������"},
{"LeadTheWay", "�����"},
{"KeepWatch", "���������"},
{"Forage", "�����"},
{"Hunt", "���������"},
{"Fish", "��������"},
{"MakeCamp", "������� ������"},
{"Rest", "��������"},
{"Sleep", "�����"},
{"Explore", "�����������"},
{"Slash", "��������", ActionSlow, Melee},
{"Stab", "������", ActionSlow, Melee},
{"Punch", "�������", ActionSlow, Melee},
{"Kick", "�����", ActionSlow, Melee},
{"Bite", "�������", ActionSlow, Melee},
{"Grapple", "��������", ActionSlow},
{"Run", "������"},
{"Flee", "���������"},
{"Dodge", "����������", ActionFast},
{"Parry", "����������", ActionFast},
{"DrawWeapon", "������� ������", ActionFast},
{"SwingWeapon", "������� � �������", ActionFast},
{"StandUp", "���������", ActionFast},
{"Shove", "��������"},
{"Disarm", "�����������"},
{"Feint", "�������� �����"},
{"Retreat", "������ �� ���"},
{"ReadyWeapon", "����������� ������"},
{"Aim", "�����������"},
{"Shoot", "����������"},
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