#pragma once

class string {
	const char*	pb;
	const char*	pe;
	constexpr const char* zend(const char* p) { while(*p) p++; return p; }
public:
	constexpr string(const char* p) : pb(p), pe(zend(p)) {}
	constexpr string(const char* pb, const char* pe) : pb(pb), pe(pe) {}
	constexpr string() : pb(""), pe("") {}
	char& operator[] (unsigned pos) { return ((char*)pb)[pos]; }
	operator bool() const { return pb < pe; }
	const char* begin() const { return pb; }
	void clear() { pb = pb = ""; }
	constexpr unsigned lenght() const { return pe - pb; }
	const char* end() const { return pe; }
	string substr(unsigned pos, unsigned n) const { return string((pb + pos > pe) ? pe : pb + pos, (pb + pos + n > pe) ? pe : pb + pos + n); }
};