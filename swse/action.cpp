#include "main.h"

static bool character_sheet(action& a, creature* player, location& area, bool run, bool interactive) {
	if(!player->isplayer())
		return false;
	if(run) {
		player->act("##%герой - %уровни\n");
		logs::next();
	}
	return true;
}

static action standart_actions_data[] = {{NoAction, "ѕосмотреть листок персонажа", character_sheet}
};
aref<action> standart_actions(standart_actions_data);