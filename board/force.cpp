#include "main.h"

template<> forcei bsmeta<forcei>::elements[] = {{"�����", 1, 0},
{"�����", 1, 1},
{"����������", 2, 1},
{"����������", 2, 1},
{"�������", 2, 1}
};
assert_enum(force, Raiders);

void forcei::add(stringbuilder& sb) const {
	sb.add("%1 (%2i/%3i)", name, attack, defence);
}

void roll() {

}