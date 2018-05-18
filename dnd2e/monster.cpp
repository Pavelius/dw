#include "main.h"

const short HD = 8;

enum frequency_s : unsigned char {
	Common, Uncommon, Rare, VeryRare,
};
enum intellegence_s : unsigned char {
	None, AnimalInt, Semi, Low,
	Average, Very, Hight, Exeptional, Genius,
	SupraGenius, Godlike,
};
// TODO: flexible leader generation table. Use percent, race, class and count (level or monster count).
struct leaderinfo {
	short		per_creatures;
	char		chance;
	race_s		race;
	class_s		type;
	dice		count;
	monster_s	monster;
};
// Variable weapon for encountered creatures
struct custom_weapons {
	char		chance;
	item_s		data[7];
};
static custom_weapons dwarf_weapon[] = {
	{15, ShortSword, Crossbow},
	{10, ShortSword, Halberd},
	{20, ShortSword, Spear},
	{10, Axe, Crossbow},
	{25, Axe, Hammer},
	{10, Axe, Mace},
	{10, Hammer, Pick},
};
static dungeon_encounter human_subtable[] = {
	{25, Bandit, {5, 15}},
	{30, Bandit, {3, 9}},
	{45, Bandit, {5, 15}},
	{100, Character, {2, 5}},
};
static dungeon_encounter monster_level_1[] = {
	{2, AntGiant, {1, 4}},
	{4, Badger, {1, 4}},
	{14, BeetleFire, {1, 4}},
	{15, DemonManes, {1, 4}},
	{17, DwarfFolk, {4, 14}},
	{18, EarSeeker, {1}},
	{19, ElfFolk, {3, 11}},
	{21, GnomeFolk, {5, 15}},
	{26, Goblin, {6, 15}},
	{28, HalflingFolk, {9, 16}},
	{33, Hobgoblin, {2, 8}},
	{48, Character, {0}, human_subtable},
	{54, Kobold, {6, 18}},
	{66, Orc, {7, 12}},
	{70, Piercer, {1, 3}},
	{83, RatGiant, {5, 20}},
	{85, RotGrub, {1, 3}},
	{96, Shrieker, {1, 2}},
	{98, Skieleton, {1, 4}},
	{100, Zombie, {1, 3}},
};
static struct monster {
	const char*				id;
	const char*				name;
	const char*				nameof;
	frequency_s				frequency;
	dice					appearing;
	char					ac;
	char					mv;
	dice					HD;
	char					lair;
	const char*				treasure;
	dice					damage[3];
	intellegence_s			intellegence;
	alignment_s				alignment;
	size_s					size;
	feat_s					feats[8];
	aref<custom_weapons>	custom_weapon;
} monster_data[] = {
	{"character", "персонаж", "персонажей", Common, {1}, 10, 12, {1, HD}, 0, 0, {{1, 2}}, Average, Neutral},
	{"ant", "муравей", "муравьев", Rare, {1, 100}, 3, 18, {2, HD}, 10, "Q3S", {{1, 6}}, Low, LawfulEvil, Small},
	{"badger", "барсук", "барсуков", Uncommon, {1, 4, 1}, 4, 6, {1, HD, 2}, 0, 0, {{1, 2}, {1, 2}, {1, 3}}, AnimalInt, Neutral, Small},
	{"bandit", "бандит", "бандитов", Common, {2, 10, 0, 10}, 10, 12, {1, 6}, 20, "MA", {LeatherArmor, ShortBow, Spear}, Average, ChaoticEvil, Medium},
	{"beetle, fire", "огненный жук", "огненных жуков", Common, {3, 4}, 4, 12, {1, HD, 2}, 0, 0, {{2, 4}}, None, Neutral, Small},
	{"demon, manes", "мейны", "мейнов", Rare, {4, 4}, 7, 3, {1, HD}, 0, 0, {{1, 2}, {1, 2}, {1, 3}}, Semi, ChaoticEvil, Small, {MagicWeaponToHit1}},
	{"dwarf", "карлик", "карликов", Common, {4, 10, 0, 10}, 4, 6, {1, HD}, 50, "M5GQ20R", {{1, 2}}, Very, LawfulGood, Small, {Infravision, DwarfCombatTactic, Mining, BonusSaveVsPoison, BonusSaveVsSpells, BonusSaveVsWands}, dwarf_weapon},
	{"ear seeker", "ушной червь", "ушных червей", VeryRare, {1, 4}, 9, 1, {1}, 90, 0, {}, None, Neutral, Small},
	{"elf", "эльф", "эльфов", Uncommon, {2, 10, 0, 10}, 5, 12, {1, HD, 1}, 70, "NGST", {Ring, Shield}, Hight, ChaoticGood, Medium},
	{"gnome", "гном", "гномов", Rare, {4, 10, 0, 10}, 5, 6, {1, HD}, 50, "M3GQ20", {{1, 2}}, Very, LawfulGood, Small, {Infravision, DwarfCombatTactic, Mining, BonusSaveVsSpells, BonusSaveVsWands}},
	{"goblin", "гоблин", "гоблинов", Rare, {4, 10, 0, 10}, 6, 6, {1, 7}, 40, "КС", {{1, 6}}, Average, LawfulEvil, Small},
	{"halfling", "хоббит", "хоббитов", Rare, {3, 10, 0, 10}, 7, 9, {1, 6}, 70, "KB", {{1, 6}}, Very, LawfulGood, Small},
	{"hobgobling", "хобгоблин", "хобголинов", Uncommon, {2, 10, 0, 10}, 5, 9, {1, HD, 1}, 25, "JMDQ5", {{1, 8}}, Average, LawfulEvil, Small},
	{"kobold", "кобольд", "кобольдов", Uncommon, {4, 10, 0, 10}, 7, 6, {1, 4}, 40, "JOQ5", {{1, 8}}, Average, LawfulEvil, Small},
	{"orc", "орк", "орков", Common, {3, 10, 0, 10}, 5, 9, {1, 8}, 10, "", {Spear, Shield, ChainArmor}, Low, LawfulEvil, Medium},
	{"piercer", "пронзатель", "пронзателей", Uncommon, {3, 6}, 3, 1, {1, HD}, 0, 0, {}, None, Neutral, Small},
	{"rat, giant", "гиганская крыса", "гиганских крыс", Common, {5, 10}, 7, 12, {1, 4}, 10, "C", {{1, 3}}, Semi, Neutral, Small},
	{"rob, grub", "гнилые черви", "гнилых червей", Rare, {5, 10}, 9, 1, {1}, 0, 0, {}, None, Neutral, Small},
	{"shrieker", "шумник", "шумников", Common, {2, 4}, 7, 1, {3, HD}, 0, 0, {}, None, Neutral, Medium},
	{"skeleton", "скелет", "скелетов", Rare, {3, 10}, 7, 12, {1, HD}, 0, 0, {1, 6}, None, Neutral, Medium, {Undead, ResistSlashingAndPierce}},
	{"zombie", "зомби", "зомби", Rare, {3, 8}, 8, 6, {2, HD}, 0, 0, {1, 8}, None, Neutral, Medium, {Undead, LooseInitiative}},
};
assert_enum(monster, Zombie);
getstr_enum(monster);

