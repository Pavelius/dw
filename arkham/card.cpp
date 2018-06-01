#include "main.h"

static quest ancient_tome = {AnyLocation, "����������� ������� ������� ���.", {Lore, -1}, {{"������ ������ ��� ���� �� �� ����������."},
{"�� ������� ������� ��������� ������.", {AddSpell, Discard}},
}};
static quest old_journal = {AnyLocation, "������� ���������� ������� �������.", {Lore, -1}, {{"������ ������ ��� ���� �� �� ����������."},
{"� ������ ������� ����������� ������ � �������� ������ � ������� ������ � �������.", {Add3Clue, Discard}},
}};
static quest langrange = {AnyLocation, 0, {}, {{"������������ ������� � ����� ������� �������� � ���� �������.", {RestoreAll}}}};
static const struct card_info {
	struct tome_info {
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
	roll_info		bonus[2];
	tome_info		tome;
	cflags<tag_s>	tags;
} card_data[] = {{"", ""},
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
{"CamillasRuby", "", UniqueItem, 1},
{"CarcosanPage", "", UniqueItem, 1},
{"CryptozoologyCollection", "", UniqueItem, 1},
{"CrystalOfTheElderThings", "", UniqueItem, 1},
{"DragonsEye", "", UniqueItem, 1},
{"ElderSign", "", UniqueItem, 1},
{"EnchantedBlade", "", UniqueItem, 1},
{"EnchantedJewelry", "", UniqueItem, 1},
{"EnchantedKnife", "", UniqueItem, 1},
{"FluteOfTheOuterGods", "", UniqueItem, 1},
{"GateBox", "", UniqueItem, 1},
{"HealingStone", "", UniqueItem, 1},
{"HolyWater", "", UniqueItem, 1},
{"LampOfAlhazred", "", UniqueItem, 1},
{"NamelessCults", "", UniqueItem, 1},
{"Necronomicon", "", UniqueItem, 1},
{"ObsidianStatue", "", UniqueItem, 1},
{"PallidMask", "", UniqueItem, 1},
{"PowderOfIbnGhazi", "", UniqueItem, 1},
{"RubyOfRlyeh", "", UniqueItem, 1},
{"SilverKey", "", UniqueItem, 1},
{"SwordOfGlory", "", UniqueItem, 1},
{"TheKingInYellow", "", UniqueItem, 1},
{"WardingStatue", "", UniqueItem, 1},
//
{"Anna Kaslow", "���� ������", Ally, 1, 10, {Luck, 2}, {}, {}},
{"Duke", "���", Ally, 1, 10, {SanityMaximum, 1}, {}, {}},
{"Eric Colt", "���� �����", Ally, 1, 10, {Speed, 2}, {}, {}},
{"John Legrasse", "���� ��������", Ally, 1, 10, {Will, 2}, {}, {}},
{"Professor Armitage", "��������� �������", Ally, 1, 10, {Lore, 2}, {}, {}},
{"Richard Upton Pickman", "", Ally, 1, 10, {{Luck, 1}, {Speed, 1}}, {}, {}},
{"Ruby Standish", "", Ally, 1, 10, {Sneak, 2}, {}, {}},
{"Ryan Dean", "���� ���", Ally, 1, 10, {{Sneak, 1}, {Will, 1}}, {}, {}},
{"Sir William Brinton", "��� ������ �������", Ally, 1, 10, {{StaminaMaximum, 1}}, {}, {}},
{"Thomas F. Malone", "", Ally, 1, 10, {{Fight, 1}, {Lore, 1}}, {}, {}},
{"Tom \"Mountain\" Murphy", "��� \"����\" �����", Ally, 1, 10, {{Fight, 2}}, {}, {}},
};
assert_enum(card, TomMountainMurphy);
getstr_enum(card);

void deck::create(stat_s group) {
	clear();
	for(auto& e : card_data) {
		if(e.type != group)
			continue;
		auto id = card_s(&e - card_data);
		for(auto i = 0; i < e.deck_count; i++)
			add(id);
	}
	zshuffle(data, count);
}

stat_s deck::getgroup(card_s id) {
	return card_data[id].type;
}

bool item::is(card_s i, tag_s value) {
	return card_data[i].tags.is(value);
}

int item::get(card_s i, stat_s id) {
	auto bonus = 0;
	if(card_data[i].bonus[0].id == id)
		bonus = card_data[i].bonus[0].bonus;
	else if(card_data[i].bonus[1].id == id)
		bonus = card_data[i].bonus[1].bonus;
	return bonus;
}

int	item::gethands(card_s i) {
	auto result = 0;
	if(is(i, OneHanded))
		result = 1;
	else if(is(i, TwoHanded))
		result = 2;
	return result;
}

char* item::getname(char* result, const char* result_maximum, card_s i) {
	result[0] = 0;
	szprints(zend(result), result_maximum, "[");
	szprints(zend(result), result_maximum, card_data[i].name);
	szprints(zend(result), result_maximum, "]");
	szprints(zend(result), result_maximum, ": ");
	if(card_data[i].bonus[0].bonus) {
		card_data[i].bonus[0].getname(zend(result), result_maximum);
		if(card_data[i].bonus[1].bonus) {
			szprints(zend(result), result_maximum, ", ");
			card_data[i].bonus[1].getname(zend(result), result_maximum);
		}
		szprints(zend(result), result_maximum, ". ");
	}
	for(auto e : card_data[i].tags)
		szprints(zend(result), result_maximum, getstr(e));
	auto pe = zend(result);
	while(pe > result && (pe[-1] == ' '))
		*--pe = 0;
	return result;
}