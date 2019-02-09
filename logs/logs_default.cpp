#include "logs.h"

static char	text_buffer[256 * 4 * 8];
static stringbuilder text(text_buffer);

stringbuilder& logs::getbuilder() {
	return text;
}

const char* logs::getpanel(int index) {
	return 0;
}

int logs::getwidth(int index) {
	return 0;
}