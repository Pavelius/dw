#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"NoItem", "Нет предмета"},
//
{"Club", "Палица", "", 1 * SP, 2, OffhandWeapon, {SimpleWeaponProficiency}, {}, {1, 8, 0, Bludgeon}},
{"Dagger", "Кинжал", "", 2 * GP, 1, OffhandWeapon, {SimpleWeaponProficiency}, {Finesse, Thrown}, {1, 4, 0, Pierce}},
{"Greatclub", "Дубина", "", 2 * SP, 10, MeleeWeapon, {SimpleWeaponProficiency}, {TwoHanded}, {1, 8, 0, Bludgeon}},
{"Handaxe", "Топор", "", 5 * GP, 2, OffhandWeapon, {SimpleWeaponProficiency}, {}, {1, 6, 0, Slashing}},
{"Javelin", "Дротик", "", 5 * SP, 2, MeleeWeapon, {SimpleWeaponProficiency}, {Thrown}, {1, 6, 0, Pierce}},
{"LightHammer", "Молоток", "", 2 * SP, 2, MeleeWeapon, {SimpleWeaponProficiency}, {Thrown}, {1, 4, 0, Bludgeon}},
{"Mace", "Булава", "", 5 * GP, 4, MeleeWeapon, {SimpleWeaponProficiency}, {}, {1, 6, 0, Bludgeon}},
{"Quaterstaff", "Посох", "", 2 * SP, 4, MeleeWeapon, {SimpleWeaponProficiency}, {Versatile}, {1, 6, 0, Bludgeon}},
{"Spear", "Копье", "", 1 * GP, 3, MeleeWeapon, {SimpleWeaponProficiency}, {Versatile}, {1, 6, 0, Pierce}},
//
{"Light Crossbow", "Легкий арбалет", "", 25 * GP, 5, RangedWeapon, {SimpleWeaponProficiency}, {TwoHanded, Loading}, {1, 8, 0, Pierce}},
{"Dart", "Дарт", "", 0, 1, RangedWeapon, {SimpleWeaponProficiency}, {Finesse, Thrown}, {1, 4, 0, Pierce}},
{"Shortbow", "Короткий лук", "", 25 * GP, 2, RangedWeapon, {SimpleWeaponProficiency, ElfWeaponTrain}, {TwoHanded}, {1, 6, 0, Pierce}},
{"Sling", "Праща", "", 1 * SP, 0, RangedWeapon, {SimpleWeaponProficiency}, {}, {1, 4, 0, Bludgeon}},
//
{"Battleaxe", "Боевой топор", "", 10 * GP, 4, MeleeWeapon, {MartialWeaponProfiency}, {Versatile}, {1, 8, 0, Slashing}},
{"Flail", "Цеп", "", 10 * GP, 2, MeleeWeapon, {MartialWeaponProfiency}, {}, {1, 8, 0, Bludgeon}},
{"Greataxe", "Секира", "", 30 * GP, 7, MeleeWeapon, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {1, 12, 0, Slashing}},
{"Halberd", "Алебарда", "", 20 * GP, 6, MeleeWeapon, {MartialWeaponProfiency}, {Heavy, TwoHanded, Reach}, {1, 10, 0, Slashing}},
{"Lance", "Кавалерийская Пика", "", 10 * GP, 6, MeleeWeapon, {MartialWeaponProfiency}, {Reach}, {1, 12, 0, Pierce}},
{"Longsword", "Длинный меч", "", 15 * GP, 3, MeleeWeapon, {MartialWeaponProfiency, ElfWeaponTrain}, {Versatile}, {1, 8, 0, Slashing}},
{"Maul", "Маул", "", 10 * GP, 10, MeleeWeapon, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {2, 6, 0, Bludgeon}},
{"Morningstar", "Шестопер", "", 15 * GP, 4, MeleeWeapon, {MartialWeaponProfiency}, {}, {1, 8, 0, Pierce}},
{"Pike", "Пика", "", 5 * GP, 18, MeleeWeapon, {MartialWeaponProfiency}, {Heavy, Reach, TwoHanded}, {1, 10, 0, Pierce}},
{"Rapier", "Рапира", "", 25 * GP, 2, MeleeWeapon, {MartialWeaponProfiency}, {Finesse}, {1, 8, 0, Pierce}},
{"Scimitar", "Скимитар", "", 25 * GP, 3, OffhandWeapon, {MartialWeaponProfiency}, {Finesse}, {1, 6, 0, Slashing}},
{"Shortsword", "Короткий меч", "", 10 * GP, 2, OffhandWeapon, {MartialWeaponProfiency, ElfWeaponTrain}, {Finesse}, {1, 6, 0, Pierce}},
{"Trident", "Трезубец", "", 5 * GP, 4, MeleeWeapon, {MartialWeaponProfiency}, {Versatile, Thrown}, {1, 6, 0, Pierce}},
{"Warhammer", "Боевой молот", "", 15 * GP, 2, MeleeWeapon, {MartialWeaponProfiency}, {Versatile}, {1, 8, 0, Bludgeon}},
{"Whip", "Кнут", "", 2 * GP, 3, MeleeWeapon, {MartialWeaponProfiency}, {Finesse, Reach}, {1, 4, 0, Slashing}},
//
{"CrossbowHeavy", "Тяжелый арбалет", "", 50 * GP, 18, RangedWeapon, {MartialWeaponProfiency}, {Heavy, Loading, TwoHanded}, {1, 10, 0, Pierce}},
{"Longbow", "Длинный лук", "", 50 * GP, 18, RangedWeapon, {MartialWeaponProfiency, ElfWeaponTrain}, {Heavy, TwoHanded}, {1, 8, 0, Pierce}},
{"Net", "Сеть", "", 1 * GP, 3, RangedWeapon, {MartialWeaponProfiency}, {Thrown}},
//
{"Arrow", "Стрелы", "", 1 * GP, 1, Ammunition},
{"Bolts", "Болты", "", 1 * GP, 2, Ammunition},
{"Stones", "Камни", "", 0, 2, Ammunition},
//
{"LeatherArmor", "Кожаная броня", "", 10 * GP, 10, Armor, {LightArmorProficiency}, {}, {}, {1, 10}},
{"PaddedArmor", "Стеганая броня", "", 5 * GP, 8, Armor, {LightArmorProficiency}, {}, {}, {1, 10, 0, Stealth}},
{"StuddedLeatherArmor", "Клепанная кожаная броня", "", 45 * GP, 13, Armor, {LightArmorProficiency}, {}, {}, {2, 10}},
//
{"Hide", "Шкуры", "", 10 * GP, 12, Armor, {MediumArmorProficiency}, {}, {}, {2, 2}},
{"Breastplate", "Нагрудник", "", 400 * GP, 20, Armor, {MediumArmorProficiency}, {}, {}, {4, 2}},
{"HalfPlate", "Полу-латы", "", 750 * GP, 40, Armor, {MediumArmorProficiency}, {}, {}, {5, 2, 0, Stealth}},
{"ChainShirt", "Кольчужная рубаха", "", 50 * GP, 20, Armor, {MediumArmorProficiency}, {}, {}, {3, 2}},
{"ScaleMail", "Чешуйчатый доспех", "", 50 * GP, 45, Armor, {MediumArmorProficiency}, {}, {}, {4, 2, 0, Stealth}},
//
{"RingMail", "Кольцевой доспех", "", 30 * GP, 40, Armor, {HeavyArmorProficiency}, {}, {}, {4, 0, 0, Stealth}},
{"Plate", "Латы", "", 1500 * GP, 65, Armor, {HeavyArmorProficiency}, {}, {}, {8, 0, 15, Stealth}},
{"ChainMail", "Кольчужный доспех", "", 75 * GP, 55, Armor, {HeavyArmorProficiency}, {}, {}, {6, 0, 13, Stealth}},
{"SplintMail", "Ленточный доспех", "", 200 * GP, 60, Armor, {HeavyArmorProficiency}, {}, {}, {7, 0, 15, Stealth}},
//
{"Shield", "Щит", "", 10 * GP, 6, OffhandWeapon, {ShieldProficiency}, {}, {}, {2}},
{"Helmet", "Шлем", "", 10 * GP, 1, Head},
{"Bracers", "Браслеты", "", 10 * GP, 1, Elbow},
{"Ring", "Кольцо", "", 10 * GP, 0, RightFinger},
{"Necklage", "Ожерелье", "", 10 * GP, 0, Neck},
//
{"Bedroll", "Постельные принадлежности", "", 1 * GP, 7},
{"Book", "Книга", "", 5 * GP, 2},
{"ComponentsPounch", "Мешочек с компонентами", "", 1 * GP, 1},
{"Crowbar", "Ломик", "", 2 * GP, 5},
{"HolySymbol", "Священный символ", "", 1 * SP, 1},
{"Map", "Карта", "", 2 * GP, 0},
{"Parchment", "Пергамент", "", 1 * SP, 0, {}, {}, {}, {}, {}},
{"Ration", "Провизия", "", 2 * SP, 4, {}, {}, {}, {}, {}},
{"Rope", "Веревка", "", 1 * GP, 10},
{"Spellbook", "Книга заклинаний", "", 10 * GP, 2},
{"Torches", "Факела", "", 1 * SP, 2, {}, {}, {}, {}, {}},
{"Waterskin", "Бурдюк", "", 2 * SP, 5, {}, {}, {}, {}, {}},
//
{"Dices", "Кубики", "", 1 * SP},
{"PlayingCards", "Игральные карты", "", 5 * SP},
//
{"Flute", "Флейта", "", 2 * GP, 1},
{"Lute", "Лютня", "", 35 * GP, 2},
//
{"AlchemistSupplies", "Алхемические компоненты", "", 50 * GP, 8},
{"BrewerSupplies", "Бутылки", "", 20 * GP, 9},
{"CalligrapherSupplies", "Пергамент", "", 10 * GP, 5},
{"CarpenterTools", "Инструменты плотника", "", 8 * GP, 6},
{"CartographerTools", "", "", 15 * GP, 6},
{"CobblerTools", "", "", 5 * GP, 5},
{"CookUtensils", "Кастрюля", "", 1 * GP, 8},
{"GlassblowerTools", "", "", 30 * GP, 5},
{"JewelerTools", "Весы", "", 25 * GP, 2},
{"LeatherworkerTools", "", "", 5 * GP, 5},
{"MasonTools", "Долото", "", 10 * GP, 8},
{"PainterSupplies", "Кисточка и краски", "", 10 * GP, 5},
{"PotterTools", "", "", 10 * GP, 3},
{"SmithTools", "Молоток", "", 20 * GP, 8},
{"TinkerTools", "Клещи", "", 50 * GP, 10},
{"WeaverTools", "Игла и нитка", "", 1 * GP, 5},
{"WoodcarverTools", "Фреза", "", 1 * GP, 5},
//
{"DisguiseKit", "Тональный крем", "", 25 * GP, 3},
{"ForgeryKit", "Ящик с печатями", "", 15 * GP, 5},
{"HerbalismKit", "Мешочек с травами", "", 5 * GP, 3},
{"NavigatorTools", "Компас", "", 25 * GP, 2},
{"PoisonerTools", "Набор ядовитых компонентов", "", 50 * GP, 2},
{"TheifTools", "Отмычки и щупы", "", 2 * GP, 5},
//
{"ScrollOfBless", "Свиток", "", 20 * GP, 0, Readable, {}, {}, {}, {}},
{"PotionOfHealing", "Зелье", "лечения", 25 * GP, 5, Drinkable, {}, {}, {}, {}},
};
assert_enum(item, LastItem);

