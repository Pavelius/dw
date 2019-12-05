#include "main.h"

abilityi bsmeta<abilityi>::elements[] = {{"Courage", "Смелость"},
{"Wisdom", "Мудрость"},
{"Charisma", "Обаяние"},
{"Dexterity", "Ловкость"},
{"Strenght", "Сила"},
//
{"LP", "Жизненная энергия", "LE"},
{"AP", "Астральная энергия", "AE"},
{"AV", "Атака", "АV"},
{"PV", "Парирование", "PV"},
{"PVC", "Парировано атак", "ПрК"},
{"RS", "Броня", "Бр"},
{"Level", "Уровень", "Ур"},
};
assert_enum(ability, Level);

const char* getsnm(ability_s id) {
	return bsmeta<abilityi>::elements[id].short_name;
}