#include "main.h"

static struct sorcery_i {
	const char*		id;
	const char*		name;
} sorcery_data[] = {{"", ""},
{"Glamour", "������"},
{"Porte", "�����"},
{"Pyeryem", "������"},
{"Laerdom", "�������"},
{"Sorte", "�����"},
};
assert_enum(sorcery, LastSorcery);
getstr_enum(sorcery);