#include "main.h"

static looti bard_weapon[] = {
	{{DuelingRapier}},
	{{RaggedBow, Arrows, SwordShort}},
	{},
};
static looti bard_defence[] = {
	{{FineClothing}},
	{{LeatherArmour}},
	{},
};
static looti bard_gear[] = {
	{{AdventuringGear}},
	{{Bandages}},
	{{HalflingPipeleaf}},
	{{}, 3},
	{},
};
static looti bard_special[] = {
	{{Mandoline}},
	{{Lute}},
	{{Pipes}},
	{},
};
static looti cleric_defence[] = {
	{{ChainMail}},
	{{Shield}},
	{},
};
static looti cleric_weapon[] = {
	{{Warhammer}},
	{{Mace}},
	{{Staff, Bandages}},
	{},
};
static looti cleric_gear[] = {
	{{AdventuringGear, DungeonRation}},
	{{HealingPotion}},
	{},
};
static looti druid_defence[] = {
	{{LeatherArmour}},
	{{Shield}},
	{},
};
static looti druid_weapon[] = {
	{{Club}},
	{{Staff}},
	{{Spear}},
	{},
};
static looti druid_gear[] = {
	{{AdventuringGear}},
	{{Herbs}},
	{{HalflingPipeleaf}},
	{{Antitoxin, Antitoxin, Antitoxin}},
	{},
};
static looti fighter_defence[] = {
	{{ChainMail, AdventuringGear}},
	{{ScaleMail}},
	{},
};
static looti fighter_gear[] = {
	{{HealingPotion, HealingPotion}},
	{{Shield}},
	{{Antitoxin, DungeonRation, Herbs}},
	{{}, 22},
	{}
};
static looti paladin_weapon[] = {
	{{Halberd}},
	{{SwordLong}},
	{}
};
static looti paladin_gear[] = {
	{{AdventuringGear}},
	{{DungeonRation, HealingPotion}},
	{}
};
static looti ranger_weapon[] = {
	{{HuntersBow, SwordShort}},
	{{HuntersBow, Spear}},
	{}
};
static looti ranger_gear[] = {
	{{AdventuringGear, DungeonRation}},
	{{AdventuringGear, Arrows}},
	{}
};
static looti theif_weapon[] = {
	{{Knife, SwordShort}},
	{{Rapier}},
	{}
};
static looti theif_ranged[] = {
	{{ThrowingDagger}},
	{{RaggedBow, Arrows}},
	{}
};
static looti theif_gear[] = {
	{{AdventuringGear}},
	{{HealingPotion}},
	{}
};
static looti wizard_weapon[] = {
	{{Knife}},
	{{Staff}},
	{}
};
static looti wizard_gear[] = {
	{{HealingPotion}},
	{{Antitoxin, Antitoxin, Antitoxin}},
	{}
};
classi bsmeta<classi>::elements[] = {
	{"Bard", "Бард", {Human, Elf}, {Good, Neutral, Chaotic}, 9, 6, 6, {{DungeonRation}},
	bard_weapon, bard_defence, bard_gear, bard_special, 0,
	{ArcaneArt, BardicLore, CharmingAndOpen, PortInTheStorm},
	},
	{"Cleric", "Клерик", {Dwarf, Human}, {Good, Lawful, Evil}, 10, 8, 6, {{DungeonRation, HolySymbol}},
	cleric_weapon, cleric_defence, cleric_gear, 0, 0,
	{Deity, DivineGuidance, TurnUndead, Commune, CastASpell},
	},
	{"Druid", "Друид", {Elf, Halfling, Human}, {Good, Neutral, Chaotic}, 6, 6, 6, {},
	druid_weapon, druid_defence, druid_gear, 0, 0,
	{BornOfTheSoil, ByNatureSustained, SpiritTongue, Shapeshifter, StudiedEssence},
	},
	{"Fighter", "Воин", {Dwarf, Elf, Halfling, Human}, {Good, Neutral, Evil}, 12, 10, 10, {{DungeonRation}},
	0, fighter_defence, fighter_gear, 0, 2,
	{BendBarsLiftGates, Armored, SignatureWeapon},
	},
	{"Paladin", "Паладин", {Human}, {Lawful, Good}, 12, 10, 10, {{DungeonRation, ScaleMail, HolySymbol}},
	paladin_weapon, 0, paladin_gear, 0, 0,
	{LayOnHands, Armored, IAmTheLaw, Quest},
	},
	{"Ranger", "Рейнджер", {Elf, Human}, {Chaotic, Good, Neutral}, 11, 8, 8, {{DungeonRation, Arrows, LeatherArmour}},
	ranger_weapon, 0, ranger_gear, 0, 0,
	{HuntAndTrack, CalledShot, AnimalCompanion, Command},
	},
	{"Theif", "Вор", {Halfling, Human}, {Chaotic, Neutral, Evil}, 9, 6, 8, {{DungeonRation, LeatherArmour, Poison}, 10},
	theif_weapon, 0, theif_gear, theif_ranged, 0,
	{TrapExpert, TricksOfTheTrade, Backstab, FlexibleMorals, Poisoner},
	},
	{"Wizard", "Волшебник", {Elf, Human}, {Good, Neutral, Evil}, 7, 4, 4, {{SpellBook, DungeonRation}},
	wizard_weapon, 0, wizard_gear, 0, 0,
	{Spellbook, PrepareSpells, CastASpell, SpellDefense, Ritual},
	},
};
assert_enum(class, Wizard);

