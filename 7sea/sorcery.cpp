#include "main.h"

static struct sorcery_i
{
	const char*		name[2];
} sorcery_data[] = {
	{{"",""}},
	{{"Glamour", "������"}},
	{{"Porte", "�����"}},
	{{"Pyeryem", "������"}},
	{{"Laerdom", "�������"}},
	{{"Sorte", "�����"}},
};
assert_enum(sorcery, LastSorcery);
getstr_enum(sorcery);