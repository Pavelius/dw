#include "main.h"

item_info item_data[] = {{"No item", "Нет предмета"},
//
{"Club", "Палица", 1 * SP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {}, {1, 8, 0, Bludgeon}},
{"Dagger", "Кинжал", 2 * GP, 1, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {Finesse, Thrown}, {1, 4, 0, Pierce}},
{"Greatclub", "Дубина", 2 * SP, 10, {MeleeWeapon}, {SimpleWeaponProficiency}, {TwoHanded}, {1, 8, 0, Bludgeon}},
{"Handaxe", "Топор", 5 * GP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {}, {1, 6, 0, Slashing}},
{"Javelin", "Дротик", 5 * SP, 2, {MeleeWeapon}, {SimpleWeaponProficiency}, {Thrown}, {1, 6, 0, Pierce}},
{"Light Hammer", "Молоток", 2 * SP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {Thrown}, {1, 4, 0, Bludgeon}},
{"Mace", "Булава", 5 * GP, 4, {MeleeWeapon}, {SimpleWeaponProficiency}, {}, {1, 6, 0, Bludgeon}},
{"Quaterstaff", "", 2 * SP, 4, {MeleeWeapon}, {SimpleWeaponProficiency}, {Versatile}, {1, 6, 0, Bludgeon}},
{"Spear", "", 1 * GP, 3, {MeleeWeapon}, {SimpleWeaponProficiency}, {Versatile}, {1, 6, 0, Pierce}},
//
{"Light Crossbow", "", 25 * GP, 5, {RangedWeapon}, {SimpleWeaponProficiency}, {TwoHanded, Loading}, {1, 8, 0, Pierce}},
{"Dart", "Дарт", 5 * СP, 1, {RangedWeapon}, {SimpleWeaponProficiency}, {Finesse, Thrown}, {1, 4, 0, Pierce}},
{"Shortbow", "Короткий лук", 25 * GP, 2, {RangedWeapon}, {SimpleWeaponProficiency, ElfWeaponTrain}, {TwoHanded}, {1, 6, 0, Pierce}},
{"Sling", "Праща", 1 * SP, 0, {RangedWeapon}, {SimpleWeaponProficiency}, {}, {1, 4, 0, Bludgeon}},
//
{"Battleaxe", "Боевой топор", 10 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile}, {1, 8, 0, Slashing}},
{"Flail", "Цеп", 10 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {}, {1, 8, 0, Bludgeon}},
{"Greataxe", "Секира", 30 * GP, 7, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {1, 12, 0, Slashing}},
{"Halberd", "Секира", 20 * GP, 6, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded, Reach}, {1, 10, 0, Slashing}},
{"Lance", "Пика", 10 * GP, 6, {MeleeWeapon}, {MartialWeaponProfiency}, {Reach}, {1, 12, 0, Pierce}},
{"Longsword", "Длинный меч", 15 * GP, 3, {MeleeWeapon}, {MartialWeaponProfiency, ElfWeaponTrain}, {Versatile}, {1, 8, 0, Slashing}},
{"Maul", "Маул", 10 * GP, 10, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {2, 6, 0, Bludgeon}},
{"Morningstar", "Шестопер", 15 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {}, {1, 8, 0, Pierce}},
{"Pike", "Пика", 5 * GP, 18, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, Reach, TwoHanded}, {1, 10, 0, Pierce}},
{"Rapier", "Рапира", 25 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {Finesse}, {1, 8, 0, Pierce}},
{"Scimitar", "Скимитар", 25 * GP, 3, {MeleeWeapon, OffhandWeapon}, {MartialWeaponProfiency}, {Finesse}, {1, 6, 0, Slashing}},
{"Shortsword", "Короткий меч", 10 * GP, 2, {MeleeWeapon, OffhandWeapon}, {MartialWeaponProfiency, ElfWeaponTrain}, {Finesse}, {1, 6, 0, Pierce}},
{"Trident", "Трезубец", 5 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile, Thrown}, {1, 6, 0, Pierce}},
{"Warhammer", "Боевой молот", 15 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile}, {1, 8, 0, Bludgeon}},
{"Whip", "Кнут", 2 * GP, 3, {MeleeWeapon}, {MartialWeaponProfiency}, {Finesse, Reach}, {1, 4, 0, Slashing}},
//
{"Crossbow Heavy", "Тяжелый арбалет", 50 * GP, 18, {RangedWeapon}, {MartialWeaponProfiency}, {Heavy, Loading, TwoHanded}, {1, 10, 0, Pierce}},
{"Longbow", "Длинный лук", 50 * GP, 18, {RangedWeapon}, {MartialWeaponProfiency, ElfWeaponTrain}, {Heavy, TwoHanded}, {1, 8, 0, Pierce}},
{"Net", "Сеть", 1 * GP, 3, {RangedWeapon}, {MartialWeaponProfiency}, {Thrown}},
//
{"Arrow", "Стрелы", 1 * GP, 1, {Ammunition}},
{"Bolts", "Болты", 1 * GP, 2, {Ammunition}},
{"Stones", "Камни", 4 * СP, 2, {Ammunition}},
//
{"Leather armor", "Кожанная броня", 10 * GP, 10, {Armor}, {LightArmorProficiency}, {}, {}, {1, 10}},
{"Padded Armor", "Мягкая броня", 5 * GP, 8, {Armor}, {LightArmorProficiency}, {}, {}, {1, 10, 0, Stealth}},
{"Studded Leather armor", "Клепанная кожанная броня", 45 * GP, 13, {Armor}, {LightArmorProficiency}, {}, {}, {2, 10}},
//
{"Hide", "Шкуры", 10 * GP, 12, {Armor}, {MediumArmorProficiency}, {}, {}, {2, 2}},
{"Breastplate", "Нагрудник", 400 * GP, 20, {Armor}, {MediumArmorProficiency}, {}, {}, {4, 2}},
{"Half Plate", "Полулаты", 750 * GP, 40, {Armor}, {MediumArmorProficiency}, {}, {}, {5, 2, 0, Stealth}},
{"Chain Shirt", "Кольчужная рубаха", 50 * GP, 20, {Armor}, {MediumArmorProficiency}, {}, {}, {3, 2}},
{"Scale Mail", "Чешуйчатый доспех", 50 * GP, 45, {Armor}, {MediumArmorProficiency}, {}, {}, {4, 2, 0, Stealth}},
//
{"Ring Mail", "Кольцевой доспех", 30 * GP, 40, {Armor}, {HeavyArmorProficiency}, {}, {}, {4, 0, 0, Stealth}},
{"Plate", "Латы", 1500 * GP, 65, {Armor}, {HeavyArmorProficiency}, {}, {}, {8, 0, 15, Stealth}},
{"Chain Mail", "Кольчужный доспех", 75 * GP, 55, {Armor}, {HeavyArmorProficiency}, {}, {}, {6, 0, 13, Stealth}},
{"Splint Mail", "Ленточный доспех", 200 * GP, 60, {Armor}, {HeavyArmorProficiency}, {}, {}, {7, 0, 15, Stealth}},
//
{"Shield", "Щит", 10 * GP, 6, {OffhandWeapon}, {ShieldProficiency}, {}, {}, {2}},
{"Helmet", "Шлем", 10 * GP, 1, {Head}},
{"Bracers", "Браслеты", 10 * GP, 1, {Elbow}},
{"Ring", "Кольцо", 10 * GP, 0, {LeftFinger, RightFinger}},
{"Necklage", "Ожерелье", 10 * GP, 0, {Neck}},
};
getstr_enum(item);
assert_enum(item, Necklage);

bool item::is(item_feat_s id) const {
	for(auto e : item_data[type].feats) {
		if(e == id)
			return true;
	}
	return false;
}

bool item::is(wear_s id) const {
	return item_data[type].wears[0] == id
		|| item_data[type].wears[1] == id;
}

bool item::islight() const {
	return item_data[type].wears[0] == MeleeWeapon
		&& item_data[type].wears[1] == OffhandWeapon;
}

int item::getac() const {
	return item_data[type].armor.ac;
}

const dice& item::getattack() const {
	return item_data[type].attack;
}

bool creature::isproficient(item_s it) const {
	if(item_data[it].proficiency[0] == NoFeat)
		return false;
	for(auto e : item_data[it].proficiency) {
		if(!e)
			break;
		if(is(e))
			return true;
	}
	return false;
}