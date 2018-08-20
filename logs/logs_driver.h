#include "stringcreator.h"
#include "grammar.h"

#pragma once

enum gender_s : unsigned char {
	NoGender, Male, Female
};

namespace logs {
	struct driver : stringcreator {
		gender_s		gender;
		const char*		name;
		int				count;
		const char*		opponent_name;
		gender_s		opponent_gender;
		int				opponent_count;
		constexpr driver() : gender(), name(), count(1), opponent_name(), opponent_gender(), opponent_count(1) {}
		void			parseidentifier(char* result, const char* result_max, const char* identifier) override;
	};
}