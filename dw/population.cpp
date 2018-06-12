#include "main.h"

static struct population_info {
	const char*		id;
	const char*		name;
	const char*		text;
} population_data[] = {{"Exodus", "Заброшенное", "Большинство домов выглядели заброшеными и скорее всего в них никто не жил."},
{"Shrinking", "Гинущее", "Многие дома были заброшены."},
{"Steady", "Населенное", ""},
{"Growing", "Растущее", "На улице было много народу."},
{"Booming", "Переполненное", "Здесь было очень много народу. Множество палаток и тентов покрывали улицы - в них жили люди."},
};
assert_enum(population, Booming);
getstr_enum(population);