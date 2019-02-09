#include "logs.h"

static char	text_buffer[256 * 4 * 8];
static logs::driver text(text_buffer, text_buffer + sizeof(text_buffer)/sizeof(text_buffer[0]) - 1);

logs::driver& logs::getbuilder() {
	return text;
}

const char* logs::getpanel(int index) {
	return 0;
}

int logs::getwidth(int index) {
	return 0;
}