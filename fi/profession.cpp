#include "main.h"

static item_s trade_goods[] = {Arrows, GrapplingHook, Rope,
TallonCandle, OilLamp, Lantern, Torches,
Waterskin, Bandages, LampOil,
InkAndQuil, Parchment, Blanket, SleepingFur, FlintAndSteel,
FieldRations};
static item_s one_handed_weapon[] = {Knife, Dagger, Falchion,
Shortsword, Broadsword, Longsword, Scimitar,
Handaxe, Battleaxe, TwoHandedAxe,
Mace, Morningstar, Warhammer, Flail, WoodenClub, HeavyHammer
};
professioni bsmeta<professioni>::elements[] = {{"Druid", "�����", Wits, {Endurance, Survival, Insight, Healing, AnimalHandling}, {D8, D8, D6, 1, {}, {{Staff, Knife}}}},
{"Fighter", "����", Strenght, {Might, Endurance, Melee, Crafting, Move}, {D8, D6, D6, 1, {StuddedLeather}, {}, 1}},
{"Hunter", "�������", Agility, {Stealth, Move, Marksmanship, Scouting, Survival}, {D8, D8, D6, 2, {}, {{ShortBow, Sling}}}},
{"Minstrel", "����������", Empathy, {Lore, Insight, Manipulation, Performance, Healing}, {D8, D6, D8, 1, {Knife}, {{Lute, Flute}}}},
{"Peddler", "��������", Empathy, {Crafting, SleightOfHand, Scouting, Insight, Manipulation}, {D8, D8, D12, 3, {Knife}}},
{"Rider", "�������", Agility, {Endurance, Melee, Marksmanship, Survival, AnimalHandling}, {D8, D8, D6, 1, {}, {{ShortSpear, Handaxe}, {ShortBow, Sling}}}},
{"Rogue", "�������", Agility, {Melee, Stealth, SleightOfHand, Move, Manipulation}, {D6, D6, D10, 2, {Dagger}}},
{"Sorcerer", "���������", Wits, {Crafting, SleightOfHand, Lore, Insight, Manipulation}, {D6, D8, D8, 1, {}, {{Staff, Knife}}}},
};
assert_enum(profession, Sorcerer);

ability_s character::getkey(profession_s id) {
	return bsmeta<professioni>::elements[id].ability;
}

int	character::getpriority(ability_s v) {
	auto min = 4;
	auto max = getmaximum(v);
	if(min == max)
		return 1;
	return (1 + (max - min)) * 2;
}

char character::getmaximum(skill_s v) const {
	for(auto e : bsmeta<professioni>::elements[profession].skills) {
		if(e == v)
			return 3;
	}
	return 1;
}

int character::roll(resource_s i) {
	static int dice[] = {6, 8, 10, 12};
	return xrand(1, dice[i]);
}

item_s character::choose_item(const char* title, aref<item_s> source, bool interactive) {
	for(auto i : source)
		an.add(i, getstr(i));
	return (item_s)an.choose(interactive, false, title);
}

void character::apply_equipment(bool interactive) {
	auto& q = bsmeta<professioni>::elements[profession].equipment;
	add(item(FieldRations, q.food));
	add(item(Waterskin, q.water));
	add(item(SilverPiece, roll(q.silver)));
	for(auto e : q.standart)
		add(e);
	if(q.one_handed_weapon)
		add(choose_item("��� ����� ����� �������?", one_handed_weapon, interactive));
	for(auto& e : q.custom) {
		if(!e[0])
			continue;
		item_s t[] = {e[0], e[1]};
		add(choose_item("��� �� �������������?", t, interactive));
	}
}