#include "main.h"

struct classinfo {
	const char*				name[2];
	race_a					race;
	alignmenta				alignment;
	char					load; // Load + Str equal optimal carried weight
	char					hp; // Hit poinst maximum is HP + Constitution
	char					damage; // Damage dice (d4, d6, d8, d10 or d12)
	lootinfo				equiped;
	lootinfo				*armament, *defence, *gear, *special;
	char					choose_gear_count; // 0 is default (chooses one)
	adat<move_s, 8>			moves;
};
static lootinfo bard_weapon[] = {
	{{DuelingRapier}},
	{{RaggedBow, Arrows, SwordShort}},
	{},
};
static lootinfo bard_defence[] = {
	{{FineClothing}},
	{{LeatherArmour}},
	{},
};
static lootinfo bard_gear[] = {
	{{AdventuringGear}},
	{{Bandages}},
	{{HalflingPipeleaf}},
	{{}, 3},
	{},
};
static lootinfo bard_special[] = {
	{{Mandoline}},
	{{Lute}},
	{{Pipes}},
	{},
};
static lootinfo cleric_defence[] = {
	{{ChainMail}},
	{{Shield}},
	{},
};
static lootinfo cleric_weapon[] = {
	{{Warhammer}},
	{{Mace}},
	{{Staff, Bandages}},
	{},
};
static lootinfo cleric_gear[] = {
	{{AdventuringGear, DungeonRation}},
	{{HealingPotion}},
	{},
};
static lootinfo druid_defence[] = {
	{{LeatherArmour}},
	{{Shield}},
	{},
};
static lootinfo druid_weapon[] = {
	{{Club}},
	{{Staff}},
	{{Spear}},
	{},
};
static lootinfo druid_gear[] = {
	{{AdventuringGear}},
	{{Herbs}},
	{{HalflingPipeleaf}},
	{{Antitoxin, Antitoxin, Antitoxin}},
	{},
};
static lootinfo fighter_defence[] = {
	{{ChainMail, AdventuringGear}},
	{{ScaleMail}},
	{},
};
static lootinfo fighter_gear[] = {
	{{HealingPotion, HealingPotion}},
	{{Shield}},
	{{Antitoxin, DungeonRation, Herbs}},
	{{}, 22},
	{}
};
static lootinfo paladin_weapon[] = {
	{{Halberd}},
	{{SwordLong}},
	{}
};
static lootinfo paladin_gear[] = {
	{{AdventuringGear}},
	{{DungeonRation, HealingPotion}},
	{}
};
static lootinfo ranger_weapon[] = {
	{{HuntersBow, SwordShort}},
	{{HuntersBow, Spear}},
	{}
};
static lootinfo ranger_gear[] = {
	{{AdventuringGear, DungeonRation}},
	{{AdventuringGear, Arrows}},
	{}
};
static lootinfo theif_weapon[] = {
	{{Knife, SwordShort}},
	{{Rapier}},
	{}
};
static lootinfo theif_ranged[] = {
	{{ThrowingDagger}},
	{{RaggedBow, Arrows}},
	{}
};
static lootinfo theif_gear[] = {
	{{AdventuringGear}},
	{{HealingPotion}},
	{}
};
static lootinfo wizard_weapon[] = {
	{{Knife}},
	{{Staff}},
	{}
};
static lootinfo wizard_gear[] = {
	{{HealingPotion}},
	{{Antitoxin, Antitoxin, Antitoxin}},
	{}
};
static classinfo classinfos[] = {
	//
	{{"Bard", "����"}, {{Human, Elf}, 2}, {{Good, Neutral, Chaotic}, 3}, 9, 6, 6, {{DungeonRation}},
	bard_weapon, bard_defence, bard_gear, bard_special, 0,
	{{ArcaneArt, BardicLore, CharmingAndOpen, PortInTheStorm}, 4},
	},
	{{"Cleric", "������"}, {{Dwarf, Human}, 2}, {{Good, Lawful, Evil}, 3}, 10, 8, 6, {{DungeonRation, HolySymbol}},
	cleric_weapon, cleric_defence, cleric_gear, 0, 0,
	{{Deity, DivineGuidance, TurnUndead, Commune, CastASpell}, 5},
	},
	{{"Druid", "�����"}, {{Elf, Halfling, Human}, 3}, {{Good, Neutral, Chaotic}, 3}, 6, 6, 6, {},
	druid_weapon, druid_defence, druid_gear, 0, 0,
	{{BornOfTheSoil, ByNatureSustained, SpiritTongue, Shapeshifter, StudiedEssence}, 5},
	},
	{{"Fighter", "����"}, {{Dwarf, Elf, Halfling, Human}, 4}, {{Good, Neutral, Evil}, 3}, 12, 10, 10, {{DungeonRation}},
	0, fighter_defence, fighter_gear, 0, 2,
	{{BendBarsLiftGates, Armored, SignatureWeapon}, 3},
	},
	{{"Paladin", "�������"}, {{Human}, 1}, {{Lawful, Good}, 2}, 12, 10, 10, {{DungeonRation, ScaleMail, HolySymbol}},
	paladin_weapon, 0, paladin_gear, 0, 0,
	{{LayOnHands, Armored, IAmTheLaw, Quest}, 4},
	},
	{{"Ranger", "��������"}, {{Elf, Human}, 2}, {{Chaotic, Good, Neutral}, 3}, 11, 8, 8, {{DungeonRation, Arrows, LeatherArmour}},
	ranger_weapon, 0, ranger_gear, 0, 0,
	{{HuntAndTrack, CalledShot, AnimalCompanion, Command}, 4},
	},
	{{"Theif", "���"}, {{Halfling, Human}, 2}, {{Chaotic, Neutral, Evil}, 3}, 9, 6, 8, {{DungeonRation, LeatherArmour, Poison}, 10},
	theif_weapon, 0, theif_gear, theif_ranged, 0,
	{{TrapExpert, TricksOfTheTrade, Backstab, FlexibleMorals, Poisoner}, 5},
	},
	{{"Wizard", "���������"}, {{Elf, Human}, 2}, {{Good, Neutral, Evil}, 3}, 7, 4, 4, {{SpellBook, DungeonRation}},
	wizard_weapon, 0, wizard_gear, 0, 0,
	{{Spellbook, PrepareSpells, CastASpell, SpellDefense, Ritual}, 5},
	},
};
static_assert((sizeof(classinfos) / sizeof(classinfos[0])) == (Wizard + 1), "Classes count invalid");
template<> const char* getstr<class_s>(class_s value) {
	return classinfos[value].name[1];
}

