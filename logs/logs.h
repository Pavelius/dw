#include "stringbuilder.h"

#pragma once

enum gender_s : unsigned char {
	NoGender, Male, Female
};

namespace logs {
struct driver : stringbuilder {
	gender_s	gender, opponent_gender;
	const char*	name;
	const char*	opponent_name;
	int			count, opponent_count;
	const char*	weapon;
	constexpr driver(char* result, const char* result_maximum) : stringbuilder(result, result_maximum),
		gender(), opponent_gender(),
		name(), opponent_name(),
		count(1), opponent_count(1),
		weapon() {}
	void		addidentifier(const char* identifier) override;
};
void				addv(int id, int priority, const char* format, const char* param);
inline void			addv(int id, const char* format, const char* param) { addv(id, 0, format, param); }
inline void			add(int id, const char* format, ...) { addv(id, 0, format, xva_start(format)); }
inline void			add(int id, int priority, const char* format, ...) { addv(id, priority, format, xva_start(format)); }
driver&				getbuilder();
inline void			addv(const char* format, const char* param) { getbuilder().addx(' ', format, param); }
inline void			add(const char* format, ...) { addv(format, xva_start(format)); }
void				clear(bool clear_text = false);
int					getcount();
const char*			getpanel(int index); // Defined in main program
int					getwidth(int index); // Defined in main program
int					input(bool interactive = true, bool clear_text = true, const char* format = 0, ...);
int					inputsg(bool interactive = true, bool clear_text = true, const char* format = 0, ...);
int					inputv(bool interactive, bool clear_text, bool return_single, const char* format, const char* param, const char* element);
void				next(bool interactive = true);
void				open(const char* title, bool resize = false);
void				setdark();
void				setlight();
void				sort();
bool				yesno(bool interactive = true, const char* format = 0, ...);
}