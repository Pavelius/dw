#include "main.h"

void actor::sufferharm(int count) {
	count -= getarmor();
	if(count <= 0) {
		//act("%����� �������%�� ���� ��� ����������.");
		return;
	} else
		act("%����� �������%� %1i �����", count);
	health -= count;
	switch(health) {
	case 5: case 4: break;
	case 3: if(d100() < 25) health = 0; break;
	case 2: if(d100() < 50) health = 0; break;
	case 1: if(d100() < 75) health = 0; break;
	default: health = 5; break;
	}
	if(!isalive())
		act(" � ������ %�� �����.");
	else if(iswounded())
		act(" � ������%� �� ����.");
	else
		logs::add(".");
}

bool actor::ishero() const {
	return this >= players && this <= (players + max_players);
}

int	actor::addbonus(state_s id) {
	if(is(id)) {
		remove(id);
		return 1;
	}
	return 0;
}