#include "main.h"

static quest ancient_tome = {AnyLocation, "Попробывать изучить древний том.", {Lore, -1}, {{"Ничего нового для себя вы не почерпнули."},
{"Вы изучили древний волшебный ритуал.", {AddSpell, Discard}},
}};
static quest old_journal = {AnyLocation, "Изучить содержимое старого журнала.", {Lore, -1}, {{"Ничего нового для себя вы не почерпнули."},
{"В старом журнале содержались важные и полезные данные о древних сектах и культах.", {Add3Clue, Discard}},
}};
static quest alien_statue = {AnyLocation, "Вы начали пристально изучать статую. Похоже она живая и ее поведение каким-то образом влияет на вас.", {TestOneDie}, {{"Вы почувствовали полное истощение.", {Lose2Stamina}},
{"Вы постигли темные знания другого мира.", {AddSpellOr3Clue}},
}};
static quest ancient_tablet = {AnyLocation, "Записи на древней табличке выглядят незнакомыми, но вм надо время чтобы их расшифровать.", {TestTwoDie}, {{"После длительного изучения вы получили факты о древних.", {Add2Clue}},
{"Давно забытые знания научили вас заклинанию.", {AddSpell}},
}};
static quest book_of_dzyan = {AnyLocation, "Вы принялись изучать древнюю книжку с востока.", {Lore, -1}, {{"Ничего нового вы не почерпнули."},
{"После длительного изучения вы узнали новое заклинание.", {AddSpell, Lose1Sanity, UsePart}}
}};
static quest langrange = {AnyLocation, 0, {}, {{"Таинственный человек в итоге человек разделил с вами трапезу.", {RestoreAll}}}};
static const struct card_info {
	const char*		id;
	const char*		name;
	stat_s			type;
	char			deck_count;
	char			cost;
	roll_info		bonus[2];
	use_info		use;
	cflags<tag_s>	tags;
	monster_info	monster;
} card_data[] = {{"", ""},
// Common items
{".18 Derringer", "Деррингер", CommonItem, 2, 3, {CombatCheck, 2}, {}, {PhysicalWeapon, CantStealOrLoose, OneHanded}},
{".38 Revolver", "Револьвер", CommonItem, 2, 4, {CombatCheck, 3}, {}, {PhysicalWeapon, OneHanded}},
{".45 Automatic", "Кольт", CommonItem, 2, 4, {CombatCheck, 4}, {}, {PhysicalWeapon, OneHanded}},
{"Ancient Tome", "Древняя книга", CommonItem, 2, 4, {}, {{Lose2Movement}, &ancient_tome}, {ExhaustToEffect, Tome}},
{"Axe", "Топор", CommonItem, 2, 3, {CombatCheck, 2}, {}, {PhysicalWeapon, CombatBonusTwoHand, OneHanded}},
{"Bullwhip", "Кнут", CommonItem, 2, 2, {CombatCheck, 1}, {}, {PhysicalWeapon, ExhaustToRerollDie, OneHanded}},
{"Cavalry Saber", "Кавалериская сабля", CommonItem, 2, 3, {CombatCheck, 2}, {}, {PhysicalWeapon, OneHanded}},
{"Cross", "Крест", CommonItem, 2, 3, {HorrorCheck, 1}, {}, {MagicalWeapon, CombatBonusVsUndead, OneHanded}},
{"Dark Cloak", "Темный плащ", CommonItem, 2, 2, {EvadeCheck, 1}},
{"Dynamite", "Динамит", CommonItem, 2, 2, {CombatCheck, 8}, {}, {PhysicalWeapon, DiscardAfterUse, TwoHanded}},
{"Food", "Еда", CommonItem, 2, 1, {Stamina, 1}, {}, {DiscardAfterUse}},
{"Knife", "Нож", CommonItem, 2, 2, {CombatCheck, 3}, {}, {PhysicalWeapon, OneHanded}},
{"Lantern", "Фонарь", CommonItem, 2, 2, {Luck}, {}, {ExhaustToRerollDie}},
{"Lucky Cigarette Case", "Удачливый портсигар", CommonItem, 2, 2, {SkillCheck}, {}, {ExhaustToRerollDie, DiscardAfterUse}},
{"Map of Arkham", "Карта Аркхема", CommonItem, 2, 2, {Movement, 1}, {}, {ExhaustToEffect}},
{"Motorcycle", "Мотоцикл", CommonItem, 2, 4, {Movement, 2}, {}, {ExhaustToEffect}},
{"Old Journal", "Старый журнал", CommonItem, 2, 1, {}, {{Lose1Movement}, &old_journal}, {ExhaustToEffect, Tome}},
{"Research Materials", "Исследовательские материалы", CommonItem, 2, 1, {Clue, 1}, {}, {DiscardAfterUse}},
{"Rifle", "Ружье", CommonItem, 2, 6, {CombatCheck, 5}, {}, {PhysicalWeapon, TwoHanded}},
{"Shotgun", "Дробовик", CommonItem, 2, 6, {CombatCheck, 4}, {}, {PhysicalWeapon, SixDoubleSuccess, TwoHanded}},
{"Tommy Gun", "Автомат", CommonItem, 2, 7, {CombatCheck, 6}, {}, {PhysicalWeapon, TwoHanded}},
{"Whiskey", "Виски", CommonItem, 2, 1, {Sanity, 1}, {}, {DiscardAfterUse}},
//
{"Skill Bravery", "Храбрость", Skill, 2, 8},
{"Skill Expert Occultist", "Оккултист", Skill, 2, 8},
{"Skill Marksman", "Снайпер", Skill, 2, 8},
{"Skill Speed", "Скорость", Skill, 2, 8, {Speed, 1}},
{"Skill Sneak", "Скрытность", Skill, 2, 8, {Sneak, 1}},
{"Skill Fight", "Бой", Skill, 2, 8, {Fight, 1}},
{"Skill Will", "Воля", Skill, 2, 8, {Will, 1}},
{"Skill Lore", "Знания", Skill, 2, 8, {Lore, 1}},
{"Skill Luck", "Удача", Skill, 2, 8, {Luck, 1}},
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
{"AlienStatue", "Статуя из другого мира", UniqueItem, 1, 5, {}, {{Lose2Movement, Lose1Sanity}, &alien_statue}, {ExhaustToEffect}},
{"AncientTablet", "Древняя плита", UniqueItem, 1, 8, {}, {{Lose3Movement}, &ancient_tablet}, {DiscardAfterUse}},
{"BlueWatcherOfThePyramid", "Синий страж пирамиды", UniqueItem, 1, 4, {}, {{Lose2Stamina}}, {AutoCombatCheck, AutoGateCheck, DiscardAfterUse}},
{"BookOfDzyan", "Книга Джинов", UniqueItem, 1, 3, {}, {{Lose2Movement}, &book_of_dzyan, 2}, {Tome}},
{"CabalaOfSaboth", "Кабала Саббота", UniqueItem, 2, 5},
{"CultesDesGoules", "Культы людоедов", UniqueItem, 2, 3},
{"DragonsEye", "Глаз дракона", UniqueItem, 1, 6},
{"ElderSign", "Знак древних", UniqueItem, 4, 5},
{"EnchantedBlade", "Колдовской клинок", UniqueItem, 2, 6, {CombatCheck, 4}, {}, {OneHanded, MagicalWeapon}},
{"EnchantedJewelry", "Заколдованная драгоценность", UniqueItem, 1, 3},
{"EnchantedKnife", "Колдовской кинжал", UniqueItem, 2, 5, {CombatCheck, 3}, {}, {OneHanded, MagicalWeapon}},
{"FluteOfTheOuterGods", "Флейта запредельных богов", UniqueItem, 1, 8, {}, {{Lose3Stamina, Lose3Sanity}}},
{"GateBox", "Короб врат", UniqueItem, 1, 4},
{"HealingStone", "Камень исцеления", UniqueItem, 1, 8},
{"HolyWater", "Святая вода", UniqueItem, 4, 4},
{"LampOfAlhazred", "Лампа Аль-Хазреда", UniqueItem, 1, 7},
{"NamelessCults", "Безымянные культы", UniqueItem, 2, 3, {}, {{Lose2Movement}, &ancient_tome}, {ExhaustToEffect, Tome}},
{"Necronomicon", "Некроминион", UniqueItem, 1, 6, {}, {{Lose2Movement}, &ancient_tome}, {ExhaustToEffect, Tome}},
{"ObsidianStatue", "Обсидиановая статуя", UniqueItem, 1, 4},
{"PallidMask", "Бледная маска", UniqueItem, 1, 4},
{"PowderOfIbnGhazi", "Порошек Ибн-Гази", UniqueItem, 2, 6},
{"RubyOfRlyeh", "Рубин Р'льэха", UniqueItem, 1, 8},
{"SilverKey", "Серебрянный ключ", UniqueItem, 1, 4},
{"SwordOfGlory", "Меч славы", UniqueItem, 1, 8},
{"TheKingInYellow", "Король в желтом", UniqueItem, 2, 2, {}, {{Lose2Movement}, &ancient_tome}, {ExhaustToEffect, Tome}},
{"WardingStatue", "Охраняющая статуя", UniqueItem, 1, 6},
//
{"Anna Kaslow", "анна Каслов", Ally, 1, 10, {Luck, 2}, {}, {}},
{"Duke", "Дюк", Ally, 1, 10, {SanityMaximum, 1}, {}, {}},
{"Eric Colt", "Эрик Кольт", Ally, 1, 10, {Speed, 2}, {}, {}},
{"John Legrasse", "Джон Леграссе", Ally, 1, 10, {Will, 2}, {}, {}},
{"Professor Armitage", "Профессор Эрмитаж", Ally, 1, 10, {Lore, 2}, {}, {}},
{"Richard Upton Pickman", "", Ally, 1, 10, {{Luck, 1}, {Speed, 1}}, {}, {}},
{"Ruby Standish", "", Ally, 1, 10, {Sneak, 2}, {}, {}},
{"Ryan Dean", "Райн Дин", Ally, 1, 10, {{Sneak, 1}, {Will, 1}}, {}, {}},
{"Sir William Brinton", "Сэр Вильям Брайтон", Ally, 1, 10, {{StaminaMaximum, 1}}, {}, {}},
{"Thomas F. Malone", "", Ally, 1, 10, {{Fight, 1}, {Lore, 1}}, {}, {}},
{"Tom \"Mountain\" Murphy", "Том \"Гора\" Мерфи", Ally, 1, 10, {{Fight, 2}}, {}, {}},
//
{"Byakhee", "Бьякхи", Monster, 3, 0, {}, {}, {}, {Flying, -2, {-1, 1}, 1, {0, 2}, {}, "Внезапно в ночи послышался шум крыльев. Вы подняли голову и увидели страшное чудовище - человекообразое с серой кожей и огромными крыльями."}},
{"Chthonian", "Чхониан", Monster, 2, 0, {}, {}, {}, {Unique, 1, {-2, 2}, 3, {-3, 3}}},
{"Cultist", "Культист", Monster, 6, 0, {}, {}, {}, {Normal, -3, {0, 0}, 1, {1, 1}}},
{"Dark Young", "Темная молодь", Monster, 3, 0, {}, {}, {}, {Stationary, -2, {0, 3}, 3, {-1, 3}, {PhysicalResistance, NightmarishI}}},
{"Dhole", "", Monster, 3, 1, {}, {}, {}, {Normal, -1, {-1, 4}, 3, {-3, 4}, {PhysicalResistance, MagicalResistance, OvervelmingI, NightmarishI}}},
{"Dimension Shambler", "", Monster, 2, 0, {}, {}, {}, {Fast, -3, {-2, 1}, 1, {-2, 0}}},
{"Elder Thing", "", Monster, 2, 0, {}, {}, {}, {Normal, -2, {-3, 2}, 2, {0, 1}}},
{"Fire Vampire", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {-2, 2}, {Ambush, PhysicalResistance}}},
{"Zombie", "Зобми", Monster, 2, 0, {}, {}, {}, {Normal, 1, {-2, 2}, 3, {-3, 3}, {Undead}, "Впереди показалая фигура человека. Она очень быстро приблежалась к вам выставив вперед руки. Глаза горели неестественным цветом - похоже это оживший зомби."}},
};
assert_enum(card, Zombie);
getstr_enum(card);

