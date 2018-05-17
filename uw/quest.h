#include "range.h"
#include "parameter.h"

#pragma once

namespace quest {
template<class T>
struct elements {
	T*					data;
	unsigned			count;
	const T*			begin() const { return data; }
	const T*			end() const { return data + count; }
};
struct method {
	const char*			id;
	int					value;
	param_types			apply() const;
};
struct jumper {
	const char*			id;
	const char*			text;
	const char*			condition;
	method				change;
};
struct scene {
	const char*			id;
	const char*			text;
	const char*			art;
	method				change;
	elements<jumper>	jumpers;
};
struct function {
	const char*			id;
	const char*			params[12];
	const char*			text;
};
struct row {
	int					params[12];
};
struct table {
	int					id;
	int					columns[12];
	elements<row>		rows;
};
void					clear();
const scene*			findscene(const char* id);
param_types				play(const char* id, const char** next_block);
};