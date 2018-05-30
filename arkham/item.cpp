#include "main.h"

static quest ancient_tome = {AnyLocation, "����������� ������� ������� ���.", {Lore, -1}, {{"������ ������ ��� ���� �� �� ����������."},
{"�� ������� ������� ��������� ������.", {AddSpell, Discard}},
}};
static quest old_journal = {AnyLocation, "������� ���������� ������� �������.", {Lore, -1}, {{"������ ������ ��� ���� �� �� ����������."},
{"� ������ ������� ����������� ������ � �������� ������ � ������� ������ � �������.", {Add3Clue, Discard}},
}};
static const struct item_i {
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
	roll_info		bonus;
	tome_i			tome;
	cflags<tag_s>	tags;
} item_data[] = {{"", ""},
// Common items
{".18 Derringer", "���������", CommonItem, 2, 3, {CombatCheck, 2}, {}, {PhysicalWeapon, CantStealOrLoose, OneHanded}},
{".38 Revolver", "���������", CommonItem, 2, 4, {CombatCheck, 3}, {}, {PhysicalWeapon, OneHanded}},
{".45 Automatic", "�����", CommonItem, 2, 4, {CombatCheck, 4}, {}, {PhysicalWeapon, OneHanded}},
{"Ancient Tome", "������� �����", CommonItem, 2, 4, {}, {2, 0, &ancient_tome}, {ExhaustToEffect, Tome}},
{"Axe", "�����", CommonItem, 2, 3, {CombatCheck, 2}, {}, {PhysicalWeapon, CombatBonusTwoHand, OneHanded}},
{"Bullwhip", "����", CommonItem, 2, 2, {CombatCheck, 1}, {}, {PhysicalWeapon, ExhaustToRerollDie, OneHanded}},
{"Cavalry Saber", "������������ �����", CommonItem, 2, 3, {CombatCheck, 2}, {}, {PhysicalWeapon, OneHanded}},
{"Cross", "�����", CommonItem, 2, 3, {HorrorCheck, 1}, {}, {MagicalWeapon, CombatBonusVsUndead, OneHanded}},
{"Dark Cloak", "������ ����", CommonItem, 2, 2, {EvadeCheck, 1}},
{"Dynamite", "�������", CommonItem, 2, 2, {CombatCheck, 8}, {}, {PhysicalWeapon, DiscardAfterUse, TwoHanded}},
{"Food", "���", CommonItem, 2, 1, {Stamina, 1}, {}, {DiscardAfterUse}},
{"Knife", "���", CommonItem, 2, 2, {CombatCheck, 3}, {}, {PhysicalWeapon, OneHanded}},
{"Lantern", "������", CommonItem, 2, 2, {Luck}, {}, {ExhaustToRerollDie}},
{"Lucky Cigarette Case", "��������� ���������", CommonItem, 2, 2, {SkillCheck}, {}, {ExhaustToRerollDie, DiscardAfterUse}},
{"Map of Arkham", "����� �������", CommonItem, 2, 2, {Movement, 1}, {}, {ExhaustToEffect}},
{"Motorcycle", "��������", CommonItem, 2, 4, {Movement, 2}, {}, {ExhaustToEffect}},
{"Old Journal", "������ ������", CommonItem, 2, 1, {}, {1, 0, &old_journal}, {ExhaustToEffect, Tome}},
{"Research Materials", "����������������� ���������", CommonItem, 2, 1, {Clue, 1}, {}, {DiscardAfterUse}},
{"Rifle", "�����", CommonItem, 2, 6, {CombatCheck, 5}, {}, {PhysicalWeapon, TwoHanded}},
{"Shotgun", "��������", CommonItem, 2, 6, {CombatCheck, 4}, {}, {PhysicalWeapon, SixDoubleSuccess, TwoHanded}},
{"Tommy Gun", "�������", CommonItem, 2, 7, {CombatCheck, 6}, {}, {PhysicalWeapon, TwoHanded}},
{"Whiskey", "�����", CommonItem, 2, 1, {Sanity, 1}, {}, {DiscardAfterUse}},
//
{"Skill Bravery", "���������", Skill, 2, 8},
{"Skill Expert Occultist", "���������", Skill, 2, 8},
{"Skill Marksman", "�������", Skill, 2, 8},
{"Skill Speed", "��������", Skill, 2, 8, {Speed, 1}},
{"Skill Sneak", "����������", Skill, 2, 8, {Sneak, 1}},
{"Skill Fight", "���", Skill, 2, 8, {Fight, 1}},
{"Skill Will", "����", Skill, 2, 8, {Will, 1}},
{"Skill Lore", "������", Skill, 2, 8, {Lore, 1}},
{"Skill Luck", "�����", Skill, 2, 8, {Luck, 1}},
//
{"Bind Monster", "��������� �������", Spell, 2},
{"Dread Curse of Azathoth", "������� ��������� �������", Spell, 4},
{"Enchant Weapon", "���������� ������", Spell, 3},
{"Find Gate", "����� �����", Spell, 4},
{"Flesh Ward", "������ �����", Spell, 4},
{"Heal", "���������", Spell, 3},
{"Mist of Releh", "����� �������", Spell, 4},
{"Red Sign of Shuddle Mell", "������� ����� ���� �����", Spell, 2},
{"Shrivelling", "���������", Spell, 5},
{"Voice of Ra", "����� ��", Spell, 3},
{"Wither", "�����", Spell, 6},
//
{"AlienStatue", "������ �� ������� ����", UniqueItem, 1},
{"AncientTablet", "������� �����", UniqueItem, 1},
{"BlueWatcherOfThePyramid", "����� ����� ��������", UniqueItem, 1},
};
assert_enum(item, BlueWatcherOfThePyramid);
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
	auto bonus = 0;
	if(item_data[i].bonus.id == id)
		bonus = item_data[i].bonus.bonus;
	return bonus;
}

int	item::gethands(item_s i) {
	auto result = 0;
	if(is(i, OneHanded))
		result = 1;
	else if(is(i, TwoHanded))
		result = 2;
	return result;
}

char* item::getname(char* result, const char* result_maximum, item_s i) {
	result[0] = 0;
	szprints(zend(result), result_maximum, "[");
	szprints(zend(result), result_maximum, item_data[i].name);
	szprints(zend(result), result_maximum, "]");
	szprints(zend(result), result_maximum, ": ");
	if(item_data[i].bonus.bonus) {
		item_data[i].bonus.getname(zend(result), result_maximum);
		szprints(zend(result), result_maximum, ". ");
	}
	for(auto e : item_data[i].tags)
		szprints(zend(result), result_maximum, getstr(e));
	auto pe = zend(result);
	while(pe > result && (pe[-1] == ' '))
		*--pe = 0;
	return result;
}