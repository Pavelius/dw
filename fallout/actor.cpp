#include "main.h"

static const char* text_count[] = {"урона", "урон", "урона"};

void actor::sufferharm(int value, bool ap) {
	auto result = value;
	if(!ap)
		result -= getarmor();
	if(result <= 0) {
		act("%герой перенес%ла удар без последствий.");
		return;
	}
	auto hp = gethp() - result;
	sethp(hp);
	act("%герой получил%а %1i %2", result, maptbl(text_count, result));
	if(hp <= 0)
		act("и упал%а");
	else if(hp <= gethpmax() / 2)
		act("и закричал%а от боли");
	act(".");
}