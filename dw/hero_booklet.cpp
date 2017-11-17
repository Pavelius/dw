#include "main.h"

struct chooseinfo
{
	item_s					item[4];
	short unsigned			coins;
	char*					getitems(char* result, bool description) const;
};
struct classinfo
{
	const char*				name[2];
	race_a					race;
	alignment_a				alignment;
	char					load; // Load + Str equal optimal carried weight
	char					hp; // Hit poinst maximum is HP + Constitution
	char					damage; // Damage dice (d4, d6, d8, d10 or d12)
	chooseinfo				equiped;
	chooseinfo				*armament, *defence, *gear, *special;
	char					choose_gear_count; // 0 is default (chooses one)
	adat<move_s, 8>			moves;
};
static chooseinfo bard_weapon[] = {
	{{DuelingRapier}},
	{{RaggedBow, Arrows, SwordShort}},
	{},
};
static chooseinfo bard_defence[] = {
	{{FineClothing}},
	{{LeatherArmour}},
	{},
};
static chooseinfo bard_gear[] = {
	{{AdventuringGear}},
	{{Bandages}},
	{{HalflingPipeleaf}},
	{{}, 3},
	{},
};
static chooseinfo bard_special[] = {
	{{Mandoline}},
	{{Lute}},
	{{Pipes}},
	{},
};
static chooseinfo cleric_defence[] = {
	{{ChainMail}},
	{{Shield}},
	{},
};
static chooseinfo cleric_weapon[] = {
	{{Warhammer}},
	{{Mace}},
	{{Staff, Bandages}},
	{},
};
static chooseinfo cleric_gear[] = {
	{{AdventuringGear, DungeonRation}},
	{{HealingPotion}},
	{},
};
static chooseinfo druid_defence[] = {
	{{LeatherArmour}},
	{{Shield}},
	{},
};
static chooseinfo druid_weapon[] = {
	{{Club}},
	{{Staff}},
	{{Spear}},
	{},
};
static chooseinfo druid_gear[] = {
	{{AdventuringGear}},
	{{Herbs}},
	{{HalflingPipeleaf}},
	{{Antitoxin, Antitoxin, Antitoxin}},
	{},
};
static chooseinfo fighter_defence[] = {
	{{ChainMail, AdventuringGear}},
	{{ScaleMail}},
	{},
};
static chooseinfo fighter_gear[] = {
	{{HealingPotion, HealingPotion}},
	{{Shield}},
	{{Antitoxin, DungeonRation, Herbs}},
	{{}, 22},
	{}
};
static chooseinfo paladin_weapon[] = {
	{{Halberd}},
	{{SwordLong}},
	{}
};
static chooseinfo paladin_gear[] = {
	{{AdventuringGear}},
	{{DungeonRation, HealingPotion}},
	{}
};
static chooseinfo ranger_weapon[] = {
	{{HuntersBow, SwordShort}},
	{{HuntersBow, Spear}},
	{}
};
static chooseinfo ranger_gear[] = {
	{{AdventuringGear, DungeonRation}},
	{{AdventuringGear, Arrows}},
	{}
};
static chooseinfo theif_weapon[] = {
	{{Knife, SwordShort}},
	{{Rapier}},
	{}
};
static chooseinfo theif_ranged[] = {
	{{ThrowingDagger}},
	{{RaggedBow, Arrows}},
	{}
};
static chooseinfo theif_gear[] = {
	{{AdventuringGear}},
	{{HealingPotion}},
	{}
};
static chooseinfo wizard_weapon[] = {
	{{Knife}},
	{{Staff}},
	{}
};
static chooseinfo wizard_gear[] = {
	{{HealingPotion}},
	{{Antitoxin, Antitoxin, Antitoxin}},
	{}
};
static classinfo classinfos[] = {
	//
	{{"Bard", "Бард"}, {{Human, Elf}, 2}, {{Good, Neutral, Chaotic}, 3}, 9, 6, 6, {{DungeonRation}},
	bard_weapon, bard_defence, bard_gear, bard_special, 0,
	{{ArcaneArt, BardicLore, CharmingAndOpen, PortInTheStorm}, 4},
	},
	{{"Cleric", "Клерик"}, {{Dwarf, Human}, 2}, {{Good, Lawful, Evil}, 3}, 10, 8, 6, {{DungeonRation, HolySymbol}},
	cleric_weapon, cleric_defence, cleric_gear, 0, 0,
	{{Deity, DivineGuidance, TurnUndead, Commune, CastASpell}, 5},
	},
	{{"Druid", "Друид"}, {{Elf, Halfling, Human}, 3}, {{Good, Neutral, Chaotic}, 3}, 6, 6, 6, {},
	druid_weapon, druid_defence, druid_gear, 0, 0,
	{{BornOfTheSoil, ByNatureSustained, SpiritTongue, Shapeshifter, StudiedEssence}, 5},
	},
	{{"Fighter", "Воин"}, {{Dwarf, Elf, Halfling, Human}, 4}, {{Good, Neutral, Evil}, 3}, 12, 10, 10, {{DungeonRation}},
	0, fighter_defence, fighter_gear, 0, 2,
	{{BendBarsLiftGates, Armored, SignatureWeapon}, 3},
	},
	{{"Paladin", "Паладин"}, {{Human}, 1}, {{Lawful, Good}, 2}, 12, 10, 10, {{DungeonRation, ScaleMail, HolySymbol}},
	paladin_weapon, 0, paladin_gear, 0, 0,
	{{LayOnHands, Armored, IAmTheLaw, Quest}, 4},
	},
	{{"Ranger", "Рейнджер"}, {{Elf, Human}, 2}, {{Chaotic, Good, Neutral}, 3}, 11, 8, 8, {{DungeonRation, Arrows, LeatherArmour}},
	ranger_weapon, 0, ranger_gear, 0, 0,
	{{HuntAndTrack, CalledShot, AnimalCompanion, Command}, 4},
	},
	{{"Theif", "Вор"}, {{Halfling, Human}, 2}, {{Chaotic, Neutral, Evil}, 3}, 9, 6, 8, {{DungeonRation, LeatherArmour, Poison}, 10},
	theif_weapon, 0, theif_gear, theif_ranged, 0,
	{{TrapExpert, TricksOfTheTrade, Backstab, FlexibleMorals, Poisoner}, 5},
	},
	{{"Wizard", "Волшебник"}, {{Elf, Human}, 2}, {{Good, Neutral, Evil}, 3}, 7, 4, 4, {{SpellBook, DungeonRation}},
	wizard_weapon, 0, wizard_gear, 0, 0,
	{{Spellbook, PrepareSpells, CastASpell, SpellDefense, Ritual}, 5},
	},
};
static_assert((sizeof(classinfos) / sizeof(classinfos[0])) == (Wizard + 1), "Classes count invalid");
template<> const char* getstr<class_s>(class_s value)
{
	return classinfos[value].name[1];
}

