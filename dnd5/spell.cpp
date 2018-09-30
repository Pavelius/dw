#include "main.h"

struct spell_info {
	const char*			id;
	const char*			name;
	char				level;
	school_s			school;
	duration_s			cast;
	range_s				range;
	duration_s			duration;
	dice				damage;
} spell_data[] = {{"No spell", "Нет заклинания"},
// 0 - уровень
{"Acid Splash", "Разбрызгивание кислоты", 0, Conjuration, Action, Range10, Instantaneous},
{"Dancing Light", "Танцующие огоньки", 0, Evocation, Action, Range120, Concentration},
{"Fire Bolt", "Огненная стрела", 0, Evocation, Action, Range120, Instantaneous, {1, 10, 0, Fire}},
{"Guidance", "Ориентир", 0, Divination, Action, Touch, Concentration},
{"Light", "Свет", 0, Evocation, Action, Touch, DurationHour},
{"Mage Hand", "Волшебная рука", 0, Conjuration, Action, Range10, DurationMinute},
{"Minor Illusion", "Мелкая иллюзия", 0, Illusion, Action, Range30, DurationMinute},
{"Poison Spray", "Распыление яда", 0, Conjuration, Action, Range10, Instantaneous, {1, 12, 0, Poison}},
{"Prestidigination", "Представление", 0, Transmutation, Action, Range10, Instantaneous},
{"Ray of Frost", "", 0, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Cold}},
{"Resistance", "", 0, Abjuration, Action, Touch, Concentration},
{"Sacred Flame", "", 0, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Radiant, Dexterity, Save}},
{"Shocking Grasp", "", 0, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Lightning}},
{"Spare the Dying", "", 0, Necromancy, Action, Touch, Instantaneous},
{"Thaumaturgy", "", 0, Transmutation, Action, Range30, Instantaneous},
};