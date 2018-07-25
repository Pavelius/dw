#include "collection.h"

#pragma once

namespace logs {
struct conversation;
struct action {
	const char*				text;
	const conversation*		next;
};
struct conversation {
	const char*				id;
	const char*				text;
	aref<action>			actions;
};
struct quest {
	enum result_s : unsigned char {
		Fail, Success, PartialSuccess,
	};
	adat<action, 1024>		actions;
	adat<conversation, 256>	conversations;
	//
	void					clear();
	bool					read(const char* url);
	result_s				run(const conversation* p);
	const conversation*		play(const conversation* p);
};
}