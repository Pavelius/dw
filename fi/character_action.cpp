#include "main.h"

struct action_info {
	const char*	id;
	const char*	name;
	used_s		type;
	variant		use;
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
{"Grapple", "��������", ActionSlow, Melee},
{"GrappleAttack", "��������", ActionSlow, Melee},
{"BreakFree", "���������", ActionSlow, Melee},
{"Run", "��������", ActionFast, Move},
{"Flee", "������", ActionSlow, Move},
{"DodgeStand", "����������", ActionDodge, Move},
{"DodgeProne", "���������� � ������", ActionDodge, Move},
{"ParryWeapon", "���������� �������", ActionParry, Melee},
{"ParryShield", "���������� �����", ActionParry, Melee},
{"DrawWeapon", "������� ������", ActionFast},
{"SwingWeapon", "������� � �������", ActionFast},
{"GetUp", "���������", ActionFast},
{"Shove", "��������", ActionFast, Melee},
{"Disarm", "�����������", ActionFast, Melee},
{"Feint", "�������� �����", ActionFast},
{"Retreat", "���������", ActionFast, Move},
{"ReadyWeapon", "����������� ������", ActionFast},
{"Aim", "�����������", ActionFast},
{"Shoot", "����������", ActionSlow, Marksmanship},
{"Persuade", "�������", ActionSlow, Manipulation},
{"Taunt", "���������", ActionSlow, Manipulation},
};
assert_enum(action, Taunt);
getstr_enum(action);
static int flee_modifiers[] = {-2, -1, 0, 1, 2};

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

bool character::react(action_s a, character* opponent, int& result, bool run) {
	if(isbroken() || getuse(a) == 0)
		return false;
	auto& weapon = wears[Hand];
	auto modifier = 0;
	switch(a) {
	case DodgeStand:
		modifier = -2;
		break;
	case DodgeProne:
		break;
	case ParryWeapon:
		if(!weapon)
			return false;
		break;
	case ParryShield:
		if(!isshield())
			return false;
		break;
	default:
		return false;
	}
	if(run) {
		switch(action_data[a].use.type) {
		case Skills:
			roll(action_data[a].use.skill, modifier, &weapon);
			break;
		}
	}
	return true;
}

range_s character::getrange(const character* opponent) const {
	if(!opponent)
		return Long;
	if(opponent->is(ArmsHand) && is(ArmsHand))
		return Arm;
	return Near;
}

int character::activity(action_s a, character* opponent, scene* ps, bool run) {
	if(isbroken() || getuse(a) == 0)
		return false;
	auto& weapon = wears[Hand];
	auto result = 0;
	auto range = getrange(opponent);
	auto modifier = 0;
	switch(a) {
	case Slash:
		if(!isstance())
			return false;
		if(range != Arm)
			return false;
		if(!weapon.is(Blunt) && !weapon.is(Edged))
			return false;
		attack(action_data[a].use.skill, weapon, opponent);
		break;
	case Stab:
		if(!isstance())
			return false;
		if(range != Arm)
			return false;
		if(!weapon.is(Pointed))
			return false;
		attack(action_data[a].use.skill, weapon, opponent);
		break;
	case Disarm:
		if(!opponent || !opponent->wears[Hand])
			return false;
		if(range != Arm)
			return false;
		break;
	case Punch: case Kick:
		if(!isstance() || weapon)
			return false;
		if(range != Arm)
			return false;
		attack(action_data[a].use.skill, weapon, opponent);
		break;
	case Grapple:
		if(!isstance() || weapon)
			return false;
		if(range != Arm)
			return false;
		break;
	case GetUp:
		if(!is(Prone))
			return false;
		break;
	case Retreat:
		if(range != Arm)
			return false;
		break;
	case Flee:
		if(range == Arm)
			return false;
		modifier = flee_modifiers[range];
		if(run) {
			if(roll(Move, modifier)) {
				act("%1 �����%��� �����.", getname());
				ps->remove(this);
			}
		}
		break;
	case Run:
		if(range == Arm)
			return false;
		if(run) {
			if(opponent)
				opponent->set(ArmsHand);
			set(ArmsHand);
		}
		break;
	default:
		return false;
	}
	return true;
}