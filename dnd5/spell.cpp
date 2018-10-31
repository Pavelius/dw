#include "main.h"

enum component_s : unsigned char {
	V, S, M
};

struct spell_info {
	const char*			id;
	const char*			name;
	char				level;
	cflags<component_s>	components;
	school_s			school;
	duration_s			cast;
	range_s				range;
	duration_s			duration;
	dice				damage;
	void(*proc)(creature& player, creature& opponent, spell_info& e, bool interactive);
};

static void make_damage(creature& player, creature& opponent, spell_info& e, bool interactive) {
	if(!e.damage)
		return;
	opponent.damage(e.damage.roll(), e.damage.type, interactive);
}

struct spell_info spell_data[] = {{"No spell", "Нет заклинания"},
	// 0 - уровень
{"Acid Splash", "Разбрызгивание кислоты", 0, {V, S}, Conjuration, Action, Range10, Instantaneous},
{"Dancing Light", "Танцующие огоньки", 0, {V, S, M}, Evocation, Action, Range120, Concentration},
{"Fire Bolt", "Огненная стрела", 0, {}, Evocation, Action, Range120, Instantaneous, {1, 10, 0, Fire}, make_damage},
{"Guidance", "Ориентир", 0, {V, S}, Divination, Action, Touch, Concentration},
{"Light", "Свет", 0, {V, M}, Evocation, Action, Touch, DurationHour},
{"Mage Hand", "Волшебная рука", 0, {V, S}, Conjuration, Action, Range10, DurationMinute},
{"Minor Illusion", "Мелкая иллюзия", 0, {}, Illusion, Action, Range30, DurationMinute},
{"Poison Spray", "Ядовитые брызги", 0, {}, Conjuration, Action, Range10, Instantaneous, {1, 12, 0, Poison}, make_damage},
{"Prestidigination", "Фокусы", 0, {}, Transmutation, Action, Range10, Instantaneous},
{"Ray of Frost", "Луч холода", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Cold}, make_damage},
{"Resistance", "Сопротивление", 0, {}, Abjuration, Action, Touch, Concentration},
{"Sacred Flame", "Священное пламя", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Radiant, Dexterity, Save}, make_damage},
{"Shocking Grasp", "Шокирующая хватка", 0, {}, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Lightning, Strenght, Attack}, make_damage},
{"Spare the Dying", "Жалость к умирающим", 0, {}, Necromancy, Action, Touch, Instantaneous},
{"Thaumaturgy", "Чудеса", 0, {}, Transmutation, Action, Range30, Instantaneous},
// 1 - уровень
{"Bless", "Благословение", 1, {V, S, M}, Transmutation},
{"Command", "Команда", 1, {V}, Transmutation},
{"Cure Wounds", "Лечить ранения", 1, {}, Transmutation},
{"Detect Magic", "Определить магию", 1, {V, S}, Transmutation},
{"Guiding Bolt", "Направляющий луч", 1, {V, S}, Transmutation},
{"Healing Word", "Исцеляющие слова", 1, {V}, Transmutation},
{"Inflict Wounds", "Нанести раны", 1, {V, S}, Transmutation},
{"Sanctuary", "Святилище", 1, {}, Transmutation},
{"ShieldOfFaith", "Щит веры", 1, {}, Transmutation},
};
assert_enum(spell, LastSpell);
getstr_enum(spell);

void creature::cast(spell_s id, creature& enemy, bool interactive) {
	auto& e = spell_data[id];
	if(e.components.is(V) || e.components.is(S)) {
		if(interactive) {
			act("%герой");
			if(e.components.is(S))
				act(" взмахнул%а руками");
			if(e.components.is(V)) {
				if(e.components.is(S))
					act(" и");
				act(" прокричал%а странные слова");
			}
			act(".");
		}
	}
	if(spell_data[id].proc)
		spell_data[id].proc(*this, enemy, spell_data[id], interactive);
}

int creature::getlevel(spell_s id) {
	return spell_data[id].level;
}