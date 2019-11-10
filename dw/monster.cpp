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
static struct monster_info {
	const char*		id;
	const char*		name;
	organization_s	organization;
	size_s			size;
	monster_tag_s	tags[4];
	int				armor;
	const char*		weapon;
	dice			damage;
	char			hp;
	distance_s		distance[4];
	aref<mastermove> moves;
} monster_data[] = {
	{"Bandit", "бандит", Horde, Small, {Intellegent, Organized}, 1, "кортик", {1, 6}, 3, {Close}, bandit_moves},
	{"Goblin", "гоблин", Horde, Small, {Intellegent, Organized}, 1, "копье", {1, 6}, 3, {Close, Reach}, goblin_moves},
	{"Kobold", "кобольд", Horde, Small, {Stealthy, Intellegent, Organized}, 1, "копье", {1, 6}, 3, {Close, Reach}, kobold_moves},
	{"Zombie", "зомби", Horde, Small, {Undead}, 0, "рвать на части", {1, 6}, 11, {Close}, zombi_moves},
};
assert_enum(monster, LastMonster);
getstr_enum(monster);

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
	for(auto e : monster_data[type].tags) {
		if(e == id)
			return true;
	}
	return false;
}

const char* monster::getweapon() const {
	return monster_data[type].name;
}

gender_s monster::getgender() const {
	return Male;
}

int monster::getmaxhits() const {
	return monster_data[type].hp;
}

int	monster::getarmor() const {
	return monster_data[type].armor;
}

int	monster::getharm() const {
	int result = 0;
	int maximum = imin(count, (char)3);
	for(int i = 0; i < maximum; i++)
		result = imax(result, getdamage().roll());
	return result;
}

dice monster::getdamage() const {
	return monster_data[type].damage;
}

void monster::set(monster_s value) {
	type = value;
	switch(monster_data[type].organization) {
	case Horde: count = xrand(3, 7); break;
	case Group: count = xrand(2, 3); break;
	default: count = 1; break;
	}
	count += add_regrouping(type);
	distance = Far;
	hp = getmaxhits();
}

const char* monster::getname() const {
	return monster_data[type].name;
}

char* monster::getname(char* result, const char* result_maximum) const {
	//return grammar::get(result, result_maximum, monster_data[type].name, count);
	return result;
}

bool monster::is(distance_s id) const {
	for(auto e : monster_data[type].distance) {
		if(e == id)
			return true;
	}
	return false;
}

void monster::regroup() {
	regrouping[type] = count + count/2;
}

aref<mastermove> monster::getmoves() const {
	return monster_data[type].moves;
}

void monster::act(const char* format, ...) const {
	auto& driver = logs::getbuilder();
	driver.name = getstr(type);
	driver.gender = Male;
	logs::addv(format, xva_start(format));
}