#pragma once

#define xva_start(v) ((const char*)&v + sizeof(v))

class stringbuilder {
	char*				p;
	char*				pb;
	const char*			pe;
	const char*			readformat(const char* format, const char* format_param);
	const char*			readvariable(const char* format);
public:
	struct driver {
		virtual void	addidentifier(stringbuilder& sb, const char* identifier) = 0;
	};
	driver*				custom;
	constexpr stringbuilder(char* pb, const char* pe) : pb(pb), p(pb), pe(pe), custom(0) { pb[0] = 0; }
	template<unsigned N> constexpr stringbuilder(char(&result)[N]) : stringbuilder(result, result + N) {}
	constexpr operator char*() const { return pb; }
	void				add(const char* format, ...) { addv(format, xva_start(format)); }
	void				adderror(const char* identifier);
	void				addicon(const char* id, int value);
	static char*		addint(char* result, const char* result_maximum, int value, int precision, const int radix);
	void				addn(const char* format, ...) { addx('\n', format, xva_start(format)); }
	void				adds(const char* format, ...) { addx(' ', format, xva_start(format)); }
	void				addsep(char separator);
	void				addsz() { if(p < pe) *p++ = 0; }
	void				addv(const char* format, const char* format_param);
	void				addx(char separator, const char* format, const char* format_param);
	static char*		adduint(char* result, const char* result_maximum, unsigned value, int precision, const int radix);
	char*				begin() { return pb; }
	const char*			begin() const { return pb; }
	void				clear() { pb[0] = 0; p = pb; }
	const char*			end() const { return pe; }
	char*				get() const { return p; }
	static bool			ischa(unsigned char sym) { return (sym >= 'A' && sym <= 'Z') || (sym >= 'a' && sym <= 'z') || sym>=0xC0; }
	static bool			isnum(unsigned char sym) { return sym >= '0' && sym <= '9'; }
	bool				ispos(const char* v) const { return p == v; }
	static unsigned char lower(unsigned char sym);
	void				set(char* v) { p = v; p[0] = 0; }
	static unsigned char upper(unsigned char sym);
};