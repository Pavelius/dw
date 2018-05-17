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
	{"angel", "ангел",
	{{1, 0, 1, 2, -1}, {1, 1, 2, 0, -1}, {-1, 1, 0, 2, 1}, {2, 0, -1, 2, -1}}, 2,
	{{SixthSense, Infirmary, ProfessionalCompassion, BattlefieldGrace, HealingTouch, TouchedByDeath}, 6},
	},
	{"battlebaby", "чертовка",
	{{3, -1, 1, 1, 0}, {3, -1, 2, 0, -1}, {3, -2, 1, 1, 1}, {3, 0, 1, 1, -1}}, 2,
	{{DangerousAndSexy, IceCold, Merciless, VisionOfDeath, PerfectInstincts, ImpossibleReflexes}, 6},
	},
	{"gunlugger", "стрелок",
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
	{"Sixth sense", "Шестое чувство", "когда ты открываешь свой разум мировому вихрю, делай это +умно, вместо того чтобы делать это +странно."},
	{"Infirmary", "Лазарет", "ты получаешь лазарет, рабочее место с системой жизнеобеспечения, фармацевтической лабораторией и двумя сотрудниками. Доставь в него пациентов и можешь работать над ними, как технарь над техникой."},
	{"Professional compassion", "Профессиональное сострадание", "когда помогаешь кому-то, можешь, если хочешь, делай это +умно, вместо того чтобы делать это +история."},
	{"Battlefield grace", "Благодать на поле боя", "когда ты ухаживаешь за людьми, а не сражаешься, ты получаешь + 1 брони."},
	{"Healing touch", "Целительное касание", "возложи руки на раненого, открой ему свой разум и делай это +странно. На 10+ исцели 1 сегмент. На 7-9 исцели 1 сегмент, но ты действуешь под огнём, преодолевая сопротивление разума твоего пациента. При промахе: во-первых, ты его не исцелил. Во-вторых, ты открываешь свой и его разум мировому вихрю без защиты и без подготовки."},
	{"Touched by death", "Прикосновение смерти", "когда кто-то, о ком ты заботишься, умирает, ты получаешь + 1 к странно (макс. + 3)."},
	//
	{"Dangerous and sexy", "Опасная и сексуальная", "когда ты оказываешься в напряжённой ситуации, действуй +пылко. На 10+ получи 2 шанса. На 7-9 получи 1 шанс. Потрать шансы 1 к 1, чтобы установить зрительный контакт с присутствующим персонажем МЦ, который замирает или вздрагивает и не может предпринимать никаких действий, пока ты не прервешь контакт. При провале твой враг немедленно определяет тебя как главную угрозу."},
	{"Ice cold", "Холодная как лед", "когда ты угрожаешь насилием, делай это +круто, а не + жёстко."},
	{"Merciless", "Безжалостная", "когда ты наносишь урон, наноси +1 урон."},
	{"Vision of death", "Видения смерти", "когда ты вступаешь в битву, сделай это +странно. На 10+ назови двоих: того, кто умрёт, и того, кто выживет. На 7-9 назови одного : того кто умрёт или того, кто выживет. МЦ исполнит твоё видение, если это хоть сколько - нибудь возможно. При провале ты предвидишь собственную смерть и в результате получаешь –1 в течение всей битвы."},
	{"Perfect instincts", "Совершенные инстинкты", "когда ты оцениваешь напряжённую ситуацию и действуешь в соответствие с ответами МЦ, получи + 2, а не + 1."},
	{"Impossible reflexes", "Невероятные рефлексы", "двигаясь налегке, ты как будто защищена броней. Если ты почти или совсем голая, это броня 2, если на тебе одежда, но не броня, это броня 1. Если ты носишь настоящую броню, используй ее показатель."},
	//
	{"Battle hardened", "Закаленный в боях", "когда ты действуешь под огнем, делай это +жестко, а не +круто."},
	{"Fuck this shit", "Да пошло оно все нахер", "скажи, как хочешь сбежать и сделай это +жестко. На 10+ чудесно, ты свалил. На 7-9 можешь уйти или остаться, но это будет тебе чего-то стоить: оставь что-то позади или возьми с собой. При провале ты попался на полпути и был уязвим."},
	{"Battlefield instincts", "Боевые инстинкты", "когда ты открываешь свой разум мировому вихрю, сделай это +жестко, а не +странно, но только в битве."},
	{"Insano like drano", "Храбр до одури", "ты получаешь +1 жестко (жестко +3)."},
	{"Prepared for the inevitable", "Готов к неизбежному", "у тебя есть укомплектованная качественная аптечка. Она считается комплектом ангела с запасом 2."},
	{"Bloodcrazed", "Кровожадный", "когда ты наносишь урон, наноси +1 урон."},
	{"Not to be fuck with!", "Вешайтесь суки!", "в битве ты считаешься бандой (урон 3 банда малая) с бронёй по обстоятельствам."},
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
	int i = logs::input(interactive, true, "Выбeрите ваши характеристики:");
	memcpy(stats, booklet_data[type].stats[i], sizeof(stats));
}

