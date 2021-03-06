#include "main.h"

struct action_context {
	actioni*			action;
	int					result, modifier;
	character*			player;
	character*			enemy;
	item*				tool;
	range_s				range;
};

static bool roll_we(action_context& e, bool run, bool interactive) {
	if(e.action->use.type != Skills)
		return false;
	if(run) {
		e.result = e.player->roll((skill_s)e.action->use.subtype, e.modifier, e.tool);
		if(e.result > 0) {
			if(e.action->text_success)
				e.player->act(e.enemy, e.action->text_success);
		} else {
			if(e.action->text_fail)
				e.player->act(e.enemy, e.action->text_fail);
		}
		if(e.result > 0) {
			if(e.action->reaction)
				e.enemy->react(e.action->reaction, e.player, e.result, interactive);
		}
	}
	return true;
}
static bool roll(action_context& e, bool run, bool interactive) {
	if(!roll_we(e, run, interactive))
		return false;
	if(run) {
		if(e.result > 0) {
			if(e.action->proc_effect)
				e.action->proc_effect(e, run, interactive);
		}
	}
	return true;
}
static bool melee(action_context& e, bool run, bool interactive) {
	if(!e.enemy)
		return false;
	if(e.range != Arm)
		return false;
	if(!e.player->isstance())
		return false;
	return roll(e, run, interactive);
}
static bool unarmed(action_context& e, bool run, bool interactive) {
	if(e.tool && *e.tool)
		return false;
	return melee(e, run, interactive);
}
static bool slash(action_context& e, bool run, bool interactive) {
	if(!e.tool || !(*e.tool))
		return false;
	if(!e.tool->is(Blunt) && !e.tool->is(Edged))
		return false;
	return melee(e, run, interactive);
}
static bool stab(action_context& e, bool run, bool interactive) {
	if(!e.tool || !(*e.tool))
		return false;
	if(!e.tool->is(Pointed))
		return false;
	return melee(e, run, interactive);
}
static bool disarm(action_context& e, bool run, bool interactive) {
	if(e.enemy && !e.enemy->get(Hand))
		return false;
	return melee(e, run, interactive);
}
static bool damage(action_context& e, bool run, bool interactive) {
	if(!e.result)
		return false;
	if(run)
		e.enemy->damage(Strenght, e.result, interactive);
	return true;
}
static bool grapple_roll(action_context& e, bool run, bool interactive) {
	auto ps = e.player->get(Strenght);
	auto os = e.enemy->get(Strenght);
	if(ps < os * 3)
		return false;
	return roll(e, run, interactive);
}
static bool grapple(action_context& e, bool run, bool interactive) {
	if(!e.result)
		return false;
	if(run)
		e.enemy->setgrappler(e.player);
	return true;
}
static bool action_run(action_context& e, bool run, bool interactive) {
	if(e.player->is(ArmsHand))
		return false;
	if(run) {
		if(e.action->text_success)
			e.player->act(e.enemy, e.action->text_success);
		if(e.enemy)
			e.enemy->set(ArmsHand);
		e.player->set(ArmsHand);
	}
	return true;
}
static bool getup(action_context& e, bool run, bool interactive) {
	if(!e.player->is(Prone))
		return false;
	if(run) {
		if(e.action->text_success)
			e.player->act(e.enemy, e.action->text_success);
		e.player->remove(Prone);
	}
	return true;
}
static variant melee_reaction[] = {DodgeStand, DodgeProne, ParryShield, ParryWeapon};
actioni bsmeta<actioni>::elements[] = {{"Hike", "��������������", QuarterDayAction, NoVariant},
{"LeadTheWay", "�����", QuarterDayAction, NoVariant},
{"KeepWatch", "���������", QuarterDayAction, NoVariant},
{"Forage", "�����", QuarterDayAction, NoVariant},
{"Hunt", "���������", QuarterDayAction, NoVariant},
{"Fish", "��������", QuarterDayAction, NoVariant},
{"MakeCamp", "������� ������", QuarterDayAction, NoVariant},
{"Rest", "��������", QuarterDayAction, NoVariant},
{"Sleep", "�����", QuarterDayAction, NoVariant},
{"Explore", "�����������", QuarterDayAction, NoVariant},
{"Slash", "��������", ActionSlow, Melee, "%����� ������%� %��������� %-�������.", "%����� ��������� %-������� �� %���������.", slash, melee_reaction, damage},
{"Stab", "������", ActionSlow, Melee, "%����� �����%� %��������� %-�������.", "%����� ��������� %-������� �� %���������.", stab, melee_reaction, damage},
{"Punch", "�������", ActionSlow, Melee, "%����� �����%�� ���� �����.", "%����� ��������%� ����� �� %���������.", unarmed, melee_reaction, damage},
{"Kick", "�����", ActionSlow, Melee, "%����� ����%� �����.", "%����� ����%� ����� � ��������%�.", unarmed, melee_reaction, damage},
{"Bite", "�������", ActionSlow, Melee, "%����� ������%� %���������.", "%����� ���������� ������� %���������, �� ���� �� �����%� � ����."},
{"Grapple", "��������", ActionSlow, Melee, "%����� �������%� %���������.", "%����� �������%��� �������%� %���������, �� �� ������� ����.", grapple_roll, melee_reaction, grapple},
{"GrappleAttack", "��������", ActionSlow, Melee},
{"BreakFree", "���������", ActionSlow, Melee},
{"Run", "������ � �����", ActionFast, Move, "%����� ��������%� � %���������.", "%����� ��������%� � %���������, �� ���������%��� � ����%�.", action_run},
{"Flee", "������", ActionSlow, Move, "%1 �����%��� �����."},
{"DodgeStand", "����������", ActionDodge, Move, "� ��������� ������ %����� �������%��� �� �����."},
{"DodgeProne", "���������� � ������", ActionDodge, Move, "� ��������� ������ %����� �������%��� �� ����� � ����� �� �����."},
{"ParryWeapon", "���������� �������", ActionParry, Melee, "%����� �����%� ����."},
{"ParryShield", "���������� �����", ActionParry, Melee, "%����� �����%� ���� �����."},
{"DrawWeapon", "������� ������", ActionFast},
{"SwingWeapon", "������� � �������", ActionFast},
{"GetUp", "���������", ActionFast, NoVariant, "%����� ������%��� �� ����.", 0, getup},
{"Shove", "��������", ActionFast, Melee},
{"Disarm", "�����������", ActionFast, Melee, "%����� �������%��� ����������� %���������.", "%����� �������%��� ����������� %���������, �� ������ �� �����.", disarm, melee_reaction},
{"Feint", "�������� �����", ActionFast},
{"Retreat", "���������", ActionFast, Move},
{"ReadyWeapon", "����������� ������", ActionFast},
{"Aim", "�����������", ActionFast},
{"Shoot", "����������", ActionSlow, Marksmanship},
{"Persuade", "�������", ActionSlow, Manipulation},
{"Taunt", "���������", ActionSlow, Manipulation},
};
assert_enum(action, Taunt);
static int flee_modifiers[] = {-2, -1, 0, 1, 2};