template<> const char* getstr<alignment_s>(alignment_s value)
{
	static const char* info[][2] = {
		{"Good", "Добрый"},
		{"Lawful", "Законопослушный"},
		{"Neutral", "Нейтральный"},
		{"Chaotic", "Хаотичный"},
		{"Evil", "Злой"},
	};
	static_assert((sizeof(info) / sizeof(info[0])) == (Evil + 1), "Alignments count invalid");
	return info[value][1];
}

template<> const char* getstr<stat_s>(stat_s value)
{
	static const char* info[][2] = {
		{"Strenght", "Сила"},
		{"Dexterity", "Ловкость"},
		{"Constitution", "Телосложение"},
		{"Intellegence", "Интеллект"},
		{"Wisdow", "Мудрость"},
		{"Charisma", "Харизма"},
	};
	return info[value][1];
}

template<> const char* getstr<race_s>(race_s value)
{
	static const char* info[][2] = {
		{"Human", "Человек"},
		{"Elf", "Эльф"},
		{"Dwarf", "Дварф"},
		{"Halfling", "Хоббит"}
	};
	return info[value][1];
}

char* chooseinfo::getitems(char* result, bool description) const
{
	result[0] = 0;
	int count = 1;
	for(int j = 0; item[j]; j++)
	{
		if(item[j] == item[j + 1])
		{
			count++;
			continue;
		}
		if(result[0])
			zcat(result, ", ");
		if(count > 1)
			szprint(zend(result), "%1i ", count);
		::item it(item[j]);
		it.getname(zend(result), description);
		count = 1;
	}
	if(coins)
	{
		if(result[0])
			zcat(result, ", ");
		szprint(zend(result), "%1i монет", coins);
	}
	if(result[0])
		zcat(result, ".");
	return result;
}

static void apply(hero& player, chooseinfo& e)
{
	for(int j = 0; e.item[j]; j++)
		player.set(item(e.item[j]));
	if(e.coins)
		player.addcoins(e.coins);
}

gender_s npc::choosegender(bool interactive)
{
	logs::add(Male, "Мужчина");
	logs::add(Female, "Женщина");
	return (gender_s)logs::input(interactive, true, "Кто вы?");
}

