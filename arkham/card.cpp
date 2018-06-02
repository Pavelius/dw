#include "main.h"

static quest ancient_tome = {AnyLocation, "����������� ������� ������� ���.", {Lore, -1}, {{"������ ������ ��� ���� �� �� ����������."},
{"�� ������� ������� ��������� ������.", {AddSpell, Discard}},
}};
static quest old_journal = {AnyLocation, "������� ���������� ������� �������.", {Lore, -1}, {{"������ ������ ��� ���� �� �� ����������."},
{"� ������ ������� ����������� ������ � �������� ������ � ������� ������ � �������.", {Add3Clue, Discard}},
}};
static quest alien_statue = {AnyLocation, "�� ������ ���������� ������� ������. ������ ��� ����� � �� ��������� �����-�� ������� ������ �� ���.", {TestOneDie}, {{"�� ������������� ������ ���������.", {Lose2Stamina}},
{"�� �������� ������ ������ ������� ����.", {AddSpellOr3Clue}},
}};
static quest ancient_tablet = {AnyLocation, "������ �� ������� �������� �������� �����������, �� �� ���� ����� ����� �� ������������.", {TestTwoDie}, {{"����� ����������� �������� �� �������� ����� � �������.", {Add2Clue}},
{"����� ������� ������ ������� ��� ����������.", {AddSpell}},
}};
static quest book_of_dzyan = {AnyLocation, "�� ��������� ������� ������� ������ � �������.", {Lore, -1}, {{"������ ������ �� �� ����������."},
{"����� ����������� �������� �� ������ ����� ����������.", {AddSpell, Lose1Sanity, UsePart}}
}};
static quest langrange = {AnyLocation, 0, {}, {{"������������ ������� � ����� ������� �������� � ���� �������.", {RestoreAll}}}};
static const struct card_info {
	const char*		id;
	const char*		name;
	stat_s			type;
	char			deck_count;
	char			cost;
	roll_info		bonus[2];
	use_info		use;
	cflags<tag_s>	tags;
	monster_info	monster;
} card_data[] = {{"", ""},
// Common items
{".18 Derringer", "���������", CommonItem, 2, 3, {CombatCheck, 2}, {}, {PhysicalWeapon, CantStealOrLoose, OneHanded}},
{".38 Revolver", "���������", CommonItem, 2, 4, {CombatCheck, 3}, {}, {PhysicalWeapon, OneHanded}},
{".45 Automatic", "�����", CommonItem, 2, 4, {CombatCheck, 4}, {}, {PhysicalWeapon, OneHanded}},
{"Ancient Tome", "������� �����", CommonItem, 2, 4, {}, {{Lose2Movement}, &ancient_tome}, {ExhaustToEffect, Tome}},
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
{"Old Journal", "������ ������", CommonItem, 2, 1, {}, {{Lose1Movement}, &old_journal}, {ExhaustToEffect, Tome}},
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
{"AlienStatue", "������ �� ������� ����", UniqueItem, 1, 5, {}, {{Lose2Movement, Lose1Sanity}, &alien_statue}, {ExhaustToEffect}},
{"AncientTablet", "������� �����", UniqueItem, 1, 8, {}, {{Lose3Movement}, &ancient_tablet}, {DiscardAfterUse}},
{"BlueWatcherOfThePyramid", "����� ����� ��������", UniqueItem, 1, 4, {}, {{Lose2Stamina}}, {AutoCombatCheck, AutoGateCheck, DiscardAfterUse}},
{"BookOfDzyan", "����� ������", UniqueItem, 1, 3, {}, {{Lose2Movement}, &book_of_dzyan, 2}, {Tome}},
{"CabalaOfSaboth", "������ �������", UniqueItem, 2, 5},
{"CultesDesGoules", "������ ��������", UniqueItem, 2, 3},
{"DragonsEye", "���� �������", UniqueItem, 1, 6},
{"ElderSign", "���� �������", UniqueItem, 4, 5},
{"EnchantedBlade", "���������� ������", UniqueItem, 2, 6, {CombatCheck, 4}, {}, {OneHanded, MagicalWeapon}},
{"EnchantedJewelry", "������������� �������������", UniqueItem, 1, 3},
{"EnchantedKnife", "���������� ������", UniqueItem, 2, 5, {CombatCheck, 3}, {}, {OneHanded, MagicalWeapon}},
{"FluteOfTheOuterGods", "������ ������������ �����", UniqueItem, 1, 8, {}, {{Lose3Stamina, Lose3Sanity}}},
{"GateBox", "����� ����", UniqueItem, 1, 4},
{"HealingStone", "������ ���������", UniqueItem, 1, 8},
{"HolyWater", "������ ����", UniqueItem, 4, 4},
{"LampOfAlhazred", "����� ���-�������", UniqueItem, 1, 7},
{"NamelessCults", "���������� ������", UniqueItem, 2, 3, {}, {{Lose2Movement}, &ancient_tome}, {ExhaustToEffect, Tome}},
{"Necronomicon", "�����������", UniqueItem, 1, 6, {}, {{Lose2Movement}, &ancient_tome}, {ExhaustToEffect, Tome}},
{"ObsidianStatue", "������������ ������", UniqueItem, 1, 4},
{"PallidMask", "������� �����", UniqueItem, 1, 4},
{"PowderOfIbnGhazi", "������� ���-����", UniqueItem, 2, 6},
{"RubyOfRlyeh", "����� �'�����", UniqueItem, 1, 8},
{"SilverKey", "����������� ����", UniqueItem, 1, 4},
{"SwordOfGlory", "��� �����", UniqueItem, 1, 8},
{"TheKingInYellow", "������ � ������", UniqueItem, 2, 2, {}, {{Lose2Movement}, &ancient_tome}, {ExhaustToEffect, Tome}},
{"WardingStatue", "���������� ������", UniqueItem, 1, 6},
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
//
{"Byakhee", "������", Monster, 3, 0, {}, {}, {}, {Flying, -2, {-1, 1}, 1, {0, 2}, {}, "�������� � ���� ���������� ��� �������. �� ������� ������ � ������� �������� �������� - ��������������� � ����� ����� � ��������� ��������."}},
{"Chthonian", "�������", Monster, 2, 0, {}, {}, {}, {Unique, 1, {-2, 2}, 3, {-3, 3}}},
{"Cultist", "��������", Monster, 6, 0, {}, {}, {}, {Normal, -3, {0, 0}, 1, {1, 1}}},
{"Dark Young", "������ ������", Monster, 3, 0, {}, {}, {}, {Stationary, -2, {0, 3}, 3, {-1, 3}, {PhysicalResistance, NightmarishI}}},
{"Dhole", "", Monster, 3, 1, {}, {}, {}, {Normal, -1, {-1, 4}, 3, {-3, 4}, {PhysicalResistance, MagicalResistance, OvervelmingI, NightmarishI}}},
{"Dimension Shambler", "", Monster, 2, 0, {}, {}, {}, {Fast, -3, {-2, 1}, 1, {-2, 0}}},
{"Elder Thing", "", Monster, 2, 0, {}, {}, {}, {Normal, -2, {-3, 2}, 2, {0, 1}}},
{"Fire Vampire", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {-2, 2}, {Ambush, PhysicalResistance}}},
{"Zombie", "�����", Monster, 2, 0, {}, {}, {}, {Normal, 1, {-2, 2}, 3, {-3, 3}, {Undead}, "������� ��������� ������ ��������. ��� ����� ������ ������������ � ��� �������� ������ ����. ����� ������ �������������� ������ - ������ ��� ������� �����."}},
};
assert_enum(card, Zombie);
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

