#pragma once

struct range {
	int				from;
	int				to;
	const char*		text;
	const range*	find(int value) const;
	operator bool() const { return text != 0; }
};