race_s npc::chooserace(const race_a& source, bool interactive)
{
	if(source.count == 1)
		return source.data[0];
	for(auto e : source)
		logs::add(e, getstr(e));
	return (race_s)logs::input(interactive, true, "Кто вы?");
}

class_s npc::chooseclass(bool interactive)
{
	for(auto e = Bard; e <= Wizard; e = (class_s)(e + 1))
		logs::add(e, getstr(e));
	return (class_s)logs::input(interactive, true, "Кем вы будете играть?");
}

alignment_s npc::choosealignment(const alignment_a& source, bool interactive)
{
	if(source.count == 1)
		return source.data[0];
	for(auto e : source)
		logs::add(e, getstr(e));
	return (alignment_s)logs::input(interactive, true, "Каково ваше [мировозрение]?");
}

static stat_s get_zero_stat(hero& player)
{
	for(auto i = Strenght; i <= Charisma; i = (stat_s)(i + 1))
	{
		if(!player.stats[i])
			return i;
	}
	return Strenght;
}

static void startabilities(hero& player, bool interactive)
{
	static char stats[6] = {16, 15, 13, 12, 9, 8};
	int index = 0;
	while(index < 5)
	{
		logs::add("Вам необходимо распределить характеристики: 16, 15, 13, 12, 9, 8.");
		for(auto m = Strenght; m <= Charisma; m = (stat_s)(m + 1))
		{
			if(player.stats[m])
				continue;
			logs::add(m, getstr(m));
		}
		int m = logs::input(interactive, true, "Куда вы хотите поставить [%1i]?", stats[index]);
		player.stats[m] = stats[index];
		index++;
	}
	player.stats[get_zero_stat(player)] = stats[index];
}

static void gears(hero& player, const char* title, chooseinfo* values, int choose_count, bool interactive)
{
	char temp[260];
	if(!values)
		return;
	char choosed[10] = {0};
	if(!choose_count)
		choose_count = 1;
	while(choose_count > 0)
	{
		player.getequipment(temp, "У вас есть: ");
		if(temp[0])
			logs::add(temp);
		for(int i = 0; values[i].coins || values[i].item[0]; i++)
		{
			if(choosed[i])
				continue;
			logs::add(i, values[i].getitems(temp, true));
		}
		auto i = logs::input(interactive, true, title);
		choosed[i]++;
		apply(player, values[i]);
		choose_count--;
	}
}

static void startgears(hero& player, bool interactive)
{
	apply(player, classinfos[player.type].equiped);
	switch(player.type)
	{
	case Bard:
		gears(player, "Выберите музыкальный инструмент", classinfos[player.type].special, 0, interactive);
		break;
	case Theif:
		gears(player, "Выберите дистанционное оружие", classinfos[player.type].special, 0, interactive);
		break;
	default:
		break;
	}
	gears(player, "Выберите вашу [защиту]", classinfos[player.type].defence, 0, interactive);
	gears(player, "Выберите ваше [оружие]", classinfos[player.type].armament, 0, interactive);
	gears(player, "Выберите ваше [снаряжение]", classinfos[player.type].gear, classinfos[player.type].choose_gear_count, interactive);
}

static void choose_known_spells(hero& player, bool interactive, int level, int count)
{
	for(int i = 0; i<count; i++)
	{
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
		{
			if(player.isknown(e))
				continue;
			if(player.getlevel(e) == 1)
				logs::add(e, getstr(e));
		}
		spell_s result = (spell_s)logs::input(interactive, true, "Выберите заклинание");
		player.setknown(result, true);
	}
}

static void startspells(hero& player, bool interactive)
{
	if(!player.iscaster())
		return;
	// Кантрипы автоматически известны всем
	for(auto e = FirstSpell; e<=LastSpell; e = (spell_s)(e+1))
	{
		if(player.getlevel(e) == 0)
			player.setknown(e, true);
	}
	switch(player.type)
	{
	case Cleric:
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
		{
			if(player.getlevel(e) == 1)
				player.setknown(e, true);
		}
		break;
	case Wizard:
		choose_known_spells(player, interactive, 1, 3);
		break;
	}
}

static void startmoves(hero& player, bool interactive)
{
	auto& e = classinfos[player.type];
	for(auto v : e.moves)
		player.set(v, interactive);
}

void hero::create(bool interactive)
{
	auto a1 = chooseclass(interactive);
	auto a2 = choosegender(interactive);
	create(interactive, a1, a2);
}

void hero::create(bool interactive, class_s type, gender_s gender)
{
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

int	hero::getdamage(class_s value)
{
	return classinfos[value].damage;
}

int	hero::gethits(class_s value)
{
	return classinfos[value].hp;
}

int	hero::getload(class_s value)
{
	return classinfos[value].load;
}