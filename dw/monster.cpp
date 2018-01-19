#include "main.h"
#include "grammar.h"

static mastermove kobold_moves[] = {
	{"%герой оступил%ась и угодил%а в хорошо замаскированный медвежий капкан.", Damage, {2, 4}, 0, {"Капкан клацнул, так и не словив %героя - в последний момент %она отпрыгнула в сторону.", Dexterity}},
	{"Внезапно, неожиданно для всех оставшиеся кобольды отступили и скрылись из виду. Скорее всего они замышляют что-то недоброе."},
	{"Мерзкий ящерообразный кобольд подудел в дудочку и за ним показался Человеко-Ящер.", Summon, {1}},
};
static mastermove goblin_moves[] = {
	{"\n- Здесь еда!!! Все сюда!! - заорал один гоблин, скаля мерзкую улыбку.\nИз темного прохода выскочили еще [%1i] гоблинов.", Summon, {1, 2, 1}, Goblin},
	{"\n- Шааааррржж!! - заорали гоблины и навалились всей кучей на ничего не ожидающего %героя.", Damage, {1, 10, 1}, 0},
	{"\n- Отсупаем!!! Все назад, схватим их позже с большими Бу!! - заорали гоблины и скрылись из виду.\n- Большой Бу?? - машинально переспросил %герой."},
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
	unsigned char			damage[2];
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
	{"goblin", "гоблин", Horde, Small, {Intellegent, Organized}, 1, "копье", {6}, 3, {Close, Reach}, AREF(goblin_moves)},
	{"kobold", "кобольд", Horde, Small, {Stealthy, Intellegent, Organized}, 1, "копье", {6}, 3, {Close, Reach}, AREF(kobold_moves)},
	{"bandit", "бандит", Horde, Small, {Intellegent, Organized}, 1, "кортик", {6}, 3, {Close}, AREF(bandit_moves)},
};
assert_enum(monster, Bandit);

template<> const char* getstr<monster_s>(monster_s value) {
	return monster_data[value].name;
}

monster::monster() : type(Bandit), count(0), hp(0) {
}

monster::monster(monster_s type) {
	set(type);
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
	dice result;
	result.c = 1;
	result.d = monster_data[type].damage[0];
	result.m = 0;
	return result;
}

void monster::set(monster_s value) {
	type = value;
	switch(monster_data[type].organization) {
	case Horde: count = xrand(7, 10); break;
	case Group: count = xrand(3, 6); break;
	default: count = 1; break;
	}
	distance = Far;
	hp = getmaxhits();
}

const char* monster::getname() const {
	return monster_data[type].name;
}

const char* monster::getLA() const {
	return "";
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

aref<mastermove> monster::getmoves() const {
	return monster_data[type].moves;
}

void monster::getloot(loot_i& loot) const {
	auto hoard = getdamage().roll();
	if(hoard < 1)
		hoard = 1;
	switch(hoard) {
	case 1: loot.coins += dice::roll(2, 8); break;
	case 2: loot.add(AdventuringGear); break;
	case 3: loot.coins += dice::roll(4, 10); break;
	case 4: loot.add((item_s)xrand(Bloodstone, Onyx)); break;
	case 5: loot.add(HealingPotion); break;
	case 6: loot.add(Map); break;
	case 7: loot.coins += dice::roll(1, 4) * 100; break;
	case 8: loot.add((item_s)xrand(Alexandrite, Topaz)); break;
	case 9: loot.coins += dice::roll(2, 4) * 100; break;
	case 10:
		// A magical item or magical effect
		break;
	case 11: loot.coins += dice::roll(2, 4) * 100; break;
	case 12: loot.coins += dice::roll(3, 4) * 100; break;
	case 13: loot.coins += dice::roll(4, 4) * 100; break;
	case 14: loot.coins += dice::roll(5, 4) * 100; break;
	case 15:
		break;
	case 16:
		break;
	case 17:
		break;
	default:
		loot.coins += dice::roll(1, 10) * 1000;
		for(int i = xrand(1, 6); i > 0; i--)
			loot.add((item_s)xrand(Alexandrite, Topaz));
		break;
	}
}