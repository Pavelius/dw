#include "main.h"

static void print_rolled(stringbuilder& sb, const char* title, const char* values, bool show_names = false) {
	auto start = sb.get();
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(values[i] == 0)
			continue;
		if(sb.ispos(start)) {
			sb.addn(title);
			sb.add(": ");
		} else
			sb.add(", ");
		if(show_names)
			sb.add("%1 %2i", getstr(i), values[i]);
		else
			sb.add("%1i", values[i]);
	}
	if(!sb.ispos(start))
		sb.add(".");
}

static void print_skills(stringbuilder& sb, const char* title, const creature* player) {
	auto start = sb.get();
	for(auto i = FirstSkill; i <= LastSkill; i = (feat_s)(i + 1)) {
		if(!player->is(i))
			continue;
		if(sb.ispos(start)) {
			sb.addn(title);
			sb.add(": ");
		} else
			sb.add(", ");
		sb.add(getstr(i));
	}
	if(!sb.ispos(start))
		sb.add(".");
}

static void print_feats(stringbuilder& sb, const char* title, const creature* player) {
	auto start = sb.get();
	for(auto i = FirstFeat; i <= LastFeat; i = (feat_s)(i + 1)) {
		if(i >= FirstSkill && i <= LastSkill)
			continue;
		if(!player->is(i))
			continue;
		if(sb.ispos(start)) {
			sb.addn(title);
			sb.add(": ");
		} else
			sb.add(", ");
		sb.add(getstr(i));
	}
	if(!sb.ispos(start))
		sb.add(".");
}

void creature::getstatistic(stringbuilder& sb) const {
	print_rolled(sb, "Атрибуты", abilities, true);
	print_skills(sb, "Навыки", this);
	print_feats(sb, "Особенности", this);
}

class_s creature::chooseclass(bool interactive) {
	for(auto i = Jedi; i <= Soldier; i = (class_s)(i + 1))
		an.add(i, getstr(i));
	an.sort();
	return (class_s)an.choose(interactive, false, "Выбрайте [класс]:");
}

specie_s creature::choosespecie(bool interactive) {
	for(auto i = Human; i <= Wookie; i = (specie_s)(i + 1))
		an.add(i, getstr(i));
	an.sort();
	return (specie_s)an.choose(interactive, false, "Выбрайте [расу]:");
}

gender_s creature::choosegender(bool interactive) {
	an.add(Male, "Мужчина");
	an.add(Female, "Женщина");
	return (gender_s)an.choose(interactive, false, "Выбрайте [пол]:");
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
			an.add(i, getstr(i));
		};
		an.sort();
		getstatistic(sb);
		sb.addn("Выбирайте [навык]");
		if(count > 1)
			sb.adds("(осталось [%1i])", count);
		auto result = (feat_s)an.choosev(interactive, false, true, 0);
		count--;
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
			an.add(source[i], getstr(source[i]));
		};
		an.sort();
		sb.addn("Выбирайте [особенность]");
		if(count > 1)
			sb.adds("(осталось [%1i])", count);
		auto result = (feat_s)an.choose(interactive, true, 0);
		count--;
		set(result);
	}
}

void creature::choosefeats(bool interactive, talent_s talent, int count) {
	feat_s source[LastFeat + 1];
	auto source_count = select(source, lenof(source), talent);
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
		print_rolled(sb, "Вы выбросили", temp, false);
		print_rolled(sb, "Вы распределили", abilities, true);
		for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
			if(abilities[i])
				continue;
			an.add(i, getstr(i));
		};
		auto result = (ability_s)an.choose(interactive, true, "Куда вы хотите поставить [%1i]?", temp[0]);
		abilities[result] = temp[0];
		memcpy(temp, temp + 1, 5); temp[5] = 0;
	}
}

void creature::chooseequip(bool interactive) {
	if(get(Jedi))
		add(LightSaber);
	else if(get(Soldier)) {
		add(Knife);
		add(BlasterRifle);
	}
	else {
		add(BlasterPistol);
	}
}

creature::creature(bool interactive, bool setplayer) :creature(choosespecie(interactive), choosegender(interactive), chooseclass(interactive), interactive, setplayer) {
}

creature::creature(specie_s specie, gender_s gender, class_s cls, bool interactive, bool setplayer) : gender(gender) {
	clear();
	chooseabilities(interactive);
	set(specie);
	set(cls);
	chooseskill(interactive, getskills());
	choosefeats(interactive, General, getfeats());
	if(getheroiclevel())
		hits = getdice(cls) * 3;
	this->name = getrandomname(specie, gender);
	chooseequip(interactive);
	if(setplayer)
		zcat(players, this);
}