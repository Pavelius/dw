#include "main.h"

struct feature_info {
	variant			type;
	char			level;
	const char*		name;
	featureproc		proc;
	variant			feat;
	aref<variant>	features;
};
static variant fighting_style_feats[] = {StyleArchery, StyleDefense, StyleDueling, StyleGreatWeaponFighting, StyleProtection, StyleTwoWeaponFighting};
static variant dwarven_tools_proficience[] = {MasonProficiency, SmithProficiency, AlchemistProficiency};
static variant cleric_spells_0[] = {Guidance, Light, Resistance, SacredFlame, SpareOfDying, Thaumaturgy};
static variant cleric_spells_1[] = {Bless, Command, CureWounds, DetectMagic, GuidingBolt, HealingWord, InflictWounds, Sanctuary, ShieldOfFaith};

static void dwarven_tools(const feature_info& info, creature& player, bool interactive) {
	player.apply(dwarven_tools_proficience, "Выбирайте [гномью] профессию", 1, interactive);
}

static void fighting_style(const feature_info& info, creature& player, bool interactive) {
	player.apply(fighting_style_feats, "Выбирайте ваш стиль боя", 1, interactive);
}

static void divine_domain(const feature_info& info, creature& player, bool interactive) {
	auto domain = player.choose_domain(interactive);
	player.set(domain);
}

static void cantrips(const feature_info& info, creature& player, bool interactive) {
	player.apply(info.features, "Выберите Заговоры", player.getslots(0), interactive);
}

static void all(const feature_info& info, creature& player, bool interactive) {
	for(auto f : info.features)
		player.set(f);
}

static feature_info feature_data[] = {{Fighter, 1, "Боевой стиль", fighting_style},
{Fighter, 1, 0, 0, SecondWind},
{Cleric, 1, 0, 0, Spellcasting},
{Cleric, 1, "Сфера божества", divine_domain},
{Cleric, 1, 0, cantrips, {}, cleric_spells_0},
{Cleric, 1, 0, all, {}, cleric_spells_1},
{Dwarf, 1, "Владение инструментами", dwarven_tools},
{Elf, 1, "Обостренные чувства", 0, Perception}
};

void creature::apply(variant type, int level, bool interactive) {
	for(auto& e : feature_data) {
		if(e.type != type || e.level != level)
			continue;
		if(e.feat)
			set(e.feat);
		if(e.proc)
			e.proc(e, *this, interactive);
	}
}