int character::getuse(action_s id) const {
	auto au = bsmeta<actioni>::elements[id].type;
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
	item* weapon = 0;
	auto modifier = 0;
	switch(a) {
	case DodgeStand:
		modifier = -2;
		break;
	case DodgeProne:
		break;
	case ParryWeapon:
		if(!wears[Hand])
			return false;
		weapon = wears + Hand;
		break;
	case ParryShield:
		if(!isshield())
			return false;
		weapon = wears + LeftHand;
		break;
	default:
		return false;
	}
	if(run) {
		auto m = 0;
		switch(bsmeta<actioni>::elements[a].use.type) {
		case Skills:
			m = roll((skill_s)bsmeta<actioni>::elements[a].use.subtype, modifier, weapon);
			break;
		}
		if(m > 0) {
			result -= m;
			act(bsmeta<actioni>::elements[a].text_success);
		}
		else
			act(bsmeta<actioni>::elements[a].text_fail);
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
	action_context e = {};
	e.player = this;
	e.enemy = opponent;
	e.action = bsmeta<actioni>::elements + a;
	e.tool = wears + Hand;
	e.range = is(ArmsHand) ? Arm : Near;
	auto interactive = true;
	if(e.action->proc_roll)
		return e.action->proc_roll(e, run, interactive);
	return false;
}