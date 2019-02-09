#include "logs.h"

#pragma once

enum gender_s : unsigned char {
	NoGender, Male, Female
};

namespace logs {
struct driver : stringbuilder {
	gender_s		gender, opponent_gender;
	const char*		name;
	const char*		opponent_name;
	int				count, opponent_count;
	const char*		weapon;
	constexpr driver(char* result, const char* result_maximum) : stringbuilder(result, result_maximum),
		gender(), opponent_gender(),
		name(), opponent_name(),
		count(1), opponent_count(1),
		weapon() {}
	void			addidentifier(const char* identifier) override;
};
}