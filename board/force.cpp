#include "main.h"

BSDATA(forcei)= {{"�����", 1, 0},
{"�����", 1, 1},
{"����������", 2, 1},
{"����������", 2, 1},
{"�������", 2, 1}
};
assert_enum(forcei, Raiders)

void forcei::add(stringbuilder& sb) const {
	sb.add("%1 (%2i/%3i)", name, attack, defence);
}

void roll() {

}