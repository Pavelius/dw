#include "main.h"

static quest ancient_tome = {AnyLocation, "����������� ������� ������� ���.", {Lore, -1}, {
	{"������ ������ ��� ���� �� �� ����������."},
	{"�� ������� ������� ��������� ������.", {AddSpell, Discard}},
}};
static quest old_journal = {AnyLocation, "������� ���������� ������� �������.", {Lore, -1}, {
	{"������ ������ ��� ���� �� �� ����������."},
	{"� ������ ������� ����������� ������ � �������� ������ � ������� ������ � �������.", {Add3Clue, Discard}},
}};
static constexpr const struct item_i {
	struct effect_i {
		stat_s		id;
		char		count;
	};
	struct tome_i {
		char		movement; // Lose this count of movement to do this
		char		sanity; // Lose this count of sanity to do this
		quest*		script;
		char		usable; // This is maximum use count
	};
	const char*		id;
	const char*		name;
	stat_s			type;
	char			deck_count;
	char			cost;
	char			hands;
	effect_i		bonus;
	tome_i			tome;
	cflags<tag_s>	tags;
} item_data[] = {
	{"", ""},
	// Common items
	{".18 Derringer", ".18 ���������", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon, CantStealOrLoose}},
	{".38 Revolver", ".38 ���������", CommonItem, 2, 4, 1, {CombatCheck, 3}, {}, {PhysicalWeapon}},
	{".45 Automatic", ".45 �����", CommonItem, 2, 4, 1, {CombatCheck, 4}, {}, {PhysicalWeapon}},
	{"Ancient Tome", "������� �����", CommonItem, 2, 4, 0, {}, {2, 0, &ancient_tome}, {ExhaustToEffect, Tome}},
	{"Axe", "�����", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon, CombatBonusTwoHand}},
	{"Bullwhip", "����", CommonItem, 2, 2, 1, {CombatCheck, 1}, {}, {PhysicalWeapon, ExhaustToRerollDie}},
	{"Cavalry Saber", "������������ �����", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon}},
	{"Cross", "�����", CommonItem, 2, 3, 1, {HorrorCheck, 1}, {}, {MagicalWeapon, CombatBonusVsUndead}},
	{"Dark Cloak", "������ ����", CommonItem, 2, 2, 0, {EvadeCheck, 1}},
	{"Dynamite", "�������", CommonItem, 2, 2, 2, {CombatCheck, 8}, {}, {PhysicalWeapon, DiscardAfterUse}},
	{"Food", "���", CommonItem, 2, 1, 0, {Stamina, 1}, {}, {DiscardAfterUse}},
	{"Knife", "���", CommonItem, 2, 2, 1, {CombatCheck, 3}, {}, {PhysicalWeapon}},
	{"Lantern", "������", CommonItem, 2, 2, 0, {Luck}, {}, {ExhaustToRerollDie}},
	{"Lucky Cigarette Case", "��������� ���������", CommonItem, 2, 2, 0, {SkillCheck}, {}, {ExhaustToRerollDie, DiscardAfterUse}},
	{"Map of Arkham", "����� �������", CommonItem, 2, 2, 0, {Movement, 1}, {}, {ExhaustToEffect}},
	{"Motorcycle", "��������", CommonItem, 2, 4, 0, {Movement, 2}, {}, {ExhaustToEffect}},
	{"Old Journal", "������ ������", CommonItem, 2, 1, 0, {}, {1, 0, &old_journal}, {ExhaustToEffect, Tome}},
	{"Research Materials", "����������������� ���������", CommonItem, 2, 1, 0, {Clue, 1}, {}, {DiscardAfterUse}},
	{"Rifle", "�����", CommonItem, 2, 6, 2, {CombatCheck, 5}, {}, {PhysicalWeapon}},
	{"Shotgun", "��������", CommonItem, 2, 6, 2, {CombatCheck, 4}, {}, {PhysicalWeapon, SixDoubleSuccess}},
	{"Tommy Gun", "�������", CommonItem, 2, 7, 2, {CombatCheck, 6}, {}, {PhysicalWeapon}},
	{"Whiskey", "�����", CommonItem, 2, 1, 0, {Sanity, 1}, {}, {DiscardAfterUse}},
	//
	{"Skill Bravery", "���������", Skill, 2, 8, 0},
	{"Skill Expert Occultist", "��������� �������", Skill, 2, 8, 0},
	{"Skill Marksman", "������ ���", Skill, 2, 8, 0},
	{"Skill Speed", "��������", Skill, 2, 8, 0, {Speed, 1}},
	{"Skill Sneak", "����������", Skill, 2, 8, 0, {Sneak, 1}},
	{"Skill Fight", "���", Skill, 2, 8, 0, {Fight, 1}},
	{"Skill Will", "����", Skill, 2, 8, 0, {Will, 1}},
	{"Skill Lore", "������", Skill, 2, 8, 0, {Lore, 1}},
	{"Skill Luck", "�����", Skill, 2, 8, 0, {Luck, 1}},
	//
	{"Bind Monster", "��������� �������", Spell, 2},
	{"Dread Curse of Azathoth", "������� ��������� �������", Spell, 2},
	{"Enchant Weapon", "���������� ������", Spell, 2},
	{"Find Gate", "����� �����", Spell, 2},
	{"Flesh Ward", "������ �����", Spell, 2},
	{"Heal", "���������", Spell, 2},
	{"Mist of Releh", "����� �������", Spell, 2},
	{"Red Sign of Shuddle Mell", "������� ����� ���� �����", Spell, 2},
	{"Shrivelling", "���������", Spell, 2},
	{"Voice of Ra", "����� ��", Spell, 2},
	{"Wither", "�����", Spell, 2},
};
assert_enum(item, Wither);
getstr_enum(item);

void deck::create(stat_s group) {
	clear();
	for(auto& e : item_data) {
		if(e.type != group)
			continue;
		auto id = item_s(&e - item_data);
		for(auto i = 0; i < e.deck_count; i++)
			add(id);
	}
	zshuffle(data, count);
}

stat_s deck::getgroup(item_s id) {
	return item_data[id].type;
}

bool item::is(item_s i, tag_s value) {
	return item_data[i].tags.is(value);
}

int item::get(item_s i, stat_s id) {
	if(item_data[i].bonus.id == id)
		return item_data[i].bonus.count;
	return 0;
}