#include "main.h"

struct action_info;
struct action_context {
	action_info*	action;
	int				result, modifier;
	character*		player;
	character*		enemy;
};
struct action_info {
	typedef void(*callback)(action_context& e, bool interactive);
	const char*		id;
	const char*		name;
	used_s			type;
	variant			use;
	const char*		text_success;
	const char*		text_fail;
	callback		proc_roll;
	aref<action_s>	reaction;
	callback		proc_effect;
};
static void damage(action_context& e, bool interactive) {
	if(e.result)
		e.enemy->damage(Strenght, e.result, interactive);
}
static void roll(action_context& e, bool interactive) {
	if(e.action->use.type != Skills)
		return;
	e.result = e.player->roll(e.action->use.skill, e.modifier);
	if(e.result > 0) {
		if(e.action->text_success)
			e.player->act(e.enemy, e.action->text_success);
	} else {
		if(e.action->text_fail)
			e.player->act(e.enemy, e.action->text_fail);
	}
	if(e.result > 0) {
		if(e.action->reaction)
			e.enemy->react(e.action->reaction, e.player, e.result, true);
	}
	if(e.action->proc_effect)
		e.action->proc_effect(e, true);
}
static void grapple(action_context& e, bool interactive) {
	e.enemy->setgrappler(e.player);
}
static void action_run(action_context& e, bool interactive) {
	if(e.enemy)
		e.enemy->set(ArmsHand);
	e.player->set(ArmsHand);
}
static action_s melee_reaction[] = {DodgeStand, DodgeProne, ParryShield, ParryWeapon};
static action_info action_data[] = {{"Hike", "Путишествовать", QuarterDayAction, NoVariant},
{"LeadTheWay", "Вести", QuarterDayAction, NoVariant},
{"KeepWatch", "Сторожить", QuarterDayAction, NoVariant},
{"Forage", "Найти", QuarterDayAction, NoVariant},
{"Hunt", "Охотиться", QuarterDayAction, NoVariant},
{"Fish", "Рыбачить", QuarterDayAction, NoVariant},
{"MakeCamp", "Разбить лагерь", QuarterDayAction, NoVariant},
{"Rest", "Отдыхать", QuarterDayAction, NoVariant},
{"Sleep", "Спать", QuarterDayAction, NoVariant},
{"Explore", "Исследовать", QuarterDayAction, NoVariant},
{"Slash", "Рубануть", ActionSlow, Melee, "%герой ударил%а %оппонента %оружием.", "%герой промазала %оружием по %оппоненту.", roll, melee_reaction, damage},
{"Stab", "Ткнуть", ActionSlow, Melee, "%герой ткнул%а %оппонента %оружием.", "%герой промазала %оружием по %оппоненту.", roll, melee_reaction, damage},
{"Punch", "Ударить", ActionSlow, Melee, "%герой нанес%ла удар рукой.", "%герой промазал%а рукой по %оппоненту.", roll, melee_reaction, damage},
{"Kick", "Пнуть", ActionSlow, Melee, "%герой пнул%а ногой.", "%герой пнул%а ногой и промазал%а.", roll, melee_reaction, damage},
{"Bite", "Укусить", ActionSlow, Melee, "%герой укусил%а %оппонента.", "%герой попыталась укусить %оппонента, но даже не попал%а в цель.", roll, melee_reaction, damage},
{"Grapple", "Схватить", ActionSlow, Melee, "%герой схватил%а %оппонента.", "%герой попытал%ась схватил%а %оппонента, но не хватило силы.", grapple},
{"GrappleAttack", "Удушение", ActionSlow, Melee},
{"BreakFree", "Вырваться", ActionSlow, Melee},
{"Run", "Пробежка", ActionFast, Move, "%герой подбежал%а к %оппоненту.", "%герой подбежал%а к %оппоненту, но спотыкнул%ась и упал%а.", action_run},
{"Flee", "Бежать", ActionSlow, Move, "%1 скрыл%ась прочь."},
{"DodgeStand", "Уклониться", ActionDodge, Move},
{"DodgeProne", "Уклониться и упасть", ActionDodge, Move},
{"ParryWeapon", "Парировать оружием", ActionParry, Melee},
{"ParryShield", "Парировать щитом", ActionParry, Melee},
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
	auto interactive = true;
	if(isbroken() || getuse(a) == 0)
		return false;
	action_context e = {};
	e.player = this;
	e.enemy = opponent;
	e.action = action_data + a;
	auto& weapon = wears[Hand];
	auto range = getrange(opponent);
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
		e.modifier = flee_modifiers[range];
		break;
	case Run:
		if(range == Arm)
			return false;
		if(run) {
		}
		break;
	default:
		return false;
	}
	if(run) {
	}
	return true;
}