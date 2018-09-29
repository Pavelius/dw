#include "main.h"

static struct feat_info {
	const char*			id;
	const char*			name;
	slot_s				slot;
} feat_data[] = {{"No feat", "Нет особенности"},
{"Armor Proficiency (light)", "Ношение легкой брони"},
{"Armor Proficiency (medium)", "Ношение средней брони"},
{"Armor Proficiency (heavy)", "Ношение тяжелой брони"},
{"Shield Proficiency", "Владение щитом"},
{"Simple weapon proficiency", "Владение простым оружием"},
{"Martial weapon proficiency", "Владение смертельным оружием"},
{"Elf weapon training", "Тренировка с оружием эльфов"},
{"Dwarven weapon training", "Тренировка с оружием карликов"},
{"Rogue weapon training", "Тренировка с оружием бродяг"},
{"Save Strenght", "Спас-бросок по силе"},
{"Save Dexterity", "Спас-бросок по ловкости"},
{"Save Constitution", "Спас-бросок по телосложению"},
{"Save Intellegence", "Спас-бросок по интеллекту"},
{"Save Wisdow", "Спас-бросок по мудросте"},
{"Save Charisma", "Спас-бросок по харизме"},
//
{"Brave", "Храбрость"},
{"Darkvision", "Инфразрение"},
{"Dwarven Resilience", "Выносливость карликов"},
{"Dwarven Toughness", "Живучесть карликов"},
{"Fey Ancestry", "Мистические предки"},
{"Keen Sences", "Обостренные чувства"},
{"Lucky", "Везение"},
{"Mask of the Wild", "Маска природы"},
{"Naturally Stealthy", "Врожденная скрытность"},
{"Stonecunning", "Обработка камня"},
{"Trance", "Транс"},
// Классовые способности воина
{"Second Wind", "Второе дыхание", SecondWindSlot},
{"Action Surge", "Ускорение", ActionSurgeSlot},
{"Extra Attack", "Дополнительная атака"},
{"Indomitable", "Неуязвимый", IndomitableSlot},
{"Improved Critical", "Улучшенный критический"},
{"Remarkable Athlete", "Выдающийся атлет"},
{"Superior Critical", "Выдающийся критический"},
{"Survivor", "Крепкий орешек"},
// Классовые способности клерика
{"Channel Divinity", "Касание божества", ChannelDivinitySlot},
{"Destroy Undead", "Уничтожение мертвых"},
{"Divine Intervention", "Божественное чудо"},
{"Disciple of Life", "Учение Жизни"},
{"Blessed Healer", "Священный целитель"},
{"Divine Strike", "Праведный гнев"},
{"Supreme Healing", "Максимальное исцеление"},
// Стили боя
{"Archery style", "Стиль стрелка"},
{"Defense style", "Стиль защиты"},
{"Dueling style", "Стиль фехтовальщика"},
{"Great weapon fighting style", "Стиль сражения огромным оружием"},
{"Protection style", "Стиль сражения с щитом"},
{"Two-weapon fighting style", "Стиль сражения двумя оружиями"},
};
assert_enum(feat, StyleTwoWeaponFighting);
getstr_enum(feat);