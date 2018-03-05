#include "main.h"

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
struct class_info {
	const char*	id;
	const char*	name;
	race_a		race;
	alignmenta	alignment;
	char		load; // Load + Str equal optimal carried weight
	char		hp; // Hit poinst maximum is HP + Constitution
	char		damage; // Damage dice (d4, d6, d8, d10 or d12)
	lootinfo	equiped;
	lootinfo	*armament, *defence, *gear, *special;
	char		choose_gear_count; // 0 is default (chooses one)
	adat<move_s, 8> moves;
};
static class_info class_data[] = {
	//
	{"Bard", "Бард", {Human, Elf}, {Good, Neutral, Chaotic}, 9, 6, 6, {{DungeonRation}},
	bard_weapon, bard_defence, bard_gear, bard_special, 0,
	{{ArcaneArt, BardicLore, CharmingAndOpen, PortInTheStorm}, 4},
	},
	{"Cleric", "Клерик", {Dwarf, Human}, {Good, Lawful, Evil}, 10, 8, 6, {{DungeonRation, HolySymbol}},
	cleric_weapon, cleric_defence, cleric_gear, 0, 0,
	{{Deity, DivineGuidance, TurnUndead, Commune, CastASpell}, 5},
	},
	{"Druid", "Друид", {Elf, Halfling, Human}, {Good, Neutral, Chaotic}, 6, 6, 6, {},
	druid_weapon, druid_defence, druid_gear, 0, 0,
	{{BornOfTheSoil, ByNatureSustained, SpiritTongue, Shapeshifter, StudiedEssence}, 5},
	},
	{"Fighter", "Воин", {Dwarf, Elf, Halfling, Human}, {Good, Neutral, Evil}, 12, 10, 10, {{DungeonRation}},
	0, fighter_defence, fighter_gear, 0, 2,
	{{BendBarsLiftGates, Armored, SignatureWeapon}, 3},
	},
	{"Paladin", "Паладин", {Human}, {Lawful, Good}, 12, 10, 10, {{DungeonRation, ScaleMail, HolySymbol}},
	paladin_weapon, 0, paladin_gear, 0, 0,
	{{LayOnHands, Armored, IAmTheLaw, Quest}, 4},
	},
	{"Ranger", "Рейнджер", {Elf, Human}, {Chaotic, Good, Neutral}, 11, 8, 8, {{DungeonRation, Arrows, LeatherArmour}},
	ranger_weapon, 0, ranger_gear, 0, 0,
	{{HuntAndTrack, CalledShot, AnimalCompanion, Command}, 4},
	},
	{"Theif", "Вор", {Halfling, Human}, {Chaotic, Neutral, Evil}, 9, 6, 8, {{DungeonRation, LeatherArmour, Poison}, 10},
	theif_weapon, 0, theif_gear, theif_ranged, 0,
	{{TrapExpert, TricksOfTheTrade, Backstab, FlexibleMorals, Poisoner}, 5},
	},
	{"Wizard", "Волшебник", {Elf, Human}, {Good, Neutral, Evil}, 7, 4, 4, {{SpellBook, DungeonRation}},
	wizard_weapon, 0, wizard_gear, 0, 0,
	{{Spellbook, PrepareSpells, CastASpell, SpellDefense, Ritual}, 5},
	},
};
assert_enum(class, Wizard);
getstr_enum(class);
bsreq class_type[] = {
	BSREQ(class_info, id, text_type),
	BSREQ(class_info, name, text_type),
	BSREQ(class_info, race, number_type),
	BSREQ(class_info, alignment, number_type),
	BSREQ(class_info, load, number_type),
	BSREQ(class_info, hp, number_type),
	BSREQ(class_info, damage, number_type),
{}
};
BSMETA(class);

template<> const char* getstr<stat_s>(stat_s value) {
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

gender_s npc::choosegender(bool interactive) {
	logs::add(Male, "Мужчина");
	logs::add(Female, "Женщина");
	return (gender_s)logs::input(interactive, true, "Кто вы?");
}

race_s npc::chooserace(const race_a& source, bool interactive) {
	for(auto e : source)
		logs::add(e, getstr(e));
	return (race_s)logs::inputsg(interactive, true, "Кто вы?");
}

class_s npc::chooseclass(bool interactive) {
	for(auto e = Bard; e <= Wizard; e = (class_s)(e + 1))
		logs::add(e, getstr(e));
	return (class_s)logs::inputsg(interactive, true, "Кем вы будете играть?");
}

alignment_s npc::choosealignment(const alignmenta& source, bool interactive) {
	for(auto e : source)
		logs::add(e, getstr(e));
	return (alignment_s)logs::inputsg(interactive, true, "Каково ваше [мировозрение]?");
}

static void startabilities(hero& player, bool interactive) {
	static char stats[6] = {16, 15, 13, 12, 9, 8};
	int index = 0;
	while(index < lenghtof(stats)) {
		logs::add("Вам необходимо распределить характеристики: 16, 15, 13, 12, 9, 8.");
		for(auto m = Strenght; m <= Charisma; m = (stat_s)(m + 1)) {
			if(player.getraw(m))
				continue;
			logs::add(m, getstr(m));
		}
		auto m = (stat_s)logs::input(interactive, true, "Куда вы хотите поставить [%1i]?", stats[index]);
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
		player.getequipment(temp, "У вас есть: ");
		if(temp[0])
			logs::add(temp);
		for(int i = 0; values[i].coins || values[i].items[0]; i++) {
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
	player.apply(class_data[player.type].equiped);
	switch(player.type) {
	case Bard:
		gears(player, "Выберите музыкальный инструмент", class_data[player.type].special, 0, interactive);
		break;
	case Theif:
		gears(player, "Выберите дистанционное оружие", class_data[player.type].special, 0, interactive);
		break;
	default:
		break;
	}
	gears(player, "Выберите вашу [защиту]", class_data[player.type].defence, 0, interactive);
	gears(player, "Выберите ваше [оружие]", class_data[player.type].armament, 0, interactive);
	gears(player, "Выберите ваше [снаряжение]", class_data[player.type].gear, class_data[player.type].choose_gear_count, interactive);
}

static void choose_known_spells(hero& player, bool interactive, int level, int count) {
	for(int i = 0; i < count; i++) {
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
			if(player.isknown(e))
				continue;
			if(player.getlevel(e) == 1)
				logs::add(e, getstr(e));
		}
		spell_s result = (spell_s)logs::input(interactive, true, "Выберите заклинание");
		player.setknown(result, true);
	}
}

static void startspells(hero& player, bool interactive) {
	if(!player.iscaster())
		return;
	// Кантрипы автоматически известны всем
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
		player.preparespells(interactive);
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
	auto& e = class_data[player.type];
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
	this->race = chooserace(class_data[type].race, interactive);
	this->alignment = choosealignment(class_data[type].alignment, interactive);
	startabilities(*this, interactive);
	startmoves(*this, interactive);
	startgears(*this, interactive);
	startspells(*this, interactive);
	this->name = getrandomname(type, race, gender);
	this->hp = getmaxhits();
	this->gender = gender;
}

int	hero::getdamage(class_s value) {
	return class_data[value].damage;
}

int	hero::gethits(class_s value) {
	return class_data[value].hp;
}

int	hero::getload(class_s value) {
	return class_data[value].load;
}