void item::addname(stringbuilder& sb) const {
	sb.add(bsmeta<itemi>::elements[type].name);
}

void item::addnameby(stringbuilder& sb) const {
	sb.addby(bsmeta<itemi>::elements[type].name);
}

void item::addnamewh(stringbuilder& sb) const {
	sb.addby(bsmeta<itemi>::elements[type].name);
}

bool item::is(feat_s id) const {
	return bsmeta<itemi>::elements[type].proficiency.is(id);
}

bool item::is(item_feat_s id) const {
	return getei().feats.is(id);
}

bool item::is(wear_s id) const {
	return getei().wears == id;
}

bool item::islight() const {
	return getei().wears == OffhandWeapon;
}

int	item::getcost() const {
	return getei().cost;
}

const dice& item::getattack() const {
	return getei().attack;
}

bool creature::isproficient(item_s it) const {
	if(feats.is(bsmeta<itemi>::elements[it].proficiency))
		return true;
	return false;
}

int item::getcount() const {
	if(iscountable())
		return 1 + charges;
	return 1;
}

void item::setcount(int v) {
	if(!v)
		clear();
	else if(iscountable()) {
		if(v > 32)
			v = 32;
		charges = v - 1;
	}
}

void item::consume() {
	auto& ei = getei();
	if(ischargeable()) {
		if(charges == 1) {
			charges = 0;
			if(d100() < 5)
				clear();
		} else {
		}
	} else if(iscountable())
		setcount(getcount() - 1);
}

void item::clear() {
	memset(this, 0, sizeof(*this));
}