#include "main.h"

logs::state logc;

logs::state::state() : state(logc) {}

logs::state::~state() {
	logc = *this;
}