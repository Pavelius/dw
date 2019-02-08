#include "main.h"

struct action_info {
	const char*		id;
	const char*		name;
	used_s			type;
	variant			use;
	const char*		text_success;
	const char*		text_fail;
	aref<action_s>	reaction;
};
static action_s melee_reaction[] = {DodgeStand, DodgeProne, ParryShield, ParryWeapon};
static action_info action_data[] = {{"Hike", "��������������", QuarterDayAction, NoVariant},
{"LeadTheWay", "�����", QuarterDayAction, NoVariant},
{"KeepWatch", "���������", QuarterDayAction, NoVariant},
{"Forage", "�����", QuarterDayAction, NoVariant},
{"Hunt", "���������", QuarterDayAction, NoVariant},
{"Fish", "��������", QuarterDayAction, NoVariant},
{"MakeCamp", "������� ������", QuarterDayAction, NoVariant},
{"Rest", "��������", QuarterDayAction, NoVariant},
{"Sleep", "�����", QuarterDayAction, NoVariant},
{"Explore", "�����������", QuarterDayAction, NoVariant},
{"Slash", "��������", ActionSlow, Melee, "%����� ������%� %��������� %�������", "%����� ��������� %������� �� %���������", melee_reaction},
{"Stab", "������", ActionSlow, Melee, "%����� �����%� %��������� %�������", "%����� ��������� %������� �� %���������", melee_reaction},
{"Punch", "�������", ActionSlow, Melee, "%����� �����%�� ���� �����", "%����� ��������%� ����� �� %���������", melee_reaction},
{"Kick", "�����", ActionSlow, Melee, "%����� ����%� �����", "%����� ����%� ����� � ��������%�", melee_reaction},
{"Bite", "�������", ActionSlow, Melee, "%����� ������%� %���������", "%����� ���������� ������� %���������, �� ���� �� �����%� � ����", melee_reaction},
{"Grapple", "��������", ActionSlow, Melee},
{"GrappleAttack", "��������", ActionSlow, Melee},
{"BreakFree", "���������", ActionSlow, Melee},
{"Run", "��������", ActionFast, Move},
{"Flee", "������", ActionSlow, Move, "%1 �����%��� �����."},
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

bool character::activity(action_s a, character* opponent, scene* ps, bool run) {
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
		break;
	case Stab:
		if(!isstance())
			return false;
		if(range != Arm)
			return false;
		if(!weapon.is(Pointed))
			return false;
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
	if(run) {
		switch(a) {
		case Run:
			break;
		default:
			switch(action_data[a].use.type) {
			case Skills:
				result = roll(action_data[a].use.skill, modifier);
				if(result > 0) {
					if(action_data[a].text_success)
						act(action_data[a].text_success);
				} else {
					if(action_data[a].text_fail)
						act(action_data[a].text_fail);
				}
				break;
			}
			break;
		}
		if(result > 0) {
			if(action_data[a].reaction)
				opponent->react(action_data[a].reaction, this, result, true);
		}
		if(result) {

		}
	}
	return true;
}