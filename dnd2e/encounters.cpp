#include "main.h"

enum encounter_s : unsigned char {
	Attack, Hide, Retreat, Wait, Conversation
};

static void roll_party_surprise(int bonus) {
	for(auto player : party) {
		if(!player->isready())
			continue;
		player->surprise(bonus);
	}
}

void game::encounter() {
	// Create group of monsters
	auto type = ElfFolk;
	character monsters(type);
	monsters.setcount(xrand(2, 12));
	encounter(monsters);
}

void game::encounter(character& monsters) {
	char temp[260];
	// Test surprise
	monsters.surprise(getminimum(&character::getsurpriseother));
	roll_party_surprise(monsters.getsurpriseother());
	// Promt
	logs::add("��������, ������� �� �������� %1.", monsters.getname(temp, zendof(temp)));
	while(true) {
		//switch(reaction) {
		//case Hostile:
		//	logs::add("������ ������, %1 ��������� � �����.", monsters.getname(temp));
		//	logs::add(Attack, "������� ������ � ������������ � �����.");
		//	break;
		//case Threatening:
		//	monsters.say("- ����� ����� ������! - ����������%� %�����. - ����� ���� �����. ���������� ����� ��� ������!");
		//	askencounter();
		//	break;
		//case Flight:
		//	logs::add("������ ���� ������� ��� ��� ��������� ������.");
		//	askencounter();
		//	break;
		//case Cautions:
		//	logs::add("��� ���� �������� ��� � ������������ � ���������������. ����� ��� ��� �� �������� ���.");
		//	askencounter();
		//	break;
		//case Friendly:
		//	logs::add("��� �������� ��� � ���� ������� �� ����������� ���������.");
		//	askencounter();
		//	break;
		//default:
		//	logs::add("��� ���� �������� ��� � ������������ � ���������������.");
		//	askencounter();
		//	break;
		//}
		auto id = (encounter_s)logs::inputsg(true, true, "��� ������ ������?");
		switch(id) {
		case Attack:
			logs::add("������ ������ �� ��������� �� %1.", monsters.getname(temp, zendof(temp)));
			combat(true, monsters);
			break;
		}
		break;
	}
}