gender_s npc::choosegender(bool interactive) {
	an.add(Male, getstr(Male));
	an.add(Female, getstr(Female));
	return (gender_s)an.choose(interactive, true, "Кто вы?");
}

race_s npc::chooserace(const race_a& source, bool interactive) {
	for(auto e = Human; e <= Human; e = (race_s)(e + 1))
		an.add(e, getstr(e));
	return (race_s)an.choose(interactive, true, "Кто вы?");
}

class_s npc::chooseclass(bool interactive) {
	for(auto e = Bard; e <= Wizard; e = (class_s)(e + 1))
		an.add(e, getstr(e));
	return (class_s)an.choose(interactive, true, "Кем вы будете играть?");
}

alignment_s npc::choosealignment(const alignmenta& source, bool interactive) {
	for(auto e = Good; e <= Evil; e = (alignment_s)(e + 1)) {
		if(source.is(e))
			an.add(e, getstr(e));
	}
	return (alignment_s)an.choose(interactive, true, "Каково ваше [мировозрение]?");
}

static void startabilities(hero& player, bool interactive) {
	static char stats[6] = {16, 15, 13, 12, 9, 8};
	int index = 0;
	while(index < lenof(stats)) {
		sb.add("Вам необходимо распределить характеристики: 16, 15, 13, 12, 9, 8.");
		for(auto m = Strenght; m <= Charisma; m = (stat_s)(m + 1)) {
			if(player.getraw(m))
				continue;
			an.add(m, getstr(m));
		}
		auto m = (stat_s)an.choose(interactive, true, "Куда вы хотите поставить [%1i]?", stats[index]);
		player.setraw(m, stats[index]);
		index++;
	}
}

static void gears(hero& player, const char* title, looti* values, int choose_count, bool interactive) {
	char temp[260];
	if(!values)
		return;
	char choosed[10] = {0};
	if(!choose_count)
		choose_count = 1;
	while(choose_count > 0) {
		player.getequipment(temp, zendof(temp), "У вас есть: ");
		if(temp[0])
			sb.add(temp);
		for(int i = 0; values[i].coins || values[i].items[0]; i++) {
			if(choosed[i])
				continue;
			stringbuilder sb(temp);
			values[i].getitems(sb, true);
			an.add(i, temp);
		}
		auto i = an.choose(interactive, true, title);
		choosed[i]++;
		player.apply(values[i]);
		choose_count--;
	}
}

static void startgears(hero& player, bool interactive) {
	auto& ed = bsmeta<classi>::elements[player.type];
	player.apply(ed.equiped);
	switch(player.type) {
	case Bard:
		gears(player, "Выберите музыкальный инструмент", ed.special, 0, interactive);
		break;
	case Theif:
		gears(player, "Выберите дистанционное оружие", ed.special, 0, interactive);
		break;
	default:
		break;
	}
	gears(player, "Выберите вашу [защиту]", ed.defence, 0, interactive);
	gears(player, "Выберите ваше [оружие]", ed.armament, 0, interactive);
	gears(player, "Выберите ваше [снаряжение]", ed.gear, ed.choose_gear_count, interactive);
}

static void choose_known_spells(hero& player, bool interactive, int level, int count) {
	for(int i = 0; i < count; i++) {
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
			if(player.isknown(e))
				continue;
			if(player.getlevel(e) == 1)
				an.add(e, getstr(e));
		}
		spell_s result = (spell_s)an.choose(interactive, true, "Выберите заклинание");
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
	auto& e = bsmeta<classi>::elements[player.type];
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
	this->race = chooserace(bsmeta<classi>::elements[type].race, interactive);
	this->alignment = choosealignment(bsmeta<classi>::elements[type].alignment, interactive);
	startabilities(*this, interactive);
	startmoves(*this, interactive);
	startgears(*this, interactive);
	startspells(*this, interactive);
	this->name = getrandomname(type, race, gender);
	this->hp = getmaxhits();
	this->gender = gender;
}

int	hero::getdamage(class_s value) {
	return bsmeta<classi>::elements[value].damage;
}

int	hero::gethits(class_s value) {
	return bsmeta<classi>::elements[value].hp;
}

int	hero::getload(class_s value) {
	return bsmeta<classi>::elements[value].load;
}