#include "main.h"

extern scene* current_scene;

const char* logs::getpanel(int index) {
	return "";
}

int logs::getwidth(int index) {
	return 0;
}

static char* get_player(char* result, const char* result_maximum, int value) {
	if(!current_scene)
		return result;
	current_scene->player.getname(result, result_maximum);
	return result;
}

static char* get_enemy(char* result, int value) {
	if(!current_scene)
		return result;
	auto p = current_scene->enemy.getname();
	if(!p)
		return result;
	zcpy(result, p);
	return result;
}

static char* add(char* result, const char* result_maximum, assets& e) {
	if(!e)
		return result;
	auto p = e.getname();
	if(p) {
		if(e.iscrew()) {
			zcpy(result, "С вами ");
			e.getname(zend(result), result_maximum);
		} else
			szprints(result, result_maximum, "У вас есть %1", p);
		zcat(result, "\n");
	}
	return zend(result);
}

static char* add(char* result, const char* result_maximum, kit_s e) {
	if(!e)
		return result;
	auto p = getstr(e);
	if(p) {
		zcpy(result, "Имеются ");
		auto z = zend(result);
		zcat(z, p);
		zcat(z, "\n");
		szlower(z);
	}
	return zend(result);
}

static char* get_assets(char* result, const char* result_maximum, int value) {
	if(!current_scene)
		return result;
	auto p = result;
	p = add(p, result_maximum, current_scene->player.weapon);
	p = add(p, result_maximum, current_scene->player.attire);
	p = add(p, result_maximum, current_scene->player.crew);
	for(auto e = BroadcastKit; e <= WildernessKit; e = (kit_s)(e + 1)) {
		if(current_scene->player.is(e))
			p = add(p, result_maximum, e);
	}
	return result;
}

static char* get_wounds(char* result, int value) {
	if(!current_scene)
		return result;
	if(current_scene->player.is(Fatal))
		zcat(result, "Вы разорваны на куски.");
	else {
		for(auto value = Minor; value < Fatal; value = (severity_s)(value + 1)) {
			if(!current_scene->player.is(value))
				continue;
			if(result[0] == 0)
				zcpy(result, "У вас ");
			else
				zcat(result, ", ");
			switch(value) {
			case Minor: zcat(result, "на теле синяк"); break;
			case Major: zcat(result, "рана"); break;
			case Severe: zcat(result, "дырка в теле"); break;
			case Critical: zcat(result, "оторвана нога"); break;
			}
		}
		if(result[0])
			zcat(result, ".");
	}
	return result;
}