bool hero::usable(card_s i) const {
	for(auto a : card_data[i].use.before) {
		if(!isallow(a))
			return false;
	}
	return true;
}

char* item::getname(char* result, const char* result_maximum, card_s i, bool description, bool exhaused, char use) {
	auto need_scope = description || exhaused;
	result[0] = 0;
	if(need_scope)
		szprints(zend(result), result_maximum, "[");
	if(exhaused && !description)
		szprints(zend(result), result_maximum, "~");
	szprints(zend(result), result_maximum, card_data[i].name);
	auto use_maximum = card_data[i].use.usable;
	if(use && use_maximum)
		szprints(zend(result), result_maximum, "(%1i/%2i)", use, use_maximum);
	if(need_scope)
		szprints(zend(result), result_maximum, "]");
	if(description) {
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
	}
	auto pe = zend(result);
	while(pe > result && (pe[-1] == ' '))
		*--pe = 0;
	return result;
}

char monster::get(stat_s id) {
	switch(id) {
	case EvadeCheck: return card_data[type].monster.awareness;
	case HorrorCheck: return card_data[type].monster.horror[0];
	case Sanity: return card_data[type].monster.horror[1];
	case CombatCheck: return card_data[type].monster.combat[0];
	case Stamina: return card_data[type].monster.combat[1];
	case Fight: return card_data[type].monster.toughness;
	default: return 0;
	}
}

bool monster::is(monster_flag_s id) const {
	return card_data[type].monster.flags.is(id);
}

const char* monster::getname() const {
	return card_data[type].name;
}

const char* monster::gettext() const {
	return card_data[type].monster.text;
}

const use_info& item::getuse(card_s i) {
	return card_data[i].use;
}

char item::getmark(card_s i) {
	return card_data[i].use.usable;
}