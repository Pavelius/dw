#include "main.h"

void actor::sufferharm(int value) {
	auto result = value - getarmor();
	if(result < 0) {
		act("%����� �������%�� ���� ��� �����������.");
		return;
	}
	act("%����� �������%� %1i �����.", result);
	sethp(gethp() - result);
}