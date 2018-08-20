#include "main.h"

void actor::sufferharm(int value) {
	auto result = value - getarmor();
	if(result < 0) {
		act("%герой перенес%ла удар без последствий.");
		return;
	}
	act("%герой получил%а %1i урона.", result);
	sethp(gethp() - result);
}