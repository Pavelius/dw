#include "main.h"

static char* print_rolled(char* result, const char* result_maximum, const char* title, const char* values, bool show_names = false) {
	auto p = result;
	auto pb = p;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(values[i] == 0)
			continue;
		if(p == result) {
			zcat(p, title);
			zcat(p, ": ");
			p = zend(p);
			pb = p;
		}
		if(pb != p) {
			zcat(p, ", ");
			p = zend(p);
		}
		if(show_names)
			szprints(p, result_maximum, "%1 %2i", getstr(i), values[i]);
		else
			sznum(p, values[i]);
		p = zend(result);
	}
	if(p != result)
		zcat(p, ".");
	return zend(p);
}

static char* print_skills(char* result, const char* result_maximum, const char* title, const creature* player) {
	auto p = result;
	auto pb = p;
	for(auto i = FirstSkill; i <= LastSkill; i = (feat_s)(i + 1)) {
		if(!player->is(i))
			continue;
		if(p == result) {
			zcat(p, title);
			zcat(p, ": ");
			p = zend(p);
			pb = p;
		}
		if(pb != p) {
			zcat(p, ", ");
			p = zend(p);
		}
		szprints(p, result_maximum, "%1", getstr(i));
		p = zend(result);
	}
	if(p != result)
		zcat(p, ".");
	return zend(p);
}

static char* print_feats(char* result, const char* result_maximum, const char* title, const creature* player) {
	auto p = result;
	auto pb = p;
	for(auto i = FirstFeat; i <= LastFeat; i = (feat_s)(i + 1)) {
		if(i >= FirstSkill && i <= LastSkill)
			continue;
		if(!player->is(i))
			continue;
		if(p == result) {
			zcat(p, title);
			zcat(p, ": ");
			p = zend(p);
			pb = p;
		}
		if(pb != p) {
			zcat(p, ", ");
			p = zend(p);
		}
		szprints(p, result_maximum, "%1", getstr(i));
		p = zend(result);
	}
	if(p != result)
		zcat(p, ".");
	return zend(p);
}

char* creature::getstatistic(char* result, const char* result_maximum) const {
	result[0] = 0;
	auto p = print_rolled(zend(result), result_maximum, "Атрибуты", abilities, true);
	if(p != result && zend(result)[-1] != '\n')
		zcat(p, "\n");
	p = print_skills(zend(result), result_maximum, "Навыки", this);
	if(p != result && zend(result)[-1] != '\n')
		zcat(p, "\n");
	p = print_feats(zend(result), result_maximum, "Особенности", this);
	return result;
}

class_s creature::chooseclass(bool interactive) {
	for(auto i = Jedi; i <= Soldier; i = (class_s)(i + 1))
		logs::add(i, getstr(i));
	logs::sort();
	return (class_s)logs::input(interactive, false, "Выбрайте [класс]:");
}

specie_s creature::choosespecie(bool interactive) {
	for(auto i = Human; i <= Wookie; i = (specie_s)(i + 1))
		logs::add(i, getstr(i));
	logs::sort();
	return (specie_s)logs::input(interactive, false, "Выбрайте [расу]:");
}

gender_s creature::choosegender(bool interactive) {
	logs::add(Male, "Мужчина");
	logs::add(Female, "Женщина");
	return (gender_s)logs::input(interactive, false, "Выбрайте [пол]:");
}

static int compare_result(const void* v1, const void* v2) {
	return *((char*)v2) - *((char*)v1);
}

void creature::chooseskill(bool interactive, int count) {
	while(count > 0) {
		for(auto i = FirstSkill; i <= LastSkill; i = (feat_s)(i + 1)) {
			if(is(i))
				continue;
			if(!isclass(i))
				continue;
			logs::add(i, getstr(i));
		};
		logs::sort();
		auto p = logs::getptr(); getstatistic(p, logs::getptrend());
		logs::add("\n");
		logs::add("Выбирайте [навык]");
		if(count > 1)
			logs::add("(осталось [%1i])", count);
		auto result = (feat_s)logs::input(interactive, false);
		count--; p[0] = 0;
		set(result);
	}
}

void creature::choosefeats(bool interactive, feat_s* source, unsigned source_count, int count) {
	while(count > 0) {
		for(unsigned i = 0; i < source_count; i++) {
			if(is(source[i]))
				continue;
			if(!isallow(source[i]))
				continue;
			logs::add(source[i], getstr(source[i]));
		};
		logs::sort();
		auto p = logs::getptr(); getstatistic(p, logs::getptrend());
		logs::add("\n");
		logs::add("Выбирайте [особенность]");
		if(count > 1)
			logs::add("(осталось [%1i])", count);
		auto result = (feat_s)logs::input(interactive, false);
		count--; p[0] = 0;
		set(result);
	}
}

void creature::choosefeats(bool interactive, talent_s talent, int count) {
	feat_s source[LastFeat + 1];
	auto source_count = select(source, lenghtof(source), talent);
	choosefeats(interactive, source, source_count, count);
}

static char roll_4d6() {
	char temp[4];
	for(auto& e : temp)
		e = (rand() % 6) + 1;
	qsort(temp, sizeof(temp) / sizeof(temp[0]), sizeof(temp[0]), compare_result);
	return temp[0] + temp[1] + temp[2];
}

void creature::chooseabilities(bool interactive) {
	char temp[6];
	memset(abilities, 0, sizeof(abilities));
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		temp[i] = roll_4d6();
	qsort(temp, sizeof(temp) / sizeof(temp[0]), sizeof(temp[0]), compare_result);
	while(temp[0]) {
		logs::add("\n"); print_rolled(logs::getptr(), logs::getptrend(), "Вы выбросили", temp, false);
		logs::add("\n"); print_rolled(logs::getptr(), logs::getptrend(), "Вы распределили", abilities, true);
		for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
			if(abilities[i])
				continue;
			logs::add(i, getstr(i));
		};
		auto result = (ability_s)logs::input(interactive, true, "Куда вы хотите поставить [%1i]?", temp[0]);
		abilities[result] = temp[0];
		memcpy(temp, temp + 1, 5); temp[5] = 0;
	}
}

creature* creature::create(bool interactive, bool setplayer) {
	auto p2 = choosespecie(interactive);
	auto p1 = choosegender(interactive);
	auto p3 = chooseclass(interactive);
	return create(p2, p1, p3,
		interactive,
		setplayer);
}

creature* creature::create(specie_s specie, gender_s gender, class_s cls, bool interactive, bool setplayer) {
	auto p = creatures.add();
	p->chooseabilities(interactive);
	p->gender = gender;
	p->set(specie);
	p->set(cls);
	p->chooseskill(interactive, p->getskills());
	p->choosefeats(interactive, General, p->getfeats());
	if(p->getheroiclevel())
		p->hits = game::getdice(cls) * 3;
	p->name = game::getrandomname(specie, gender);
	if(setplayer)
		zcat(players, p);
	return p;
}