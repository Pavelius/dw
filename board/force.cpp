#include "main.h"

template<> forcei bsmeta<forcei>::elements[] = {{"Пчелы", 1, 0},
{"Крысы", 1, 1},
{"Кротокрысы", 2, 1},
{"Грязекрабы", 2, 1},
{"Рейдеры", 2, 1}
};
assert_enum(force, Raiders);

void forcei::add(stringbuilder& sb) const {
	sb.add("%1 (%2i/%3i)", name, attack, defence);
}

void roll() {

}