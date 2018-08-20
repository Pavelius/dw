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
		const char*		opponent_name;
		gender_s		opponent_gender;
		int				opponent_count;
		constexpr driver() : gender(), name(), opponent_name(), opponent_gender(), opponent_count(1) {}
		void			msg(gender_s gender, char* result, const char* result_max, const char* text_male, const char* text_female);
		void			msg(gender_s gender, char* result, const char* result_max, const char* text_male, const char* text_female, const char* text_pluar);
		void			parseidentifier(char* result, const char* result_max, const char* identifier) override;
	};
}