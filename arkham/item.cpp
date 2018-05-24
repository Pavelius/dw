#include "main.h"

static quest ancient_tome = {AnyLocation, "Попробывать изучить древний том.", {Lore, -1}, {
	{"Ничего нового для себя вы не почерпнули."},
{"Вы изучили древний волшебный ритуал.", {AddSpell, Discard}},
}};
static quest old_journal = {AnyLocation, "Изучить содержимое старого журнала.", {Lore, -1}, {
	{"Ничего нового для себя вы не почерпнули."},
{"В старом журнале содержались важные и полезные данные о древних сектах и культах.", {Add3Clue, Discard}},
}};
static constexpr const struct item_i {
	struct effect_i {
		stat_s		id;
		char		count;
	};
	struct tome_i {
		char		movement; // Lose this count of movement to do this
		char		sanity; // Lose this count of sanity to do this
		quest*		script;
		char		usable; // This is maximum use count
	};
	const char*		id;
	const char*		name;
	stat_s			type;
	char			deck_count;
	char			cost;
	char			hands;
	effect_i		bonus;
	tome_i			tome;
	cflags<tag_s>	tags;
} item_data[] = {{"", ""},
// Common items
{".18 Derringer", "Деррингер", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon, CantStealOrLoose}},
{".38 Revolver", "Револьвер", CommonItem, 2, 4, 1, {CombatCheck, 3}, {}, {PhysicalWeapon}},
{".45 Automatic", "Кольт", CommonItem, 2, 4, 1, {CombatCheck, 4}, {}, {PhysicalWeapon}},
{"Ancient Tome", "Древняя книга", CommonItem, 2, 4, 0, {}, {2, 0, &ancient_tome}, {ExhaustToEffect, Tome}},
{"Axe", "Топор", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon, CombatBonusTwoHand}},
{"Bullwhip", "Кнут", CommonItem, 2, 2, 1, {CombatCheck, 1}, {}, {PhysicalWeapon, ExhaustToRerollDie}},
{"Cavalry Saber", "Кавалериская сабля", CommonItem, 2, 3, 1, {CombatCheck, 2}, {}, {PhysicalWeapon}},
{"Cross", "Крест", CommonItem, 2, 3, 1, {HorrorCheck, 1}, {}, {MagicalWeapon, CombatBonusVsUndead}},
{"Dark Cloak", "Темный плащ", CommonItem, 2, 2, 0, {EvadeCheck, 1}},
{"Dynamite", "Динамит", CommonItem, 2, 2, 2, {CombatCheck, 8}, {}, {PhysicalWeapon, DiscardAfterUse}},
{"Food", "Еда", CommonItem, 2, 1, 0, {Stamina, 1}, {}, {DiscardAfterUse}},
{"Knife", "Нож", CommonItem, 2, 2, 1, {CombatCheck, 3}, {}, {PhysicalWeapon}},
{"Lantern", "Фонарь", CommonItem, 2, 2, 0, {Luck}, {}, {ExhaustToRerollDie}},
{"Lucky Cigarette Case", "Удачливый портсигар", CommonItem, 2, 2, 0, {SkillCheck}, {}, {ExhaustToRerollDie, DiscardAfterUse}},
{"Map of Arkham", "Карта Аркхема", CommonItem, 2, 2, 0, {Movement, 1}, {}, {ExhaustToEffect}},
{"Motorcycle", "Мотоцикл", CommonItem, 2, 4, 0, {Movement, 2}, {}, {ExhaustToEffect}},
{"Old Journal", "Старый журнал", CommonItem, 2, 1, 0, {}, {1, 0, &old_journal}, {ExhaustToEffect, Tome}},
{"Research Materials", "Исследовательские материалы", CommonItem, 2, 1, 0, {Clue, 1}, {}, {DiscardAfterUse}},
{"Rifle", "Ружье", CommonItem, 2, 6, 2, {CombatCheck, 5}, {}, {PhysicalWeapon}},
{"Shotgun", "Дробовик", CommonItem, 2, 6, 2, {CombatCheck, 4}, {}, {PhysicalWeapon, SixDoubleSuccess}},
{"Tommy Gun", "Автомат", CommonItem, 2, 7, 2, {CombatCheck, 6}, {}, {PhysicalWeapon}},
{"Whiskey", "Виски", CommonItem, 2, 1, 0, {Sanity, 1}, {}, {DiscardAfterUse}},
//
{"Skill Bravery", "Храбрость", Skill, 2, 8, 0},
{"Skill Expert Occultist", "Оккултист", Skill, 2, 8, 0},
{"Skill Marksman", "Снайпер", Skill, 2, 8, 0},
{"Skill Speed", "Скорость", Skill, 2, 8, 0, {Speed, 1}},
{"Skill Sneak", "Скрытность", Skill, 2, 8, 0, {Sneak, 1}},
{"Skill Fight", "Бой", Skill, 2, 8, 0, {Fight, 1}},
{"Skill Will", "Воля", Skill, 2, 8, 0, {Will, 1}},
{"Skill Lore", "Знания", Skill, 2, 8, 0, {Lore, 1}},
{"Skill Luck", "Удача", Skill, 2, 8, 0, {Luck, 1}},
//
{"Bind Monster", "Подчинить монстра", Spell, 2},
{"Dread Curse of Azathoth", "Ужасное проклятие Азазоса", Spell, 4},
{"Enchant Weapon", "Зачоровать оружие", Spell, 3},
{"Find Gate", "Найти врата", Spell, 4},
{"Flesh Ward", "Защита плоти", Spell, 4},
{"Heal", "Исцеление", Spell, 3},
{"Mist of Releh", "Туман Рильеха", Spell, 4},
{"Red Sign of Shuddle Mell", "Красная метка Шудл Мелла", Spell, 2},
{"Shrivelling", "Иссушение", Spell, 5},
{"Voice of Ra", "Голос Ра", Spell, 3},
{"Wither", "Ломка", Spell, 6},
//
{"AlienStatue", "Статуя из другого мира", UniqueItem, 1},
{"AncientTablet", "Древняя плита", UniqueItem, 1},
{"BlueWatcherOfThePyramid", "Синий страж пирамиды", UniqueItem, 1},
};
assert_enum(item, BlueWatcherOfThePyramid);
getstr_enum(item);

void deck::create(stat_s group) {
	clear();
	for(auto& e : item_data) {
		if(e.type != group)
			continue;
		auto id = item_s(&e - item_data);
		for(auto i = 0; i < e.deck_count; i++)
			add(id);
	}
	zshuffle(data, count);
}

stat_s deck::getgroup(item_s id) {
	return item_data[id].type;
}

bool item::is(item_s i, tag_s value) {
	return item_data[i].tags.is(value);
}

int item::get(item_s i, stat_s id) {
	if(item_data[i].bonus.id == id)
		return item_data[i].bonus.count;
	return 0;
}

int item::gethands(item_s i) {
	return item_data[i].hands;
}