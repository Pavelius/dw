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

void logs::driver::parseidentifier(char* result, const char* result_max, const char* identifier) {
	if(strcmp(identifier, "�����") == 0)
		zcpy(result, name);
	else if(strcmp(identifier, "�����") == 0)
		grammar::of(result, name);
	else if(strcmp(identifier, "��������") == 0)
		zcpy(result, opponent_name);
	else if(strcmp(identifier, "���������") == 0)
		grammar::of(result, opponent_name);
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "��", identifier, "���");
	else if(strcmp(identifier, "�") == 0)
		msg(gender, result, "", identifier, "�");
	else if(strcmp(identifier, "�") == 0)
		msg(opponent_gender, result, "", "�", "�");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, "", identifier, "��");
	else if(strcmp(identifier, "��") == 0)
		msg(opponent_gender, result, "", "��", "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "��", identifier, "���");
	else if(strcmp(identifier, "���") == 0)
		msg(opponent_gender, result, "��", "���", "���");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, "���", identifier, "��");
	else if(strcmp(identifier, "��") == 0)
		msg(opponent_gender, result, "���", "��", "��");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, "���", identifier, "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, "����", identifier, "���");
	else {
		zcat(result, "[-");
		zcat(result, identifier);
		zcat(result, "]");
	}
}

void hero::act(const char* format, ...) const {
	logs::driver driver;
	driver.name = getname();
	driver.gender = getgender();
	driver.opponent_name = 0;
	driver.opponent_gender = Male;
	logs::addv(driver, format, xva_start(format));
}

static void show_items(char* result, const char* result_maximum, deck& source, const char* title) {
	if(!source.count)
		return;
	szprints(result, result_maximum, "%1: ", title);
	result = zend(result);
	for(auto e : source) {
		if(result[0])
			zcat(result, ", ");
		szprints(zend(result), result_maximum, getstr(e));
	}
	zcat(result, ".\n");
}

static void show_items(char* result, const char* result_maximum, hero& player, const char* title, stat_s group) {
	deck items;
	player.select(items, group);
	show_items(result, result_maximum, items, title);
}

static void show_items(char* result, const char* result_maximum, hero& player, const char* title, stat_s g1, stat_s g2) {
	deck items;
	player.select(items, g1);
	player.select(items, g2);
	show_items(result, result_maximum, items, title);
}

PRINTPLG(investigator) {
	logs::driver driver; result[0] = 0;
	driver.name = player.getname();
	driver.gender = player.getgender();
	driver.print(zend(result), "###%�����\n");
	auto ps = zend(result);
	for(auto i = Speed; i <= Luck; i = stat_s(i + 1)) {
		if(ps[0]) {
			if(i==Will)
				zcat(ps, "\n:::");
			else
				zcat(ps, ", ");
		}
		driver.print(zend(ps), "%1 %2i", getstr(i), player.get(i));
	}
	zcat(ps, "\n");
	show_items(zend(ps), logs::getptrend(), player, getstr(Skill), Skill);
	show_items(zend(ps), logs::getptrend(), player, "��������", CommonItem, UniqueItem);
	ps = zend(result);
	szprints(ps, logs::getptrend(), "� ��� ����: %1i$, %2i ����.\n", player.get(Money), player.get(Clue));
	return result;
}