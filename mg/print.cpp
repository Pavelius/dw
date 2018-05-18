#include "main.h"

logs::state logc;

logs::state::state() {
	memcpy(this, &logc, sizeof(*this));
}

logs::state::~state() {
	memcpy(&logc, this, sizeof(*this));
}

int logs::getwidth(int index) {
	return 0;
}

const char* logs::getpanel(int index) {
	return 0;
}