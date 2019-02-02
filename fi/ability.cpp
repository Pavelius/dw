#include "main.h"

static struct ability_info {
	const char*			id;
	const char*			name;
	const char*			nameof;
} ability_data[] = {{"Strenght", "����", "����"},
{"Agility", "�����������", "�����������"},
{"Wits", "��", "���"},
{"Empathy", "��������", "��������"},
};
assert_enum(ability, Empathy);
getstr_enum(ability);

const char* character::getnameof(ability_s id) {
	return ability_data[id].nameof;
}