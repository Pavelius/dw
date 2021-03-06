#include "main.h"

struct question {
	const char*			text;
	int					value;
};
bookleti bsmeta<bookleti>::elements[] = {
	{},
	{"angel", "�����",
	{{1, 0, 1, 2, -1}, {1, 1, 2, 0, -1}, {-1, 1, 0, 2, 1}, {2, 0, -1, 2, -1}}, 2,
	{SixthSense, Infirmary, ProfessionalCompassion, BattlefieldGrace, HealingTouch, TouchedByDeath},
	},
	{"battlebaby", "��������",
	{{3, -1, 1, 1, 0}, {3, -1, 2, 0, -1}, {3, -2, 1, 1, 1}, {3, 0, 1, 1, -1}}, 2,
	{DangerousAndSexy, IceCold, Merciless, VisionOfDeath, PerfectInstincts, ImpossibleReflexes},
	},
	{"gunlugger", "�������",
	{{1, 2, -1, 1, 0}, {-1, 2, -2, 1, 2}, {1, 2, -2, 2, -1}, {2, 2, -2, 0, 0}}, 3,
	{BattleHardened, FuckThisShit, BattlefieldInstincts, InsanoLikeDrano, PreparedForTheInevitable, Bloodcrazed, NotToBeFuckWith},
	}
};
assert_enum(booklet, TheGunlugger);

static void addstats(int index, char* stats) {
	char temp[260]; stringbuilder sbn(temp);
	for(auto e = Cool; e <= Weird; e = (stat_s)(e + 1)) {
		if(sbn)
			sbn.add(", ");
		sbn.add("%+1%+2i", getstr(e), stats[e]);
	}
	an.add(index, temp);
}

void hero::choosestats(bool interactive) {
	for(int i = 0; i < 4; i++)
		addstats(i, bsmeta<bookleti>::elements[type].stats[i]);
	int i = an.choose(interactive, true, "���e���� ���� ��������������:");
	memcpy(stats, bsmeta<bookleti>::elements[type].stats[i], sizeof(stats));
}

void hero::choosetype(bool interactive) {
	for(auto e = TheAngel; e <= TheGunlugger; e = (booklet_s)(e + 1)) {
		if(is(e))
			continue;
		an.add(e, getstr(e));
	}
	auto v = (booklet_s)an.choose(interactive, true, "��� �� ������ ������?");
	type = Booklet;
	subtype = v;
}

void hero::choosemoves(bool interactive, booklet_s type, int count) {
	for(int i = 0; i < count; i++) {
		for(auto e : bsmeta<bookleti>::elements[type].moves) {
			if(is(e))
				continue;
			if(bsmeta<movei>::elements[e].descritpion)
				an.add(e, "[%1]: %2", getstr(e), bsmeta<movei>::elements[e].descritpion);
			else
				an.add(e, getstr(e));
		}
		set((move_s)an.choose(interactive, true, "�������� ����� ���� (%1i/%2i):", i + 1, count));
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
			an.add(elements[i], it.getname(temp, true));
		}
		result[j] = (item_s)an.choose(interactive, true, title, j + 1, choose_count);
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
			an.add(elements[i], getstr(elements[i]));
		}
		e.set((upgrade_s)an.choose(interactive, true, "�������� ��������� (%1i/%2i):", j + 1, upgrade_count));
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
	for(auto& e : bsmeta<hero>())
		an.add((int)&e, e.getname());
	return *((hero*)an.choose(interactive, false, "��� ��� ����� ������?"));
}

hero& hero::chooseally(bool interactive, bool clear_text) {
	for(auto& e : bsmeta<hero>()) {
		if(this == &e)
			continue;
		an.add((int)&e, e.getname());
	}
	return *((hero*)an.choose(interactive, false, 0));
}

static void questions(hero& player, bool interactive, question* elements, char others) {
	char history[max_players] = {0};
	for(int i = 0; elements[i].text; i++) {
		sb.add(elements[i].text, player.getname());
		for(int j = 0; j < max_players; j++) {
			if(history[j])
				continue;
			if(&player == &bsmeta<hero>::elements[j])
				continue;
			an.add(j, bsmeta<hero>::elements[j].getname());
		}
		an.add(1000, "����� �� ���.");
		int id = an.choose(interactive, true, 0);
		if(id == 1000)
			continue;
		history[id] = elements[i].value;
	}
	for(int i = 0; i < max_players; i++) {
		if(!history[i])
			history[i] = others;
	}
	for(int i = 0; i < max_players; i++)
		bsmeta<hero>::elements[i].sethistory(player, history[i]);
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
			if(interactive)
				sb.add("[%1], �� ������ ����������� ���� �� �����. ������� ��� ������� ���� �����.", getname());
			for(int i = 0; i < max_players; i++)
				bsmeta<hero>::elements[i].history[index] = 1;
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
			if(interactive)
				sb.add("[%1], �� ���������� �� ������� ������������� � �����. �����, ���� ��� ������ ��� ����� ���������. �� ������ ������������ ���������, ��������� �������. ��� �������.", getname());
			for(int i = 0; i < max_players; i++)
				bsmeta<hero>::elements[i].history[index] -= 1;
			next(interactive);
			break;
		case TheBattleBaby:
			if(interactive)
				sb.add("[%1], ������ �� ��� �� �� ���������. ��� ���?", getname());
			history[chooseally(interactive, true).getindex()] = 3;
			break;
		case TheGunlugger:
			if(interactive)
				sb.add("[%1], ������ �� ��� �� �������� ����� �����. ��� ���?", getname());
			history[chooseally(interactive, true).getindex()] += 1;
			break;
        default:
            break;
		}
	}
}

void hero::create(bool interactive) {
	gender_s gender;
	choosetype(interactive);
	if(subtype == TheBattleBaby)
		gender = Female;
	else
		gender = choosegender(interactive);
	choosestats(interactive);
	choosemoves(interactive, booklet_s(subtype), bsmeta<bookleti>::elements[subtype].choose_moves);
	choosegear(interactive);
	setname(choosename(interactive, booklet_s(subtype), gender));
}

void hero::createparty(bool interactive) {
	for(int i = 0; i < max_players; i++) {
		auto p = bsmeta<hero>::add();
		p->create(interactive);
	}
	for(auto& e : bsmeta<hero>())
		e.choosehistory(interactive, 1);
	for(auto& e : bsmeta<hero>())
		e.choosehistory(interactive, 2);
}