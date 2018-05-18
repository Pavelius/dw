#include "main.h"

struct dicex {
	short c, d, b, m;
	int	roll() const {
		if(!d)
			return c;
		int result = 0;
		for(int i = 0; i < c; i++)
			result += 1 + (rand() % d);
		return result;
	}
};
struct appear {
	char			chance;
	dicex			count;
	int roll() const {
		if(d100() < chance)
			return count.roll();
		return 0;
	}
};
static struct lair_treasure {
	const char		symbol;
	appear			cp;
	appear			sp;
	appear			gp;
	appear			pp;
	appear			gems;
	appear			art;
	appear			magic;
	magic_item_s	magic_item;
	magic_item_s	magic_item_bonus;
	magic_item_s	magic_item_exept;
} treasure_data[] = {
	{'A', {25, {1, 3, 0, 1000}}, {30, {2, 10, 0, 100}}, {40, {1, 6, 0, 1000}}, {35, {3, 6, 0, 100}}, {60, {1, 4, 0, 10}}, {50, {2, 6}}, {30, {3}}},
	{'B', {50, {1, 6, 0, 1000}}, {25, {1, 3, 0, 1000}}, {25, {2, 10, 0, 100}}, {25, {1, 10, 0, 100}}, {30, {1, 8}}, {20, {1, 4}}, {10, {1}}, Armors},
	{'C', {20, {1, 10, 0, 1000}}, {30, {1, 6, 0, 1000}}, {0}, {10, {1, 6, 0, 100}}, {25, {1, 6}}, {20, {1, 3}}, {10, {2}}},
	{'D', {10, {1, 6, 0, 1000}}, {15, {1, 10, 0, 1000}}, {50, {1, 3, 0, 1000}}, {15, {1, 6, 0, 100}}, {30, {1, 10}}, {25, {1, 6}}, {15, {2}}, Any, Potions},
	{'E', {5, {1, 6, 0, 1000}}, {25, {1, 10, 0, 1000}}, {25, {1, 4, 0, 1000}}, {25, {3, 6, 0, 100}}, {15, {1, 12}}, {10, {1, 6}}, {25, {3}}, Any, Scrolls},
	{'F', {0}, {10, {3, 6, 0, 1000}}, {40, {1, 6, 0, 1000}}, {15, {1, 4, 0, 1000}}, {20, {2, 10}}, {10, {1, 8}}, {30, {5}}, Any, Any, Weapons},
	{'G', {0}, {0}, {50, {2, 10, 0, 1000}}, {50, {1, 10, 0, 1000}}, {30, {3, 6}}, {25, {1, 6}}, {35, {5}}},
	{'H', {25, {3, 6, 0, 1000}}, {40, {2, 10, 0, 1000}}, {55, {2, 10, 0, 1000}}, {40, {1, 8, 0, 1000}}, {50, {3, 10}}, {50, {2, 10}}, {15, {6}}},
	{'I', {0}, {0}, {0}, {30, {1, 6, 0, 100}}, {55, {2, 6}}, {50, {2, 8}}, {15, {1}}},
	//
	{'J', {100, {3, 8}}, {0}, {0}, {0}, {0}, {0}, {0}},
	{'K', {0}, {100, {3, 6}}, {0}, {0}, {0}, {0}, {0}},
	{'L', {0}, {0}, {0}, {100, {2, 6}}, {0}, {0}, {0}},
	{'M', {0}, {0}, {100, {2, 4}}, {0}, {0}, {0}, {0}},
	{'N', {0}, {0}, {0}, {100, {1, 6}}, {0}, {0}, {0}},
	{'O', {100, {1, 4, 0, 10}}, {100, {1, 3, 0, 10}}, {0}, {0}, {0}, {0}, {0}},
	{'P', {0}, {100, {1, 6, 0, 10}}, {0}, {100, {1, 20}}, {0}, {0}, {0}},
	{'Q', {0}, {0}, {0}, {0}, {100, {1, 4}}, {0}, {0}},
	{'R', {0}, {0}, {100, {2, 10}}, {100, {1, 6}}, {100, {2, 4}}, {100, {1, 3}}, {0}},
	{'S', {0}, {0}, {0}, {0}, {0}, {0}, {100, {1, 8}}, Potions},
	{'T', {0}, {0}, {0}, {0}, {0}, {0}, {100, {1, 4}}, Scrolls},
	{'U', {0}, {0}, {0}, {0}, {90, {2, 8}}, {80, {1, 6}}, {70, {1}}},
	{'V', {0}, {0}, {0}, {0}, {0}, {0}, {100, {2}}},
	{'W', {0}, {0}, {100, {5, 6}}, {100, {1, 8}}, {60, {2, 8}}, {50, {1, 8}}, {60, {2}}},
	{'X', {0}, {0}, {0}, {0}, {0}, {0}, {100, {2}}, Potions},
	{'Y', {0}, {0}, {100, {2, 6, 0, 100}}, {0}, {0}, {0}, {0}},
	{'Z', {100, {1, 3, 0, 100}}, {100, {1, 4, 0, 100}}, {100, {1, 6, 0, 100}}, {100, {1, 4, 0, 100}}, {55, {1, 6}}, {50, {2, 6}}, {50, {3}}}
};
static item_s ornamental_stones[] = {
	Azurite, BandedAgate, BlueQuartz, EyeAgate, Hematite,
	LapisLazuli, Malachite, MossAgate, Obsidian, Rhodochrosite,
	TigerEyeAgate, Turquoise
};
static item_s semi_precious_stones[] = {
	Bloodstone, Chalcedony, Chrysoprase, Citrine, Jasper,
	Moonstone, Onyx, RockCrystal, Sardonyx, SmokyQuartz,
	StarRoseQuartz, Zircon
};
static item_s fancy_stones[] = {
	Amber, Alexandrite, Amethyst, Chrysoberyl, Coral, Jade, Jet, Spinel, Tourmaline,
};
static item_s precious_stones[] = {
	Aquamarine, Garnet, Pearl, Peridot, Topaz,
};
static item_s gems_stones[] = {
	BlackOpal, FireOpal, Opal, OrientalAmethyst, OrientalTopaz, Sapphire,
};
static item_s jewels_stones[] = {
	BlackSapphire, Diamond, Emerald, Jacinth, OrientalEmerald, Ruby, StarRuby, StarSapphire,
};
static struct item_range {
	char			percent;
	aref<item_s>	items;
} gem_generator[] = {
	{25, ornamental_stones},
	{50, semi_precious_stones},
	{70, fancy_stones},
	{90, precious_stones},
	{99, gems_stones},
	{100, jewels_stones},
};
static lair_treasure* find(char symbol) {
	for(auto& e : treasure_data) {
		if(e.symbol == symbol)
			return &e;
	}
	return 0;
}
static item_s get(aref<item_range> range) {
	auto roll = (1 + rand() % 100);
	for(auto& e : range) {
		if(roll <= e.percent)
			return e.items.data[rand() % e.items.count];
	}
	// This case is only for errors
	return range[0].items.data[rand() % range[0].items.count];
}