template<> const char* getstr<alignment_s>(alignment_s value) {
	static const char* info[][2] = {
		{"Good", "������"},
		{"Lawful", "���������������"},
		{"Neutral", "�����������"},
		{"Chaotic", "���������"},
		{"Evil", "����"},
	};
	static_assert((sizeof(info) / sizeof(info[0])) == (Evil + 1), "Alignments count invalid");
	return info[value][1];
}

template<> const char* getstr<stat_s>(stat_s value) {
	static const char* info[][2] = {
		{"Strenght", "����"},
		{"Dexterity", "��������"},
		{"Constitution", "������������"},
		{"Intellegence", "���������"},
		{"Wisdow", "��������"},
		{"Charisma", "�������"},
	};
	return info[value][1];
}

template<> const char* getstr<race_s>(race_s value) {
	static const char* info[][2] = {
		{"Human", "�������"},
		{"Elf", "����"},
		{"Dwarf", "�����"},
		{"Halfling", "������"}
	};
	return info[value][1];
}

gender_s npc::choosegender(bool interactive) {
	logs::add(Male, "�������");
	logs::add(Female, "�������");
	return (gender_s)logs::input(interactive, true, "��� ��?");
}

race_s npc::chooserace(const race_a& source, bool interactive) {
	if(source.count == 1)
		return source.data[0];
	for(auto e : source)
		logs::add(e, getstr(e));
	return (race_s)logs::input(interactive, true, "��� ��?");
}

class_s npc::chooseclass(bool interactive) {
	for(auto e = Bard; e <= Wizard; e = (class_s)(e + 1))
		logs::add(e, getstr(e));
	return (class_s)logs::input(interactive, true, "��� �� ������ ������?");
}

alignment_s npc::choosealignment(const alignmenta& source, bool interactive) {
	if(source.count == 1)
		return source.data[0];
	for(auto e : source)
		logs::add(e, getstr(e));
	return (alignment_s)logs::input(interactive, true, "������ ���� [������������]?");
}

