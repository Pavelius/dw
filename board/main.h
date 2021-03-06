#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

enum force_s : unsigned char {
	Bees, Rats, RatMutants, CrabMutants, Raiders
};
enum item_s : unsigned char {
	Pistol, Shootgun, MachineGun,
	CombatArmor,
};

struct forcei {
	const char*		name;
	char			attack;
	char			defence;
	char			power;
	char			hits;
	void			add(stringbuilder& sb) const;
};
struct combat {
	char			actions[3];
	void			apply(forcei& attacker, forcei& defender) const;
	void			roll();
};
struct character : forcei {
};