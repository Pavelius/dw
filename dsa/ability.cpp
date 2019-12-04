#include "main.h"

abilityi bsmeta<abilityi>::elements[] = {{"Courage", "Смелость"},
{"Wisdom", "Мудрость"},
{"Charisma", "Обаяние"},
{"Dexterity", "Ловкость"},
{"Strenght", "Сила"},
//
{"LP", "Жизнь", "ОЗ"},
{"AP", "Магия", "ОА"},
{"AV", "Атака", "Ат"},
{"PV", "Парирование", "Пр"},
{"PVC", "Парировано атак", "ПрК"},
{"RS", "Доспех", "Бр"},
{"Level", "Уровень", "Ур"},
};
assert_enum(ability, Level);