treasure::treasure() {
	clear();
}

void treasure::clear() {
	memset(this, 0, sizeof(*this));
}

item_s treasure::anygem() {
	return get(gem_generator);
}

item treasure::gemquality(item_s type) {
	item result;
	result.type = type;
	while(true) {
		switch(1 + rand() % 6) {
		case 1:
			result.state = item::Magic;
			continue;
		case 2:
			result.quality = 3;
			break;
		case 3:
			result.quality = 2;
			break;
		case 4:
			result.quality = 1;
			break;
		case 5: result.quality = 0;
			break;
		default:
			result.state = item::Cursed;
			continue;
		}
		break;
	}
	return result;
}

void treasure::generate(char symbol) {
	auto p = find(symbol);
	if(!p)
		return;
	cp += p->cp.roll();
	sp += p->sp.roll();
	gp += p->gp.roll();
	pp += p->pp.roll();
	gems += p->gems.roll();
	art += p->art.roll();
	// Magic items add right now
	auto m = p->magic.roll();
	if(m) {
		for(auto i = 0; i < m; i++) {
			auto type = Any;
			while(true) {
				if(p->magic_item)
					type = p->magic_item;
				else if(p->magic_item_exept) {
					type = anymagic();
					if(p->magic_item_exept == type)
						continue;
				}
				else
					type = anymagic();
				break;
			}
			add(type);
		}
		magic += m;
	}
	if(p->magic_item_bonus) {
		add(p->magic_item_bonus);
		magic++;
	}
}

void treasure::generate(const char* type) {
	auto p = type;
	while(*p) {
		char count = 0;
		char symbol = *p++;
		while(p[0] >= '0' && p[0] <= '9')
			count = count * 10 + ((*p++) - '0');
		if(!count)
			count = 1;
		for(int i = 0; i < count; i++)
			generate(symbol);
	}
	addgems(gems);
	addarts(art);
	zshuffle(items, zlen(items));
}

void treasure::add(item value) {
	for(auto& e : items) {
		if(!e) {
			e = value;
			return;
		}
	}
}

void treasure::addgems(int count) {
	for(int i = 0; i < count; i++)
		add(gemquality(anygem()));
}

