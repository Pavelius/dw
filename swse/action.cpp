#include "main.h"

static bool character_sheet(action& a, creature* player, location& area, bool run, bool interactive) {
	if(!player->isplayer())
		return false;
	if(run) {
		player->act("##%����� - %������\n");
		logs::next();
	}
	return true;
}

static action standart_actions_data[] = {{NoAction, "���������� ������ ���������", character_sheet}
};
aref<action> standart_actions(standart_actions_data);