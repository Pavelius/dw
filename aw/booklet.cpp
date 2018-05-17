#include "main.h"

struct question {
	const char*			text;
	int					value;
};

static struct booklet_i {
	const char*			id;
	const char*			name;
	char				stats[4][5];
	char				choose_moves;
	adat<move_s, 8>		moves;
	adat<move_s, 4>		start;
} booklet_data[] = {
	{},
	{"angel", "�����",
	{{1, 0, 1, 2, -1}, {1, 1, 2, 0, -1}, {-1, 1, 0, 2, 1}, {2, 0, -1, 2, -1}}, 2,
	{{SixthSense, Infirmary, ProfessionalCompassion, BattlefieldGrace, HealingTouch, TouchedByDeath}, 6},
	},
	{"battlebaby", "��������",
	{{3, -1, 1, 1, 0}, {3, -1, 2, 0, -1}, {3, -2, 1, 1, 1}, {3, 0, 1, 1, -1}}, 2,
	{{DangerousAndSexy, IceCold, Merciless, VisionOfDeath, PerfectInstincts, ImpossibleReflexes}, 6},
	},
	{"gunlugger", "�������",
	{{1, 2, -1, 1, 0}, {-1, 2, -2, 1, 2}, {1, 2, -2, 2, -1}, {2, 2, -2, 0, 0}}, 3,
	{{BattleHardened, FuckThisShit, BattlefieldInstincts, InsanoLikeDrano, PreparedForTheInevitable, Bloodcrazed, NotToBeFuckWith}, 7},
	}
};
assert_enum(booklet, TheGunlugger);
getstr_enum(booklet)

static struct move_i {
	const char*			id;
	const char*			name;
	const char*			descritpion;
} move_data[] = {
	{"Sixth sense", "������ �������", "����� �� ���������� ���� ����� �������� �����, ����� ��� +����, ������ ���� ����� ������ ��� +�������."},
	{"Infirmary", "�������", "�� ��������� �������, ������� ����� � �������� ����������������, ���������������� ������������ � ����� ������������. ������� � ���� ��������� � ������ �������� ��� ����, ��� ������� ��� ��������."},
	{"Professional compassion", "���������������� �����������", "����� ��������� ����-��, ������, ���� ������, ����� ��� +����, ������ ���� ����� ������ ��� +�������."},
	{"Battlefield grace", "��������� �� ���� ���", "����� �� ���������� �� ������, � �� ����������, �� ��������� + 1 �����."},
	{"Healing touch", "����������� �������", "������� ���� �� ��������, ������ ��� ���� ����� � ����� ��� +�������. �� 10+ ������ 1 �������. �� 7-9 ������ 1 �������, �� �� ���������� ��� ����, ����������� ������������� ������ ������ ��������. ��� �������: ��-������, �� ��� �� �������. ��-������, �� ���������� ���� � ��� ����� �������� ����� ��� ������ � ��� ����������."},
	{"Touched by death", "������������� ������", "����� ���-��, � ��� �� ����������, �������, �� ��������� + 1 � ������� (����. + 3)."},
	//
	{"Dangerous and sexy", "������� � �����������", "����� �� ������������ � ���������� ��������, �������� +�����. �� 10+ ������ 2 �����. �� 7-9 ������ 1 ����. ������� ����� 1 � 1, ����� ���������� ���������� ������� � �������������� ���������� ��, ������� �������� ��� ����������� � �� ����� ������������� ������� ��������, ���� �� �� �������� �������. ��� ������� ���� ���� ���������� ���������� ���� ��� ������� ������."},
	{"Ice cold", "�������� ��� ���", "����� �� ��������� ��������, ����� ��� +�����, � �� + �����."},
	{"Merciless", "������������", "����� �� �������� ����, ������ +1 ����."},
	{"Vision of death", "������� ������", "����� �� ��������� � �����, ������ ��� +�������. �� 10+ ������ �����: ����, ��� ����, � ����, ��� �������. �� 7-9 ������ ������ : ���� ��� ���� ��� ����, ��� �������. �� �������� ��� �������, ���� ��� ���� ������� - ������ ��������. ��� ������� �� ���������� ����������� ������ � � ���������� ��������� �1 � ������� ���� �����."},
	{"Perfect instincts", "����������� ���������", "����� �� ���������� ���������� �������� � ���������� � ������������ � �������� ��, ������ + 2, � �� + 1."},
	{"Impossible reflexes", "����������� ��������", "�������� �������, �� ��� ����� �������� ������. ���� �� ����� ��� ������ �����, ��� ����� 2, ���� �� ���� ������, �� �� �����, ��� ����� 1. ���� �� ������ ��������� �����, ��������� �� ����������."},
	//
	{"Battle hardened", "���������� � ����", "����� �� ���������� ��� �����, ����� ��� +������, � �� +�����."},
	{"Fuck this shit", "�� ����� ��� ��� �����", "�����, ��� ������ ������� � ������ ��� +������. �� 10+ �������, �� ������. �� 7-9 ������ ���� ��� ��������, �� ��� ����� ���� ����-�� ������: ������ ���-�� ������ ��� ������ � �����. ��� ������� �� ������� �� ������� � ��� ������."},
	{"Battlefield instincts", "������ ���������", "����� �� ���������� ���� ����� �������� �����, ������ ��� +������, � �� +�������, �� ������ � �����."},
	{"Insano like drano", "����� �� �����", "�� ��������� +1 ������ (������ +3)."},
	{"Prepared for the inevitable", "����� � �����������", "� ���� ���� ���������������� ������������ �������. ��� ��������� ���������� ������ � ������� 2."},
	{"Bloodcrazed", "�����������", "����� �� �������� ����, ������ +1 ����."},
	{"Not to be fuck with!", "��������� ����!", "� ����� �� ���������� ������ (���� 3 ����� �����) � ����� �� ���������������."},
};
assert_enum(move, NotToBeFuckWith);
getstr_enum(move);

