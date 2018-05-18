#include "main.h"

static const char* getdescription(item_s type) {
	switch(type) {
	case Potion: return "%����� �����%� �����.";
	case Scroll: return "%����� ������%� ������ � �������%� ��� ����������.";
	case Ring: return "%����� �����%�� ������ �� ����, � ����� ��������%� ���� ����� �����.";
	case Wand: return "%����� ��������%� ��������.";
	case Staff: return "%����� ��������%� ����� ����� �����.";
	case Rod: return "%����� ������%� ��������.";
	default: return "%����� �����������%� %1.";
	}
}

static void use_potion(bool interactive, character* player, item& e) {
	if(interactive) {
		if(player->isplayer())
			logs::add("��� ���� ������.");
	}
}

void character::use(bool interactive, item& e) {
	if(interactive)
		act(getdescription(e.type), getstr(e.type));
	switch(e.type) {
	case Potion: use_potion(interactive, this, e); break;
	default:
		if(interactive)
			logs::add("������ �� ���������.");
		break;
	}
}