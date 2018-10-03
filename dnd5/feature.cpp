#include "main.h"

struct feature_info {
	variant			type;
	char			level;
	const char*		name;
	featureproc		proc;
	variant			feat;
};
static variant fighting_style_feats[] = {StyleArchery, StyleDefense, StyleDueling, StyleGreatWeaponFighting, StyleProtection, StyleTwoWeaponFighting};
static variant dwarven_tools_proficience[] = {MasonProficiency, SmithProficiency, AlchemistProficiency};

static void dwarven_tools(const feature_info& info, creature& player, bool interactive) {
	player.apply(dwarven_tools_proficience, "��������� [������] ���������", 1, interactive);
}

static void fighting_style(const feature_info& info, creature& player, bool interactive) {
	player.apply(fighting_style_feats, "��������� ��� ����� ���", 1, interactive);
}

static void divine_domain(const feature_info& info, creature& player, bool interactive) {
	auto domain = player.choose_domain(interactive);
	player.set(domain);
}

static feature_info feature_data[] = {{Fighter, 1, "������ �����", fighting_style},
{Fighter, 1, 0, 0, SecondWind},
{Cleric, 1, 0, 0, Spellcasting},
{Cleric, 1, "����� ��������", divine_domain},
{Dwarf, 1, "�������� �������������", dwarven_tools},
{Elf, 1, "����������� �������", 0, Perception}
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