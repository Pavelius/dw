#include "main.h"

struct alignment_info {
	const char* id;
	const char* name;
} alignment_data[] = {{"Good", "Добрый"},
{"Lawful", "Законопослушный"},
{"Neutral", "Нейтральный"},
{"Chaotic", "Хаотичный"},
{"Evil", "Злой"},
};
assert_enum(alignment, Evil);
getstr_enum(alignment);