void deck::create(stat_s group) {
	clear();
	for(auto& e : card_data) {
		if(e.type != group)
			continue;
		auto id = card_s(&e - card_data);
		for(auto i = 0; i < e.deck_count; i++)
			add(id);
	}
	zshuffle(data, count);
}

stat_s deck::getgroup(card_s id) {
	return card_data[id].type;
}

bool item::is(card_s i, tag_s value) {
	return card_data[i].tags.is(value);
}

int item::get(card_s i, stat_s id) {
	auto bonus = 0;
	if(card_data[i].bonus[0].id == id)
		bonus = card_data[i].bonus[0].bonus;
	else if(card_data[i].bonus[1].id == id)
		bonus = card_data[i].bonus[1].bonus;
	return bonus;
}

int	item::gethands(card_s i) {
	auto result = 0;
	if(is(i, OneHanded))
		result = 1;
	else if(is(i, TwoHanded))
		result = 2;
	return result;
}

bool hero::usable(card_s i) const {
	for(auto a : card_data[i].use.before) {
		if(!isallow(a))
			return false;
	}
	return true;
}

char* item::getname(char* result, const char* result_maximum, card_s i, bool description, bool exhaused, char use) {
	auto need_scope = description || exhaused;
	result[0] = 0;
	if(need_scope)
		szprints(zend(result), result_maximum, "[");
	if(exhaused && !description)
		szprints(zend(result), result_maximum, "~");
	szprints(zend(result), result_maximum, card_data[i].name);
	auto use_maximum = card_data[i].use.usable;
	if(use && use_maximum)
		szprints(zend(result), result_maximum, "(%1i/%2i)", use, use_maximum);
	if(need_scope)
		szprints(zend(result), result_maximum, "]");
	if(description) {
		szprints(zend(result), result_maximum, ": ");
		if(card_data[i].bonus[0].bonus) {
			card_data[i].bonus[0].getname(zend(result), result_maximum);
			if(card_data[i].bonus[1].bonus) {
				szprints(zend(result), result_maximum, ", ");
				card_data[i].bonus[1].getname(zend(result), result_maximum);
			}
			szprints(zend(result), result_maximum, ". ");
		}
		for(auto e : card_data[i].tags)
			szprints(zend(result), result_maximum, getstr(e));
	}
	auto pe = zend(result);
	while(pe > result && (pe[-1] == ' '))
		*--pe = 0;
	return result;
}

char monster::get(stat_s id) {
	switch(id) {
	case EvadeCheck: return card_data[type].monster.awareness;
	case HorrorCheck: return card_data[type].monster.horror[0];
	case Sanity: return card_data[type].monster.horror[1];
	case CombatCheck: return card_data[type].monster.combat[0];
	case Stamina: return card_data[type].monster.combat[1];
	case Fight: return card_data[type].monster.toughness;
	default: return 0;
	}
}

bool monster::is(monster_flag_s id) const {
	return card_data[type].monster.flags.is(id);
}

const char* monster::getname() const {
	return card_data[type].name;
}

const char* monster::gettext() const {
	return card_data[type].monster.text;
}

const use_info& item::getuse(card_s i) {
	return card_data[i].use;
}

char item::getmark(card_s i) {
	return card_data[i].use.usable;
}