#include "answer.h"

#pragma once

enum gender_s : unsigned char {
	NoGender, Male, Female
};

namespace logs {
typedef void(*logp)(stringbuilder& sb); // Standart status printer
template<unsigned last>
class flagable {
	static constexpr unsigned s = 8;
	static constexpr unsigned c = 1 + last / s;
	unsigned char			data[c];
public:
	constexpr flagable() : data{0} {}
	template<class T> constexpr flagable(const std::initializer_list<T>& v) : data{0} { for(auto e : v) set(e); }
	constexpr void			add(const flagable& e) { for(unsigned i = 0; i < c; i++) data[i] |= e.data[i]; }
	void					clear() { memset(this, 0, sizeof(*this)); }
	constexpr bool			is(short unsigned v) const { return (data[v / s] & (1 << (v%s))) != 0; }
	constexpr void			remove(short unsigned v) { data[v / s] &= ~(1 << (v%s)); }
	constexpr void			set(short unsigned v) { data[v / s] |= 1 << (v%s); }
	constexpr void			set(short unsigned v, bool activate) { if(activate) set(v); else remove(v); }
};
struct driver : stringbuilder {
	gender_s				gender, opponent_gender;
	const char				*name, *opponent_name;
	int						count, opponent_count;
	const char*				weapon;
	constexpr driver(const stringbuilder& sb) : stringbuilder(sb),
		gender(NoGender), opponent_gender(NoGender),
		name(0), opponent_name(0),
		count(1), opponent_count(1),
		weapon(0) {
	}
	void					addidentifier(const char* identifier) override;
};
extern answeri				an;
void						open(const char* title, bool resize = false);
void						next(bool clear_text = true);
extern logp					right_proc;
extern stringbuilder		sb;
void						setdark();
void						setlight();
bool						yesno(bool interactive = true);
}