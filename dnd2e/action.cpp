#include "main.h"

struct action {
	tag						id;
	const char*				text;
	duration_s				duration;
	unsigned				experience;
	const char*				success_text;
	const char*				fail_text;
	void					(*success)(character* player);
	void					(*fail)(character* player);
	operator bool() const { return text != 0; }
};