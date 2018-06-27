#include "main.h"

static magic_power_s potion_powers[] = {
	AnimalControl, Clairaudience, Clairvoyance, Climbing,
	Diminution, DragonControl,
	Health, Madness, Madness, Youth, ESP, ExtraHealing, FireBreath, FireResistance, Flying, GaseousForm,
	GiantControl, GiantStrength, Growth, Healing, Heroism, HumanControl, Invisibility,
	Invulnerability, Levitation, Longevity
};
static magic_power_s ring_powers[] = {
	AnimalControl, Blinking, Clumsiness, Contrariness, DjinniSummoning,
	ElementalControl, FeatherFalling, FireResistance, FreeAction, HumanControl, Invisibility,
	JumpingPower, JumpingPower, AnimalControl, MindShielding, Protection, Protection, Protection,
	Ram, Regeneration, ShockingGrasp, ShootingStars, SpellStoring, SpellTurning,
	Sustenance, SwimmingPower, Telekinesis, Truth, Warmth, WaterWalking, Weakness, Wizardry, DarkvisionPower,
};
static item_s armor_items[] = {
	BandedArmor,
	ChainArmor, ChainArmor, ChainArmor,
	LeatherArmor,
	PlateArmor, PlateArmor, PlateArmor, PlateArmor,
	RingArmor, ScaleArmor,
	Shield, Shield, Shield,
	SplintedArmor,
	StuddedArmor,
};
static item_s weapon_items[] = {
	Arrow, Arrow, Arrow,
	Axe, Pick,
	Bolt, Bolt, Stone,
	Dagger, Dagger, Dagger,
	Mace, Mace,
	MorningStar, Staff,
	Scimitar, Scimitar,
	Spear, Spear, Spear,
	ShortSword, ShortSword, ShortSword, LongSword, LongSword, LongSword, BastardSword, TwoHandedSword, TwoHandedSword,
};
static char armor_bonus[20] = {
	-1, -1,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2,
	3, 3, 3,
	4, 4,
	5
};
static char weapon_bonus[20] = {
	-1, -1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2,
	3
};
static struct magic_item {
	const char*		id;
	const char*		name;
	item_s			type; // Single item type. If has two or more use subtable.
	aref<item_s>	types;
	aref<magic_power_s>	powers;
	aref<char>		magic_bonus;
} magic_item_data[] = {
	{"Any magic item", "����� �������� �������"},
	{"Potions", "�����", Potion, {}, potion_powers},
	{"Oils", "�����"},
	{"Scrolls", "������", Scroll},
	{"Armors", "�������", LeatherArmor, armor_items, {}, armor_bonus},
	{"Shields", "����", Shield},
	{"Weapons", "������", Axe, weapon_items, {}, weapon_bonus},
	{"Rings", "������", Ring, {}, ring_powers},
	{"Rods", "�������", Rod},
	{"Staves", "������", Staff},
	{"Wands", "�������", Wand},
	{"Books", "�����", Book},
	{"Tomes", "����", Tome},
	{"Jewels", "�������������", Azurite},
	{"Jewelry", "��������", Necklage},
	{"Cloacks", "�����", Cloack},
	{"Robes", "����", Robe},
	{"Boots", "�����", Boot},
	{"Gloves", "��������", Glove},
	{"Gridles", "�����", Gridle},
	{"Helms", "�����", Helm},
	{"Bags", "�����", Bag},
	{"Bottles", "�������", Bottle},
	{"Dusts", "����", Dust},
	{"Stones", "�����", Stone},
	{"Tools", "�����������"},
	{"Musical Instruments", "����������� �����������", Flute},
	{"Weird Stuffs", "���������� ������"},
};
getstr_enum(magic_item);
assert_enum(magic_item, WeirdStuffs);

item_s item::get(magic_item_s type) {
	return magic_item_data[type].type;
}

aref<item_s> item::gettypes(magic_item_s type) {
	return magic_item_data[type].types;
}

aref<magic_power_s> item::getpowers(magic_item_s type) {
	return magic_item_data[type].powers;
}

aref<char> item::getbonus(magic_item_s type) {
	return magic_item_data[type].magic_bonus;
}