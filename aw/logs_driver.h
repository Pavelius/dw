#include "logs/stringcreator.h"
#include "logs/grammar.h"

#pragma once

enum gender_s : unsigned char {
	Transgender, Male, Female
};

namespace logs {
	struct driver : stringcreator {
		gender_s		gender;
		const char*		name;
		const char*		opponent_name;
		gender_s		opponent_gender;
		constexpr driver() : gender(), name(), opponent_name(), opponent_gender() {}
		void			parseidentifier(char* result, const char* result_max, const char* identifier) override;
	};
}