void hero::choosetype(bool interactive) {
	for(auto e = TheAngel; e <= TheGunlugger; e = (booklet_s)(e + 1))
		logs::add(e, getstr(e));
	set((booklet_s)logs::input(interactive, true, "Кем вы будете играть?"));
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
		set((move_s)logs::input(interactive, true, "Выберите новые ходы (%1i/%2i):", i + 1, count));
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
		e.set((upgrade_s)logs::input(interactive, true, "Выберите улучшение (%1i/%2i):", j + 1, upgrade_count));
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
		chooseitem(interactive, "Выберите охренительную пушку:", fuckoff_big_guns, weapons[0]);
		chooseitem(interactive, "Выберите серьезную пушку (%1i/%2i):", serious_guns, weapons[1], weapons[2]);
		chooseitem(interactive, "Выберите запасное оружие:", buckup_weapons, weapons[3]);
		break;
	case TheBattleBaby:
		chooseitem(interactive, "Выберите стрелковое оружие:", custom_firearms, weapons[0]);
		upgradeitem(interactive, weapons[0], firearms_upgrade, sizeof(firearms_upgrade) / sizeof(firearms_upgrade[0]), 2);
		chooseitem(interactive, "Выберите холодное оружие:", hand_weapons, weapons[1]);
		upgradeitem(interactive, weapons[1], hand_weapons_upgrade, sizeof(hand_weapons_upgrade) / sizeof(hand_weapons_upgrade[0]), 2);
		break;
	default:
		chooseitem(interactive, "Выберите практичное оружие:", small_practic_weapons, weapons[0]);
		break;
	}
	for(auto& e : weapons)
		add(e);
}

hero& hero::choose(bool interactive) {
	for(auto& e : players)
		logs::add((int)&e, e.getname());
	return *((hero*)logs::input(interactive, false, "Кто это будет делать?"));
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
		logs::add(1000, "Никто из них.");
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
		{"[%1], в прошлом один из вас протянул руку, когда это было важно, и помог тебе, спасти кому-то жизнь. Кто это был?", 2},
		{"[%1], один из вас, на твой взгляд, обречен на саморазрушение. Кто это?", -1},
		{"[%1], один из вас был с тобой и видел все, что видел ты. Кто это?", 2},
		{0}
	};
	static question gunslugger[] = {
		{"[%1], в прошлом, один из них сражался с тобой плечом к плечу. Кто это был?", 2},
		{"[%1], в прошлом, один из них как-то бросил тебя умирать. Кто это?", -2},
		{"[%1], один из них самый красивый, на твой взгляд. Кто это?", 2},
		{0}
	};
	int index = getindex();
	if(stage == 1) {
		switch(type) {
		case TheAngel:
			questions(*this, interactive, angel, 1);
			break;
		case TheBattleBaby:
			logs::add("[%1], ты всегда выставляешь себя на показ. Поэтому все немного тебя знают.", getname());
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
			logs::add("[%1], ты стараешься не слишком превязываться к людям. Иначе, рано или поздно они могут погибнуть. Ты будешь испытываться депрессию, угрызения совести. Это никчему.", getname());
			for(int i = 0; i < max_players; i++)
				players[i].history[index] -= 1;
			logs::next(interactive);
			break;
		case TheBattleBaby:
			logs::add("[%1], одному из них ты не доверяешь. Кто это?", getname());
			history[chooseally(interactive, true).getindex()] = 3;
			break;
		case TheGunlugger:
			logs::add("[%1], одного из них ты считаешь самым умным. Кто это?", getname());
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
