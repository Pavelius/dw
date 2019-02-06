#include "main.h"

int logs::getwidth(int panel) {
	return 300;
}

const char* logs::getpanel(int panel) {
	return "%investigator";
}

static void msg(gender_s gender, char* result, const char* text_male, const char* text_female, const char* text_pluar) {
	if(gender == Female) {
		if(text_female)
			zcpy(result, text_female);
	} else {
		if(text_male)
			zcpy(result, text_male);
	}
}

void hero::act(const char* format, ...) const {
	logs::driver driver;
	driver.name = getname();
	driver.gender = getgender();
	driver.opponent_name = 0;
	driver.opponent_gender = Male;
	logs::addv(format, xva_start(format));
}

static void show_items(hero& player, char* result, const char* result_maximum, deck& source, const char* title) {
	if(!source.count)
		return;
	szprints(result, result_maximum, "%1: ", title);
	result = zend(result);
	for(auto e : source) {
		if(result[0])
			zcat(result, ", ");
		item::getname(zend(result), result_maximum, e, false, player.isexhause(e), player.getmark(e));
	}
	zcat(result, ".\n");
}

static void show_items(char* result, const char* result_maximum, hero& player, const char* title, stat_s group) {
	deck items;
	player.select(items, group);
	show_items(player, result, result_maximum, items, title);
}

static void show_items(char* result, const char* result_maximum, hero& player, const char* title, stat_s g1, stat_s g2) {
	deck items;
	player.select(items, g1);
	player.select(items, g2);
	show_items(player, result, result_maximum, items, title);
}

static void show_weapons(char* result, const char* result_maximum, hero& player, const char* title) {
	deck items;
	items.add(player.getwepon(0));
	items.add(player.getwepon(1));
	show_items(player, result, result_maximum, items, title);
}

//PRINTPLG(investigator) {
//	auto& player = game.players[0];
//	logs::driver driver;
//	driver.name = player.getname();
//	driver.gender = player.getgender();
//	driver.prints(result, result_maximum, "###%герой\n", 0);
//	auto ps = zend(result);
//	for(auto i = Speed; i <= Luck; i = stat_s(i + 1)) {
//		if(ps[0]) {
//			if(i==Will)
//				zcat(ps, "\n:::");
//			else
//				zcat(ps, ", ");
//		}
//		driver.prints(zend(ps), result_maximum, "%1 %2i", getstr(i), player.get(i));
//	}
//	zcat(ps, "\n");
//	show_items(zend(ps), result_maximum, player, getstr(Skill), Skill);
//	show_items(zend(ps), result_maximum, player, getstr(Spell), Spell);
//	show_items(zend(ps), result_maximum, player, "Предметы", CommonItem, UniqueItem);
//	show_items(zend(ps), result_maximum, player, getstr(Ally), Ally);
//	show_weapons(zend(ps), result_maximum, player, "Оружие");
//	szprints(zend(result), result_maximum, "У вас есть: %1i$, %2i улик.\n", player.get(Money), player.get(Clue));
//	szprints(zend(result), result_maximum, "Здоровье: %1i, Рассудок %2i.\n", player.get(Stamina), player.get(Sanity));
//	szprints(zend(result), result_maximum, "Движение: %1i.\n", player.get(Movement));
//	szprints(zend(result), result_maximum, "Трофеи монстров: %1i.\n", player.gettrophy());
//	return result;
//}