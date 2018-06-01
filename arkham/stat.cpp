#include "main.h"

static struct stat_i {
	const char*		id;
	const char*		name;
} stat_data[] = {{"", ""},
{"Speed", "Скорость"},
{"Sneack", "Скрытность"},
{"Fight", "Бой"},
{"Will", "Воля"},
{"Lore", "Знания"},
{"Luck", "Удача"},
//
{"Sanity", "Рассудок"},
{"Stamina", "Жизнь"},
//
{"Clue", "Улика"},
{"Money", "Деньги"},
{"Focus", "Фокус"},
{"TurnToSkip", "Пропускает ход"},
{"Blessed", "Благословен"},
{"Movement", "Движение"},
// Special damage
{"Stamina Maximum", "Максимум жизни"},
{"Sanity Maximum", "Рассудок максимум"},
// Special checks
{"Combat Check", "Боевой бросок"},
{"Evade Check", "Бросок уклонения"},
{"Horror Check", "Бросок ужаса"},
{"Skill Check", "Бросок любого навыка"},
{"Spell Check", "Бросок заклинаний"},
// Calculated values
{"Test One Die"},
{"Test Two Die"},
//
{"Ally", "Союзник"},
{"Common Item", "Общий предмет"},
{"Skill", "Навык"},
{"Spell", "Заклинание"},
{"Unique Item", "Уникальный предмет"},
};
assert_enum(stat, UniqueItem);
getstr_enum(stat);