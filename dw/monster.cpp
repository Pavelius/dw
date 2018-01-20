#include "main.h"
#include "grammar.h"

static mastermove kobold_moves[] = {
	{"%герой оступил%ась и угодил%а в хорошо замаскированный медвежий капкан.", Damage, {2, 6}, 0, {"Капкан клацнул, так и не словив %героя - в последний момент %она отпрыгнула в сторону.", Dexterity}},
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
static struct monsterinfo {
	const char*				id;
	const char*				name;
	organization_s			organization;
	size_s					size;
	monster_tag_s			tags[4];
	int						armor;
	const char*				weapon;
	dice					damage;
	char					hp;
	distance_s				distance[4];
	aref<mastermove>		moves;

	bool is(monster_tag_s id) const {
		for(auto e : tags) {
			if(e == id)
				return true;
		}
		return false;
	}

} monster_data[] = {
	{"goblin", "гоблин", Horde, Small, {Intellegent, Organized}, 1, "копье", {1, 6}, 3, {Close, Reach}, AREF(goblin_moves)},
	{"kobold", "кобольд", Horde, Small, {Stealthy, Intellegent, Organized}, 1, "копье", {1, 6}, 3, {Close, Reach}, AREF(kobold_moves)},
	{"bandit", "бандит", Horde, Small, {Intellegent, Organized}, 1, "кортик", {1, 6}, 3, {Close}, AREF(bandit_moves)},
};
assert_enum(monster, Bandit);
getstr_enum(monster);

struct regroupinfo {
	monster_s		type;
	unsigned char	count;
	operator bool() const { return count != 0; }
};
static adat<regroupinfo, 128> regroup_data;

static void correct_regroup() {
	while(regroup_data.count) {
		if(!regroup_data.data[regroup_data.count - 1])
			regroup_data.count--;
	}
}

static int add_regrouping(monster_s type) {
	for(auto& e : regroup_data) {
		if(e.type == type) {
			auto r = e.count;
			e.count = 0;
			correct_regroup();
			return r;
		}
	}
	return 0;
}

monster::monster(monster_s type) : effect() {
	set(type);
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
	case Horde: count = xrand(5, 10); break;
	case Group: count = xrand(3, 6); break;
	default: count = 1; break;
	}
	count += add_regrouping(type);
	distance = Far;
	hp = getmaxhits();
}

const char* monster::getname() const {
	return monster_data[type].name;
}

char* monster::getname(char* result) const {
	return grammar::get(result, monster_data[type].name, count);
}

bool monster::is(distance_s id) const {
	for(auto e : monster_data[type].distance) {
		if(e == id)
			return true;
	}
	return false;
}

void monster::regroup() {
	regroup_data.addz({type, (unsigned char)count});
}

aref<mastermove> monster::getmoves() const {
	return monster_data[type].moves;
}