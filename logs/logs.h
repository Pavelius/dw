#include "stringbuilder.h"

#pragma once

namespace logs {
void			addv(int id, int priority, const char* format, const char* param);
inline void		addv(int id, const char* format, const char* param) { addv(id, 0, format, param); }
inline void		add(int id, const char* format, ...) { addv(id, 0, format, xva_start(format)); }
inline void		add(int id, int priority, const char* format, ...) { addv(id, priority, format, xva_start(format)); }
stringbuilder&	getbuilder();
inline void		addv(const char* format, const char* param) { getbuilder().addx(' ', format, param); }
inline void		add(const char* format, ...) { addv(format, xva_start(format)); }
void			clear(bool clear_text = false);
int				getcount();
const char*		getpanel(int index); // Defined in main program
int				getwidth(int index); // Defined in main program
int				input(bool interactive = true, bool clear_text = true, const char* format = 0, ...);
int				inputsg(bool interactive = true, bool clear_text = true, const char* format = 0, ...);
int				inputv(bool interactive, bool clear_text, bool return_single, const char* format, const char* param, const char* element);
void			next(bool interactive = true);
void			open(const char* title, bool resize = false);
void			setdark();
void			setlight();
void			sort();
bool			yesno(bool interactive = true, const char* format = 0, ...);
}