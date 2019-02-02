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
static quest cabballa_of_saboth = {AnyLocation, "Вы принялись изучать очень практичную книгу.", {Lore, -2}, {{"Ничего нового вы не почерпнули."},
{"После длительного изучения вы узнали новый навык.", {AddSkill, Discard}}
}};
static quest cultes_des_goules = {AnyLocation, "Вы принялись изучать очень страшную книгу ритуалов.", {Lore, -2}, {{"Ничего нового вы не почерпнули."},
{"После длительного изучения вы узнали новый темнй ритуал.", {AddSpell, Add1Clue, Discard}}
}};
static quest nameless_cults = {AnyLocation, "Книга безымянных культов очень заинтересовала вас, когда вы начали листать ее страницы.", {Lore, -1}, {{"Но, ничего нового вы не почерпнули."},
{"После длительного изучения вы узнали новый темный ритуал, который пшатнул ваш рассудок.", {AddSpell, Lose1Sanity, Discard}}
}};
static quest necrominion = {AnyLocation, "Некроминион описывал принципы жизни и смерти, а также то, как можно оживлять мертвых.", {Lore, -2}, {{"Немотря на ваши попытки вы ничего так и не поняли."},
{"После длительного изучения вы узнали страшный ритал, связанный со смертью.", {AddSpell, Lose2Sanity}}
}};
static quest king_in_yellow = {AnyLocation, "Король в желтом описывал потусторонние миры.", {Lore, -2}, {{"Вы несмогли осознать глубину написанного."},
{"После длительного изучения вы осознали ужасные способы попасть в другие миры и получили некую информацию о древних.", {Add4Clue, Lose1Sanity, Discard}}
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
	cflags<feature_s>	tags;
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
{"CabalaOfSaboth", "Кабала Саббота", UniqueItem, 2, 5, {}, {{Lose2Movement}, &cabballa_of_saboth}, {Tome}},
{"CultesDesGoules", "Культы людоедов", UniqueItem, 2, 3, {}, {{Lose2Movement}, &cultes_des_goules}, {Tome}},
{"DragonsEye", "Глаз дракона", UniqueItem, 1, 6},
{"ElderSign", "Знак древних", UniqueItem, 4, 5},
{"EnchantedBlade", "Колдовской клинок", UniqueItem, 2, 6, {CombatCheck, 4}, {}, {OneHanded, MagicalWeapon}},
{"EnchantedJewelry", "Заколдованная драгоценность", UniqueItem, 1, 3},
{"EnchantedKnife", "Колдовской кинжал", UniqueItem, 2, 5, {CombatCheck, 3}, {}, {OneHanded, MagicalWeapon}},
{"FluteOfTheOuterGods", "Флейта запредельных богов", UniqueItem, 1, 8, {}, {{Lose3Stamina, Lose3Sanity}}},
{"GateBox", "Короб врат", UniqueItem, 1, 4},
{"HealingStone", "Камень исцеления", UniqueItem, 1, 8},
{"HolyWater", "Святая вода", UniqueItem, 4, 4, {CombatCheck, 6}, {}, {MagicalWeapon, TwoHanded, DiscardAfterUse}},
{"LampOfAlhazred", "Лампа Аль-Хазреда", UniqueItem, 1, 7, {CombatCheck, 5}, {}, {TwoHanded}},
{"NamelessCults", "Безымянные культы", UniqueItem, 2, 3, {}, {{Lose1Movement}, &nameless_cults}, {Tome}},
{"Necronomicon", "Некроминион", UniqueItem, 1, 6, {}, {{Lose2Movement}, &necrominion}, {Tome}},
{"ObsidianStatue", "Обсидиановая статуя", UniqueItem, 1, 4},
{"PallidMask", "Бледная маска", UniqueItem, 1, 4, {EvadeCheck, 2}},
{"PowderOfIbnGhazi", "Порошек Ибн-Гази", UniqueItem, 2, 6, {CombatCheck, 9}, {{Lose1Sanity, Discard}}, {MagicalWeapon, TwoHanded}},
{"RubyOfRlyeh", "Рубин Р'льэха", UniqueItem, 1, 8, {Movement, 3}},
{"SilverKey", "Серебрянный ключ", UniqueItem, 1, 4, {}, {{UsePart}, 0, 3}},
{"SwordOfGlory", "Меч славы", UniqueItem, 1, 8, {CombatCheck, 6}, {}, {TwoHanded}},
{"TheKingInYellow", "Король в желтом", UniqueItem, 2, 2, {}, {{Lose2Movement}, &king_in_yellow}, {Tome}},
{"WardingStatue", "Охраняющая статуя", UniqueItem, 1, 6},
//
{"Anna Kaslow", "Анна Каслов", Ally, 1, 10, {Luck, 2}, {}, {}},
{"Duke", "Дюк", Ally, 1, 10, {SanityMaximum, 1}, {}, {}},
{"Eric Colt", "Эрик Кольт", Ally, 1, 10, {Speed, 2}, {}, {}},
{"John Legrasse", "Джон Леграссе", Ally, 1, 10, {Will, 2}, {}, {}},
{"Professor Armitage", "Профессор Эрмитаж", Ally, 1, 10, {Lore, 2}, {}, {}},
{"Richard Upton Pickman", "Ричард Аптон Пикман", Ally, 1, 10, {{Luck, 1}, {Speed, 1}}, {}, {}},
{"Ruby Standish", "Руби Стендиш", Ally, 1, 10, {Sneak, 2}, {}, {}},
{"Ryan Dean", "Райн Дин", Ally, 1, 10, {{Sneak, 1}, {Will, 1}}, {}, {}},
{"Sir William Brinton", "Сэр Вильям Брайтон", Ally, 1, 10, {{StaminaMaximum, 1}}, {}, {}},
{"Thomas F. Malone", "Томас Ф.Малоун", Ally, 1, 10, {{Fight, 1}, {Lore, 1}}, {}, {}},
{"Tom \"Mountain\" Murphy", "Том \"Гора\" Мерфи", Ally, 1, 10, {{Fight, 2}}, {}, {}},
//
{"Byakhee", "Бьякхи", Monster, 3, 0, {}, {}, {}, {Flying, -2, {-1, 1}, 1, {0, 2}, {}, "Внезапно в ночи послышался шум крыльев. Вы подняли голову и увидели страшное чудовище - человекообразое с серой кожей и огромными крыльями. Покрытая панцирем голова склонилась над вами щелкая зубами."}},
{"Chthonian", "Хтоническое чудище", Monster, 2, 0, {}, {}, {}, {Unique, 1, {-2, 2}, 3, {-3, 3}, {}, "Прямо из земли показалась огромная голова чудовищного червы, в диаметре метров шесть. Вместо пасти из его оболочки вылазило можество щупальцев, которые пытались схватить вас."}},
{"Cultist", "Культист", Monster, 6, 0, {}, {}, {}, {Normal, -3, {0, 0}, 1, {1, 1}, {}, "Темная фигура в рясе с капюшоном возникла из неоткуда прямо перед вами.\n - Во имя Темного бога! - произнесла фигура достав нож."}},
{"Dark Young", "Темная молодь", Monster, 3, 0, {}, {}, {}, {Stationary, -2, {0, 3}, 3, {-1, 3}, {PhysicalResistance, NightmarishI}, "Прямо к вам направлялось огромной существо больше похожее на дерево. Вместо веток у него были толстые щупальцы, вместо корней чешуйчатые ноги. Земля сотрясалась под приближающими шагами гиганских копыт. На месте ствола сиял огромный зубастый рот."}},
{"Dhole", "Червь", Monster, 3, 1, {}, {}, {}, {Normal, -1, {-1, 4}, 3, {-3, 4}, {PhysicalResistance, MagicalResistance, OvervelmingI, NightmarishI}, "Огромный червь толщиной в несколько метров вылез и подземли и надвис над вами. Его пасть состоящая из трех частей пыталась вам схватить."}},
{"Dimension Shambler", "Бродящий меж мирами", Monster, 2, 0, {}, {}, {}, {Fast, -3, {-2, 1}, 1, {-2, 0}, {}, "Внезапно перед вами раздалась яркая вспышка из которой показалась уродливая человекаобразная фигура. Вместо пальцев были толстые щупальца, которые тянулись к вам."}},
{"Elder Thing", "Древнейший", Monster, 2, 0, {}, {}, {}, {Normal, -2, {-3, 2}, 2, {0, 1}, {}, "Большое существо с крыльями и щупальцами преградило ваш путь. Его четыре глаза, расположенных на конце щупальцев, отросших на голове внимательно изучали вас."}},
{"Fire Vampire", "Огненный вампир", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {-2, 2}, {Ambush, PhysicalResistance}, "Впереди вы увидели множество кружащихся огоньков. Поначалу они были похожи на бабочек, но потом вы поняли что это огонь, летающий в воздухе. Вскоре, огоньки один за одним соединились в человекообразную фигуру, которая тут же набросилась на вас."}},
{"Flying Polyp", "Летучий полип", Monster, 1, 0, {}, {}, {}, {Flying, 0, {-2, 4}, 3, {-3, 3}, {PhysicalResistance, NightmarishI, OvervelmingI}, "Высоко над головой появилось нечто. Это было пятно огромных размеров с которого вылазили щупальцы, еще мгновение и это пятно в 4 метра в диаметре обрушилось прямо на вас."}},
{"Formless Spawn", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Ghost", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Ghoul", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"God of the Bloody Tongue", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Gug", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Haunter of the Dark", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"High Priest", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Hound of Tindalos", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Maniac", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Mi-Go", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Nightgaunt", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Shoggoth", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Star Spawn", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"The Black Man", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"The Bloated Woman", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"The Dark Pharoah", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Vampire", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Warlock", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
{"Witch", "", Monster, 2, 0, {}, {}, {}, {Flying, 0, {0, 0}, 1, {0, 0}, {}, ""}},
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

stat_s item::getgroup(card_s id) {
	return card_data[id].type;
}

bool item::is(card_s i, feature_s value) {
	return card_data[i].tags.is(value);
}

char item::getcost(card_s i) {
	return card_data[i].cost;
}

char item::getcount(card_s i) {
	return card_data[i].deck_count;
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

char* item::getname(char* result, const char* result_maximum, card_s i, bool description, bool exhaused, char use, bool price, int mode_cost) {
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
		if(price)
			szprints(zend(result), result_maximum, "Стоит %1i$. ", card_data[i].cost + mode_cost);
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
	case Sanity:
		return card_data[type].monster.horror[1];
	case CombatCheck:
		switch(getid()) {
		case Cultist:
			if(game.is(Hastur))
				return -2;
		default:
			return card_data[type].monster.combat[0];
		}
	case Stamina:
		return card_data[type].monster.combat[1];
	case Fight:
		return card_data[type].monster.toughness;
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

monster_color_s monster::getcolor() const {
	auto t = getid();
	if(t == Cultist) {
		if(game.is(Hastur))
			return Flying;
	}
	return card_data[t].monster.color;
}

const use_info& item::getuse(card_s i) {
	return card_data[i].use;
}

char item::getmark(card_s i) {
	return card_data[i].use.usable;
}