static void addstats(int index, char* stats) {
	char temp[260]; temp[0] = 0;
	for(auto e = Cool; e <= Weird; e = (stat_s)(e + 1)) {
		if(temp[0])
			zcat(temp, ", ");
		szprints(zend(temp), zendof(temp), "%1%+2i", getstr(e), stats[e]);
	}
	logs::add(index, temp);
}

void hero::choosestats(bool interactive) {
	for(int i = 0; i < 4; i++)
		addstats(i, booklet_data[type].stats[i]);
	int i = logs::input(interactive, true, "���e���� ���� ��������������:");
	memcpy(stats, booklet_data[type].stats[i], sizeof(stats));
}

void hero::choosetype(bool interactive) {
	for(auto e = TheAngel; e <= TheGunlugger; e = (booklet_s)(e + 1))
		logs::add(e, getstr(e));
	set((booklet_s)logs::input(interactive, true, "��� �� ������ ������?"));
}

void hero::choosemoves(bool interactive, booklet_s type, int count) {
	for(int i = 0; i < count; i++) {
		for(auto e : booklet_data[type].moves) {
			if(is(e))
				continue;
			if(move_data[e].descritpion)
				logs::add(e, "[%1]: %2", getstr(e), move_data[e].descritpion);
			else
				logs::add(e, getstr(e));
		}
		set((move_s)logs::input(interactive, true, "�������� ����� ���� (%1i/%2i):", i + 1, count));
	}
}

static void chooseitem(bool interactive, const char* title, item_s* result, const item_s* elements, int choose_count) {
	result[0] = NoItem;
	for(int j = 0; j < choose_count; j++) {
		for(int i = 0; elements[i] != NoItem; i++) {
			if(zchr(result, elements[i]))
				continue;
			char temp[128];
			item it(elements[i]);
			logs::add(elements[i], it.getname(temp, true));
		}
		result[j] = (item_s)logs::input(interactive, true, title, j + 1, choose_count);
		result[j + 1] = NoItem;
	}
}

static void chooseitem(bool interactive, const char* title, const item_s* elements, item& i1) {
	item_s result[2];
	chooseitem(interactive, title, result, elements, 1);
	i1 = result[0];
}

static void chooseitem(bool interactive, const char* title, const item_s* elements, item& i1, item& i2) {
	item_s result[3];
	chooseitem(interactive, title, result, elements, 2);
	i1 = result[0];
	i2 = result[1];
}

static void upgradeitem(bool interactive, item& e, upgrade_s* elements, int count, int upgrade_count) {
	for(int j = 0; j < upgrade_count; j++) {
		for(int i = 0; i < count; i++) {
			if(e.is(elements[i]))
				continue;
			logs::add(elements[i], getstr(elements[i]));
		}
		e.set((upgrade_s)logs::input(interactive, true, "�������� ��������� (%1i/%2i):", j + 1, upgrade_count));
	}
}

void hero::choosegear(bool interactive) {
	static item_s fuckoff_big_guns[] = {SniperRifle, MachineGun, AssaultRifle, GrenadeLauncher, NoItem};
	static item_s serious_guns[] = {Rifle, Shotgun, SMG, Magnum, NoItem};
	static item_s buckup_weapons[] = {Pistol, Knife, Machete, ManyKnives, Grenades, NoItem};
	static item_s custom_firearms[] = {Pistol, Shotgun, Rifle, /*Crossbow, */NoItem};
	static item_s hand_weapons[] = {Staff, Knife, Chain, NoItem};
	static item_s small_practic_weapons[] = {Revolver, Pistol, Knife, SawedOff, NoItem};
	static upgrade_s firearms_upgrade[] = {Scoped, Big, HiPower, Semiautomatic, Silenced, Valuable};
	static upgrade_s hand_weapons_upgrade[] = {Blade, Spikes, Big, Valuable};
	switch(type) {
	case TheGunlugger:
		chooseitem(interactive, "�������� ������������� �����:", fuckoff_big_guns, weapons[0]);
		chooseitem(interactive, "�������� ��������� ����� (%1i/%2i):", serious_guns, weapons[1], weapons[2]);
		chooseitem(interactive, "�������� �������� ������:", buckup_weapons, weapons[3]);
		break;
	case TheBattleBaby:
		chooseitem(interactive, "�������� ���������� ������:", custom_firearms, weapons[0]);
		upgradeitem(interactive, weapons[0], firearms_upgrade, sizeof(firearms_upgrade) / sizeof(firearms_upgrade[0]), 2);
		chooseitem(interactive, "�������� �������� ������:", hand_weapons, weapons[1]);
		upgradeitem(interactive, weapons[1], hand_weapons_upgrade, sizeof(hand_weapons_upgrade) / sizeof(hand_weapons_upgrade[0]), 2);
		break;
	default:
		chooseitem(interactive, "�������� ���������� ������:", small_practic_weapons, weapons[0]);
		break;
	}
	for(auto& e : weapons)
		add(e);
}

