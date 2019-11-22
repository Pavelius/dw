#include "logs.h"

answeri			logs::an;
static char		text_buffer[4096];
static char		text_buffer_right[4096];
stringbuilder	logs::sb(text_buffer);
logs::logp		logs::right_proc;

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