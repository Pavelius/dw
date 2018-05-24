#include "main.h"

static struct sorcery_i {
	const char*		id;
	const char*		name;
} sorcery_data[] = {{"", ""},
{"Glamour", "Гламур"},
{"Porte", "Порте"},
{"Pyeryem", "Пирием"},
{"Laerdom", "Лаэдрон"},
{"Sorte", "Сорте"},
};
assert_enum(sorcery, LastSorcery);
getstr_enum(sorcery);