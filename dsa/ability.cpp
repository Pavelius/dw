#include "main.h"

abilityi bsmeta<abilityi>::elements[] = {{"Courage", "Смелость", "MU"},
{"Wisdom", "Мудрость"},
{"Charisma", "Обаяние", "CH"},
{"Dexterity", "Ловкость"},
{"Strenght", "Сила", "KK"},
//
{"LP", "Жизненная энергия", "LE"},
{"AP", "Астральная энергия", "AE"},
{"AV", "Атака", "АV"},
{"PV", "Парирование", "PV"},
{"PVC", "Парировано атак", "ПрК"},
{"RS", "Броня", "RS"},
{"Level", "Уровень", "LV"},
};
assert_enum(ability, Level);

const char* getsnm(ability_s id) {
	return bsmeta<abilityi>::elements[id].short_name;
}