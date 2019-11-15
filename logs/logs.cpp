#include "logs.h"

static char text_buffer[4096];
static char text_buffer_right[4096];
answeri logs::an;
stringbuilder logs::sb(text_buffer);
stringbuilder logs::sb_right(text_buffer_right);

void logs::next(bool interactive) {
	an.add(1, "Далее");
	an.choosev(interactive, true, false, 0);
}

bool logs::yesno(bool interactive) {
	if(!interactive)
		return true;
	an.add(1, "Да");
	an.add(2, "Нет");
	return an.choosev(interactive, true, false, 0) == 1;
}