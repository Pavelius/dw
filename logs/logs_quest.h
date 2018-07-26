#include "collection.h"

#pragma once

namespace logs {
struct conversation;
struct action {
	const char*				text;
	const char*				next;
};
struct conversation {
	const char*				id;
	const char*				text;
	aref<action>			action;
};
struct quest {
	enum result_s : unsigned char {
		Fail, Success, PartialSuccess,
	};
	adat<action, 1024>		actions;
	adat<conversation, 256>	conversations;
	//
	void					clear();
	const conversation*		find(const char* id) const;
	const conversation*		play(const conversation* p);
	bool					read(const char* url);
	result_s				run(const conversation* p);
};
}