#include "main.h"

static const char* text_count[] = {"�����", "����", "�����"};

void actor::sufferharm(int value, bool ap) {
	auto result = value;
	if(!ap)
		result -= getarmor();
	if(result <= 0) {
		act("%����� �������%�� ���� ��� �����������.");
		return;
	}
	auto hp = gethp() - result;
	sethp(hp);
	act("%����� �������%� %1i %2", result, maptbl(text_count, result));
	if(hp <= 0)
		act("� ����%�");
	else if(hp <= gethpmax() / 2)
		act("� ��������%� �� ����");
	act(".");
}