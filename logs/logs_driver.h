#include "logs.h"
#include "grammar.h"

#pragma once

enum gender_s : unsigned char {
	NoGender, Male, Female
};

namespace logs {
	class driver : stringbuilder::driver {
		stringbuilder::driver* custom;
	public:
		gender_s		gender, opponent_gender;
		const char*		name, *opponent_name;
		int				count, opponent_count;
		driver();
		~driver();
		void			addidentifier(stringbuilder& sb, const char* identifier) override;
	};
}