#include "answer.h"

#pragma once

enum gender_s : unsigned char {
	NoGender, Male, Female
};

namespace logs {
struct driver : stringbuilder {
	gender_s			gender, opponent_gender;
	const char*			name;
	const char*			opponent_name;
	int					count, opponent_count;
	const char*			weapon;
	constexpr driver(const stringbuilder& sb) : stringbuilder(sb),
		gender(), opponent_gender(),
		name(), opponent_name(),
		count(1), opponent_count(1),
		weapon() {}
	void				addidentifier(const char* identifier) override;
};
extern answeri			an;
void					open(const char* title, bool resize = false);
void					next(bool clear_text = true);
extern stringbuilder	sb;
void					setdark();
void					setlight();
bool					yesno(bool interactive = true);
}