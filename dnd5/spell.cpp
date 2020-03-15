#include "main.h"

const unsigned Minute = 1;

static unsigned getduration(duration_s v) {
	switch(v) {
	case Action: return 1;
	case Concentration: return 60 * Minute;
	case DurationMinute: return Minute;
	case Duration10Minute: return 10 * Minute;
	case DurationHour: return 60 * Minute;
	case DurationNight: return 8 * 60 * Minute;
	default: return 0;
	}
}

spelli bsmeta<spelli>::elements[] = {{"No spell", "Нет заклинания"},
// 0 - уровень
{"Acid Splash", "Разбрызгивание кислоты", 0, {V, S}, Conjuration, Action, Range10, Instantaneous},
{"Dancing Light", "Танцующие огоньки", 0, {V, S, M}, Evocation, Action, Range120, Concentration},
{"Fire Bolt", "Огненная стрела", 0, {}, Evocation, Action, Range120, Instantaneous, {1, 10, 0, Fire}},
{"Guidance", "Ориентир", 0, {V, S}, Divination, Action, Touch, Concentration, {}},
{"Light", "Свет", 0, {V, M}, Evocation, Action, Touch, DurationHour, {}},
{"Mage Hand", "Волшебная рука", 0, {V, S}, Conjuration, Action, Range10, DurationMinute},
{"Minor Illusion", "Мелкая иллюзия", 0, {}, Illusion, Action, Range30, DurationMinute},
{"Poison Spray", "Ядовитые брызги", 0, {}, Conjuration, Action, Range10, Instantaneous, {1, 12, 0, Poison}},
{"Prestidigination", "Фокусы", 0, {}, Transmutation, Action, Range10, Instantaneous, {}},
{"Ray of Frost", "Луч холода", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Cold}},
{"Resistance", "Сопротивление", 0, {}, Abjuration, Action, Touch, Concentration},
{"Sacred Flame", "Священное пламя", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Radiant, Dexterity, Save}},
{"Shocking Grasp", "Шокирующая хватка", 0, {}, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Lightning, Strenght, Attack}},
{"Spare the Dying", "Жалость к умирающим", 0, {}, Necromancy, Action, Touch, Instantaneous, {}},
{"Thaumaturgy", "Чудеса", 0, {}, Transmutation, Action, Range30, Instantaneous},
// 1 - уровень
{"Bless", "Благословение", 1, {V, S, M}, Transmutation},
{"Command", "Команда", 1, {V}, Transmutation},
{"Cure Wounds", "Лечить ранения", 1, {}, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Healing}},
{"Detect Magic", "Определить магию", 1, {V, S}, Divination, Action, Self, Instantaneous},
{"Guiding Bolt", "Направляющий луч", 1, {V, S}, Evocation, Action, Range120, DurationMinute, {4, 6, 0, Radiant, Dexterity, Attack}},
{"Healing Word", "Исцеляющие слова", 1, {V}, Transmutation},
{"Inflict Wounds", "Нанести раны", 1, {V, S}, Transmutation},
{"Sanctuary", "Святилище", 1, {}, Transmutation},
{"ShieldOfFaith", "Щит веры", 1, {}, Transmutation},
};
assert_enum(spell, LastSpell);

bool creature::use(spell_s id, creature& opponent, int level, int modifier, bool run) {
	auto& ei = bsmeta<spelli>::elements[id];
	auto damage = ei.damage;
	switch(id) {
	case CureWounds:
		if(opponent.gethp() >= opponent.gethpmax())
			return false;
		if(run) {
			damage.d += level -ei.level;
			opponent.damage(-damage.roll(), ei.damage.type, true);
		}
		break;
	default:
		return false;
	}
	return true;
}

bool creature::cast(spell_s id, creature& enemy, bool interactive, bool run) {
	auto& e = bsmeta<spelli>::elements[id];
	if(e.components.is(V) || e.components.is(S)) {
		if(interactive && run) {
			act("%герой");
			auto p = sb.get();
			if(e.components.is(S))
				act(" взмахнул%а руками");
			if(e.components.is(V)) {
				if(!sb.ispos(p))
					act(" и");
				act(" прокричал%а странные слова");
			}
			if(sb.ispos(p))
				act(" взглянул на %1", enemy.getname());
			act(".");
		}
	}
	auto level = getlevel(id);
	auto modifier = get(Intellegence);
	return use(id, enemy, level, modifier, true);
}

int creature::getlevel(spell_s id) {
	return bsmeta<spelli>::elements[id].level;
}