static void startabilities(hero& player, bool interactive) {
	static char stats[6] = {16, 15, 13, 12, 9, 8};
	int index = 0;
	while(index < lenghtof(stats)) {
		logs::add("��� ���������� ������������ ��������������: 16, 15, 13, 12, 9, 8.");
		for(auto m = Strenght; m <= Charisma; m = (stat_s)(m + 1)) {
			if(player.getraw(m))
				continue;
			logs::add(m, getstr(m));
		}
		auto m = (stat_s)logs::input(interactive, true, "���� �� ������ ��������� [%1i]?", stats[index]);
		player.setraw(m, stats[index]);
		index++;
	}
}

static void gears(hero& player, const char* title, lootinfo* values, int choose_count, bool interactive) {
	char temp[260];
	if(!values)
		return;
	char choosed[10] = {0};
	if(!choose_count)
		choose_count = 1;
	while(choose_count > 0) {
		player.getequipment(temp, "� ��� ����: ");
		if(temp[0])
			logs::add(temp);
		for(int i = 0; values[i].coins || values[i].item[0]; i++) {
			if(choosed[i])
				continue;
			logs::add(i, values[i].getitems(temp, true));
		}
		auto i = logs::input(interactive, true, title);
		choosed[i]++;
		player.apply(values[i]);
		choose_count--;
	}
}

static void startgears(hero& player, bool interactive) {
	player.apply(classinfos[player.type].equiped);
	switch(player.type) {
	case Bard:
		gears(player, "�������� ����������� ����������", classinfos[player.type].special, 0, interactive);
		break;
	case Theif:
		gears(player, "�������� ������������� ������", classinfos[player.type].special, 0, interactive);
		break;
	default:
		break;
	}
	gears(player, "�������� ���� [������]", classinfos[player.type].defence, 0, interactive);
	gears(player, "�������� ���� [������]", classinfos[player.type].armament, 0, interactive);
	gears(player, "�������� ���� [����������]", classinfos[player.type].gear, classinfos[player.type].choose_gear_count, interactive);
}

static void choose_known_spells(hero& player, bool interactive, int level, int count) {
	for(int i = 0; i < count; i++) {
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
			if(player.isknown(e))
				continue;
			if(player.getlevel(e) == 1)
				logs::add(e, getstr(e));
		}
		spell_s result = (spell_s)logs::input(interactive, true, "�������� ����������");
		player.setknown(result, true);
	}
}

static void startspells(hero& player, bool interactive) {
	if(!player.iscaster())
		return;
	// �������� ������������� �������� ����
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
		if(player.getlevel(e) == 0)
			player.setknown(e, true);
	}
	switch(player.type) {
	case Cleric:
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
			if(player.getlevel(e) == 1)
				player.setknown(e, true);
		}
		break;
	case Wizard:
		choose_known_spells(player, interactive, 1, 3);
		player.preparespells(interactive);
		break;
	}
}

static void startmoves(hero& player, bool interactive) {
	move_s basic_moves[] = {HackAndSlash,
		DefyDangerStreght, DefyDangerDexterity, DefyDangerConstitution, DefyDangerIntellegence, DefyDangerWisdow, DefyDangerCharisma,
		Parley, SpoutLore, DiscernRealities, Supply};
	auto& e = classinfos[player.type];
	for(auto v : e.moves)
		player.set(v, interactive);
	for(auto v : basic_moves)
		player.set(v, interactive);
}

void hero::create(bool interactive) {
	auto a1 = chooseclass(interactive);
	auto a2 = choosegender(interactive);
	create(interactive, a1, a2);
}

void hero::create(bool interactive, class_s type, gender_s gender) {
	clear();
	level = 1;
	this->type = type;
	this->gender = gender;
	this->race = chooserace(classinfos[type].race, interactive);
	this->alignment = choosealignment(classinfos[type].alignment, interactive);
	startabilities(*this, interactive);
	startmoves(*this, interactive);
	startgears(*this, interactive);
	startspells(*this, interactive);
	this->name = getrandomname(type, race, gender);
	this->hp = getmaxhits();
}

int	hero::getdamage(class_s value) {
	return classinfos[value].damage;
}

int	hero::gethits(class_s value) {
	return classinfos[value].hp;
}

int	hero::getload(class_s value) {
	return classinfos[value].load;
}