hero& hero::choose(bool interactive) {
	for(auto& e : players)
		logs::add((int)&e, e.getname());
	return *((hero*)logs::input(interactive, false, "��� ��� ����� ������?"));
}

hero& hero::chooseally(bool interactive, bool clear_text) {
	for(int j = 0; j < max_players; j++) {
		if(this == &players[j])
			continue;
		logs::add(j, players[j].getname());
	}
	return players[logs::input(interactive, clear_text)];
}

static void questions(hero& player, bool interactive, question* elements, char others) {
	char history[max_players] = {0};
	for(int i = 0; elements[i].text; i++) {
		logs::add(elements[i].text, player.getname());
		for(int j = 0; j < max_players; j++) {
			if(history[j])
				continue;
			if(&player == &players[j])
				continue;
			logs::add(j, players[j].getname());
		}
		logs::add(1000, "����� �� ���.");
		int id = logs::input(interactive);
		if(id == 1000)
			continue;
		history[id] = elements[i].value;
	}
	for(int i = 0; i < max_players; i++) {
		if(!history[i])
			history[i] = others;
	}
	for(int i = 0; i < max_players; i++)
		players[i].sethistory(player, history[i]);
}

void hero::choosehistory(bool interactive, int stage) {
	static question angel[] = {
		{"[%1], � ������� ���� �� ��� �������� ����, ����� ��� ���� �����, � ����� ����, ������ ����-�� �����. ��� ��� ���?", 2},
		{"[%1], ���� �� ���, �� ���� ������, ������� �� ��������������. ��� ���?", -1},
		{"[%1], ���� �� ��� ��� � ����� � ����� ���, ��� ����� ��. ��� ���?", 2},
		{0}
	};
	static question gunslugger[] = {
		{"[%1], � �������, ���� �� ��� �������� � ����� ������ � �����. ��� ��� ���?", 2},
		{"[%1], � �������, ���� �� ��� ���-�� ������ ���� �������. ��� ���?", -2},
		{"[%1], ���� �� ��� ����� ��������, �� ���� ������. ��� ���?", 2},
		{0}
	};
	int index = getindex();
	if(stage == 1) {
		switch(type) {
		case TheAngel:
			questions(*this, interactive, angel, 1);
			break;
		case TheBattleBaby:
			logs::add("[%1], �� ������ ����������� ���� �� �����. ������� ��� ������� ���� �����.", getname());
			for(int i = 0; i < max_players; i++)
				players[i].history[index] = 1;
			logs::next(interactive);
			break;
		case TheGunlugger:
			questions(*this, interactive, gunslugger, 1);
			break;
        default:
            break;
		}
	} else {
		switch(type) {
		case TheAngel:
			logs::add("[%1], �� ���������� �� ������� ������������� � �����. �����, ���� ��� ������ ��� ����� ���������. �� ������ ������������ ���������, ��������� �������. ��� �������.", getname());
			for(int i = 0; i < max_players; i++)
				players[i].history[index] -= 1;
			logs::next(interactive);
			break;
		case TheBattleBaby:
			logs::add("[%1], ������ �� ��� �� �� ���������. ��� ���?", getname());
			history[chooseally(interactive, true).getindex()] = 3;
			break;
		case TheGunlugger:
			logs::add("[%1], ������ �� ��� �� �������� ����� �����. ��� ���?", getname());
			history[chooseally(interactive, true).getindex()] += 1;
			break;
        default:
            break;
		}
	}
}

void hero::create(bool interactive) {
	choosetype(interactive);
	if(type == TheBattleBaby)
		setgender(Female);
	else
		choosegender(interactive);
	choosestats(interactive);
	choosemoves(interactive, type, booklet_data[type].choose_moves);
	choosegear(interactive);
	choosename(interactive);
}

void hero::createparty(bool interactive) {
	for(int i = 0; i < max_players; i++)
		players[i].create(interactive);
	for(int i = 0; i < max_players; i++)
		players[i].choosehistory(interactive, 1);
	for(int i = 0; i < max_players; i++)
		players[i].choosehistory(interactive, 2);
}

void hero::set(booklet_s value) {
	type = value;
}
