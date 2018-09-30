#include "crt.h"
#include "grammar.h"

static const char spaces[] = {" \n\t\r.,!?;:"};

struct grammar_map {
	const char*		name;
	const char*		change;
	unsigned		name_size;
	unsigned		change_size;
	constexpr grammar_map() : name(0), change(0), name_size(0), change_size(0) {}
	grammar_map(const char* name, const char* change) :
		name(name), change(change), name_size(zlen(name)), change_size(zlen(change)) {}
	operator bool() const { return name != 0; }
};

static const char* word_end(const char* ps) {
	while(*ps) {
		for(auto e : spaces) {
			if(*ps == e)
				return ps;
		}
		ps++;
	};
	return ps;
}

static const char* skip_space(const char* ps) {
	while(*ps) {
		for(auto e : spaces) {
			if(*ps != e)
				return ps;
		}
		ps++;
	};
	return ps;
}

static inline bool is_space(char sym) {
	for(auto e : spaces) {
		if(sym == e)
			return true;
	}
	return false;
}

static void change(char* result, const char* result_maximum, const char* s, const grammar_map* source, const char* def = 0) {
	auto r = result;
	auto ps = skip_space(s);
	while(*ps) {
		auto pe = word_end(ps);
		unsigned s1 = pe - ps;
		auto found = false;
		for(auto p = source; *p; p++) {
			auto s2 = p->name_size;
			if(p->name_size > s1)
				continue;
			if(memcmp(pe - s2, p->name, s2) == 0) {
				auto s3 = p->change_size;
				memcpy(r, ps, s1 - s2);
				memcpy(r + (s1 - s2), p->change, s3);
				r = r + (s1 - s2 + s3);
				if(pe[0] == 0)
					def = 0;
				found = true;
				break;
			}
		}
		if(!found) {
			memcpy(r, ps, pe - ps);
			r += pe - ps;
		}
		ps = pe;
		while(*ps) {
			if(is_space(*ps))
				*r++ = *ps++;
			break;
		}
	}
	r[0] = 0;
	if(def)
		szprints(zend(r), result_maximum, def);
}

char* grammar::of(char* result, const char* result_maximum, const char* s) {
	static grammar_map map[] = {{"ый", "ого"},
	{"ий", "ого"},
	{"ое", "ого"},
	{"ая", "ой"},
	{"би", "би"},
	{"ты", "т"},
	{"сы", "сов"},
	{"ны", "н"},
	{"а", "ы"},
	{"ь", "и"},
	{"о", "а"},
	{"я", "и"},
	{}};
	change(result, result_maximum, s, map, "а");
	return result;
}

char* grammar::by(char* result, const char* result_maximum, const char* s) {
	static grammar_map map[] = {{"ая", "ой"},
	{"ый", "ым"},
	{"ое", "ым"},
	{"би", "би"},
	{"ий", "ием"},
	{"й", "ем"}, {"ь", "ем"}, {"е", "ем"},
	{"а", "ой"},
	{"ч", "чем"},
	{}
	};
	change(result, result_maximum, s, map, "ом");
	return result;
}

char* grammar::to(char* result, const char* result_maximum, const char* s) {
	static grammar_map map[] = {{"а", "е"},
	{"о", "у"},
	{"ы", "ам"},
	{}
	};
	change(result, result_maximum, s, map, "у");
	return result;
}

//char* grammar::pluar::of(char* r, const char* s) {
//	static grammar_map map[] = {
//		{"ты", "т"},
//	{"ы", ""},
//	{"а", ""},
//	{"и", "и"},
//	{"ч", "чей"},
//	{"ж", "жей"},
//	{}
//	};
//	change(r, s, map, "ов");
//	return r;
//}

//char* grammar::get(char* result, const char* result_maximum, const char* word, int count) {
//	if(count <= 1) {
//		zcpy(result, word);
//	} else {
//		szprints(result, result_maximum, "%1i ", count);
//		auto p = zend(result);
//		if(count <= 4)
//			of(p, word);
//		else
//			pluar::of(p, word);
//	}
//	return result;
//}