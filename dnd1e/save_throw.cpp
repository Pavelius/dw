#include "main.h"

struct save_i {
	const char*		id;
	const char*		name;
} save_data[] = {
	{"Save vs Paralization", "Защита от парализации"},
	{"Save vs Poison", "Защита от яда"},
	{"Save vs Death", "Защита от смерти"},
	{"Save vs Wands", "Защита от палочек"},
	{"Save vs Petrification", "Защита от окаменения"},
	{"Save vs Polymorph", "Защита от превращения"},
	{"Save vs Breath Weapon", "Защита от дыхания"},
	{"Save vs Spells", "Защита от магии"},
};
bsreq save_type[] = {
	BSREQ(save_i, id, text_type),
	BSREQ(save_i, name, text_type),
	{}
};
assert_enum(save, SaveVsSpells);
getstr_enum(save);
BSMETA(save);