static item_s primitive_weapon[] = {
	Axe, Mace, MorningStar, Hammer, Pick, Spear,
	Spear, Staff, Halberd,
	Sling,
};
static item_s swords_weapon[] = {
	Dagger, ShortSword, LongSword, BastardSword, TwoHandedSword, Scimitar,
};
static item_s distance_weapon[] = {
	Dagger, ShortSword, LongSword, BastardSword, TwoHandedSword, Scimitar,
};
static item_s art_bows[] = {
	ShortBow, LongBow, Crossbow,
};
static item_s art_armor[] = {
	LeatherArmor, LeatherArmor, ChainArmor, ScaleArmor, PlateArmor, RingArmor, SplintedArmor,
	Shield
};
item treasure::anyart() {
	static struct range {
		char			chance;
		dicex			cost;
		aref<item_s>	items;
		unsigned char	quality;
	} ranges[] = {
		{10, {1, 10, 0, 10}, primitive_weapon, 0},
		{25, {3, 6, 0, 10}, art_bows, 1},
		{40, {1, 6, 0, 100}, swords_weapon, 1},
		{50, {1, 10, 0, 100}, art_armor, 1},
		{60, {2, 6, 0, 100}, primitive_weapon, 2},
		{70, {3, 6, 0, 100}, art_bows, 2},
		{80, {4, 6, 0, 100}, swords_weapon, 2},
		{85, {5, 6, 0, 100}, art_armor, 2},
		{90, {1, 4, 0, 1000}, primitive_weapon, 3},
		{95, {1, 6, 0, 1000}, art_bows, 3},
		{99, {2, 4, 0, 1000}, swords_weapon, 3},
		{100, {2, 6, 0, 1000}, art_armor, 3},
	};
	char roll = xrand(1, 100);
	for(auto& e : ranges) {
		if(roll <= e.chance) {
			item result(game::random(e.items));
			result.quality = e.quality;
			result.fashion = xrand(1, 3);
			return result;
		}
	}
	return NoItem;
}

void treasure::addarts(int count) {
	for(auto i = 0; i < count; i++)
		add(anyart());
}

magic_item_s treasure::anymagic() {
	static struct range {
		char			chance;
		magic_item_s	type;
		magic_item_s	type2;
	} ranges[] = {
		{20, Potions, Oils},
		{35, Scrolls},
		{40, Rings},
		{41, Rods},
		{42, Staves},
		{45, Wands},
		{46, Books, Tomes},
		{48, Jewels, Jewelry},
		{50, Cloacks, Robes},
		{52, Boots, Gloves},
		{53, Gridles, Helms},
		{55, Bags, Bottles},
		{56, Dusts, Stones},
		{57, Tools},
		{58, MusicalInstruments},
		{60, WeirdStuffs},
		{75, Armors, Shields},
		{100, Weapons},
	};
	char roll = xrand(1, 100);
	for(auto& e : ranges) {
		if(roll <= e.chance)
			return e.type;
	}
	return Any;
}

static struct scroll_spell_level {
	char	chance;
	char	count;
	dice	mage;
	dice	priest;
} scroll_spell_levels[] = {
	{3, 1, {1, 4}},
	{5, 1, {1, 6}},
	{6, 1, {1, 8, 1}, {1, 6, 1}},
	{7, 2, {1, 4}},
	{8, 2, {1, 8, 1}, {1, 6, 1}},
	{9, 3, {1, 4}},
	{10, 3, {1, 8, 1}, {1, 6, 1}},
	{11, 4, {1, 6}},
	{12, 4, {1, 8}, {1, 6}},
	{13, 5, {1, 6}},
	{14, 5, {1, 8}, {1, 6}},
	{15, 6, {1, 6}},
	{16, 6, {1, 6, 2}, {1, 3, 2}},
	{17, 7, {1, 8}},
	{18, 7, {1, 8, 1}, {1, 6, 1}},
	{20, 7, {1, 6, 3}, {1, 4, 3}},
};

item treasure::anymagic(magic_item_s type, char level, class_s usable) {
	auto item_type = item::get(type);
	auto item_types = item::gettypes(type);
	auto item_bonus = item::getbonus(type);
	if(item_types)
		item_type = game::random(item_types);
	item result(item_type);
	result.state = item::Magic;
	// Determine quality bonus if any
	switch(item_type) {
	case ShortSword:
	case LongSword:
	case TwoHandedSword:
	case BastardSword:
		item_bonus = item::getbonus(Armors);
		break;
	}
	if(item_bonus) {
		auto bonus = game::random(item_bonus);
		if(bonus == -1)
			result.state = item::Cursed;
		else if(bonus >= 1 && bonus <= 4)
			result.quality = bonus - 1;
		else {
			result.quality = 3;
			result.state = item::Artifact;
		}
	}
	// Determine special power
	while(true) {
		auto source = item::getpowers(type);
		if(source.count) {
			result.power = game::random(source);
			if(result.power == Delusion) {
				result.state = item::Cursed;
				continue;
			}
		}
		break;
	}
	return result;
}

void treasure::add(magic_item_s type) {
	if(type == Scroll) {
		auto chance = d20();
		for(auto& e : scroll_spell_levels) {
			if(chance <= e.chance) {
				auto usable = (d10() <= 7) ? MagicUser : Cleric;
				auto count = e.count;
				for(auto i = 0; i < count; i++) {
					auto level = ((usable ==Cleric) && e.priest.c) ? e.priest.roll() : e.mage.roll();
					add(anymagic(type, level, usable));
				}
				return;
			}
		}
	}
	add(anymagic(type));
}

void treasure::addmagic(int count) {
	for(auto i = 0; i < count; i++)
		add(anymagic());
}

item treasure::getfirst() {
	auto count = zlen(items);
	if(!count)
		return NoItem;
	auto result = items[0];
	if(count > 1)
		memmove(items, items + 1, count - 1);
	else
		items[0] = NoItem;
	return result;
}