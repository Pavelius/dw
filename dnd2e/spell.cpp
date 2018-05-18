#include "main.h"

enum target_s : unsigned char {
	TargetNone,
	TargetAlly, TargetAllAlly,
	TargetEnemy,
	TargetCreature,
};

static struct spell {
	const char*			id;
	const char*			name;
	school_s			school[2];
	char				levels[3]; // Cleric, Mage, Druid
	distance_s			distance;
	duration_s			duration;
	saveinfo			save;
	target_s			target;
	magic_power_s		state;
} spell_data[] = {
	{"Bless", "Благословение", {Conjuration, Summoning}, {1}, Range6, Duration6Round, {}, TargetAllAlly, Blessed},
	{"Command", "Команда", {Enchantment, Charm}, {1}, Range1, Duration1Round, {}, TargetEnemy, HumanControl},
	{"Create Water", "Создать воду", {Alteration}, {1}, Range1, Permanent},
	{"Cure Light Wounds", "Лечить легкое ранение", {Necromantic}, {1}, Touch, Instantaneous, {}, TargetAlly, Healing},
	{"Detect Evil", "Определить зло", {Divination}, {1}, Range12, Duration1TurnPlus1Per2Level},
	{"Detect Magic", "Определить магию", {Divination}, {1}, Range3, Duration1Turn},
	{"Light", "Свет", {Alteration}, {1}, Range12, Duration6TurnPlus1PerLevel},
	{"Protection From Evil", "Защита от зла", {Abjuration}, {1}, Touch, Duration5RoundPerLevel},
	{"Purify Food and Drink", "Очистить еду и воду", {Alteration}, {1}, Range3, Instantaneous},
	{"Remove Fear", "Убрать страх", {Abjuration}, {1}, Touch, Instantaneous},
	{"Resist Cold", "Сопротивление холоду", {Alteration}, {1}, Touch, Duration1TurnPerLevel},
	{"Sanctuary", "Убежище", {Abjuration}, {1}, Touch, Duration2RoundPlus1RoundPerLevel},
	//
	{"Augury", "Гадание", {Divination}, {1}, Self},
	{"Chant", "Песнопение", {Conjuration, Summoning}, {1}, Self, Concetration, {}, TargetAllAlly},
	{"Detect Charm", "Определить очарование", {Divination}, {1}, Range3, Duration1Turn},
	{"Find Traps", "Найти ловушки", {Divination}, {1}, Range3, Duration5Turn},
	{"Hold Person", "Обездвижить персону", {Enchantment, Charm}, {1}, Range6, Duration4RoundPlus1RoundPerLevel, {SaveVsParalization, Negate}},
	{"Know Alignment", "Узнать мировозрение", {Divination}, {1}, Range1},
	{"Resist Fire", "Сопротивление огню", {Alteration}, {1}, Touch},
	{"Silence, 15 Radius", "Тишина, 15 радиус", {Alteration}, {1}, Range12},
	{"Slow Poison", "Замедлить яд", {Necromantic}, {1}, Touch},
	{"Snake Charm", "Очаровать змей", {Enchantment, Charm}, {1}, Range3},
	{"Speak With Animals", "Разговор с животными", {Alteration}, {1}, Self},
	{"Spiritual Hammer", "Духовный молот", {Invocation}, {1}, Range3},
};
assert_enum(spell, SpellSpiritualHammer);
getstr_enum(spell);