#include "main.h"

static mastermove kobold_moves[] = {
	{"%герой оступил%ась и угодил%а в хорошо замаскированный медвежий капкан.", Damage, {2, 6}, {"Капкан клацнул, так и не словив %героя - в последний момент %она отпрыгнула в сторону.", Dexterity}},
	{"Внезапно, оставшиеся кобольды отступили и скрылись из виду. Скорее всего они замышляют что-то недоброе.", Regroup},
	{"Мерзкий ящерообразный кобольд подудел в дудочку и из-за стоящего рядом камня выскочил еще один кобольд и присоединился к битве.", Summon, {1}},
};
static mastermove goblin_moves[] = {
	{"\n- Здесь еда!!! Все сюда!! - заорал один гоблин, скаля мерзкую улыбку.\nИз темного прохода выскочили еще двое голодных гоблинов.", Summon, {2}},
	{"\n- Шааааррржж!! - заорали гоблины и навалились всей кучей на ничего не ожидающего %героя.", Damage, {1, 10, 1}, 0},
	{"\n- Отсупаем!!! Все назад, схватим их позже с большими Бу!! - заорали гоблины и скрылись из виду.\n- Большой Бу?? - машинально переспросил %герой.", Regroup},
};
static mastermove bandit_moves[] = {
	{"Вместо того, чтобы нанести удар кортиком, бандит схватил %героя и выхватил у %нее мешочек с меребрянными монетами.", LooseMoney, {2, 6}},
};
static mastermove zombi_moves[] = {
	{"Внезапно один из зарубленных зомби снова ожил.", Summon, {1}},
	{"Зомби зажали %героя в углу и начали рвать на части.", Damage, {1, 10}},
};
monsteri bsmeta<monsteri>::elements[] = {
	{"Bandit", "бандит", Horde, Small, {Intellegent, Organized}, 1, "кортик", {1, 6}, 3, {Close}, bandit_moves},
	{"Goblin", "гоблин", Horde, Small, {Intellegent, Organized}, 1, "копье", {1, 6}, 3, {Close, Reach}, goblin_moves},
	{"Kobold", "кобольд", Horde, Small, {Stealthy, Intellegent, Organized}, 1, "копье", {1, 6}, 3, {Close, Reach}, kobold_moves},
	{"Zombie", "зомби", Horde, Small, {Undead}, 0, "рвать на части", {1, 6}, 11, {Close}, zombi_moves},
};
assert_enum(monster, LastMonster);

static char regrouping[LastMonster + 1];

static int add_regrouping(monster_s type) {
	auto r = regrouping[type];
	regrouping[type] = 0;
	return r;
}

monster::monster(monster_s type) : effect() {
	set(type);
}

bool monster::is(monster_tag_s id) const {
	for(auto e : bsmeta<monsteri>::elements[type].tags) {
		if(e == id)
			return true;
	}
	return false;
}

const char* monster::getweapon() const {
	return bsmeta<monsteri>::elements[type].name;
}

gender_s monster::getgender() const {
	return Male;
}

int monster::getmaxhits() const {
	return bsmeta<monsteri>::elements[type].hp;
}

int	monster::getarmor() const {
	return bsmeta<monsteri>::elements[type].armor;
}

int	monster::getharm() const {
	int result = 0;
	int maximum = imin(count, (char)3);
	for(int i = 0; i < maximum; i++)
		result = imax(result, getdamage().roll());
	return result;
}

dice monster::getdamage() const {
	return bsmeta<monsteri>::elements[type].damage;
}

void monster::set(monster_s value) {
	type = value;
	switch(bsmeta<monsteri>::elements[type].organization) {
	case Horde: count = xrand(3, 7); break;
	case Group: count = xrand(2, 3); break;
	default: count = 1; break;
	}
	count += add_regrouping(type);
	distance = Far;
	hp = getmaxhits();
}

const char* monster::getname() const {
	return bsmeta<monsteri>::elements[type].name;
}

const char* monster::getname(const stringbuilder& sb) const {
	stringbuilder sbn = sb;
	sbn.get(bsmeta<monsteri>::elements[type].name, count);
	return sb;
}

bool monster::is(distance_s id) const {
	for(auto e : bsmeta<monsteri>::elements[type].distance) {
		if(e == id)
			return true;
	}
	return false;
}

void monster::regroup() {
	regrouping[type] = count + count / 2;
}

aref<mastermove> monster::getmoves() const {
	return bsmeta<monsteri>::elements[type].moves;
}

void monster::act(const char* format, ...) const {
	driver dr(sb);
	dr.name = getstr(type);
	dr.gender = Male;
	dr.addv(format, xva_start(format));
	sb = dr;
}