const char* character::getnameof(monster_s id) {
	return monster_data[id].nameof;
}

dice character::getappearing(monster_s id) {
	return monster_data[id].appearing;
}

alignment_s	character::getalignment(monster_s id) {
	return monster_data[id].alignment;
}

void character::setmonsterhp() {
	hp_maximum = 0;
	if(getHD() == 0)
		hp_maximum += dice::roll(1, 6);
	else {
		for(auto i = getHD(); i > 0; i--)
			hp_maximum += dice::roll(1, 8);
	}
}

int	character::getAC(monster_s value) {
	return monster_data[value].ac;
}

static custom_weapons& random(aref<custom_weapons> source) {
	auto result = 0;
	auto roll = 1 + (rand() % 100);
	for(auto& e : source) {
		result += e.chance;
		if(result <= e.chance)
			return e;
	}
	return source.data[0];
}

character::character(monster_s type) {
	clear();
	auto& e = monster_data[type];
	// Set basic values
	alignment = e.alignment;
	if(e.HD.d == 0)
		levels[0] = 1;
	else
		levels[0] = (char)e.HD.c;
	monster = type;
	// Set all ability to 10
	for(auto& c : abilities)
		c = 10;
	// Add custom weapon
	if(e.custom_weapon) {
		auto& pw = random(e.custom_weapon);
		for(auto& w : pw.data)
			add(w);
	}
	// Set hit points
	setmonsterhp();
	// Get current hit points and raise levels
	finish(false);
}

char* character::getmonstername(char* result, const char* result_maximum) const {
	if(count == 1)
		zcpy(result, monster_data[monster].name);
	else
		szprints(result, result_maximum, "%1i %2", count, monster_data[monster].nameof);
	return result;
}

const dungeon_encounter* game::getdungeonencounter(int level) {
	return monster_level_1;
}