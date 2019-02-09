#include "main.h"

template<> const char* getstr<variant>(variant e) {
	switch(e.type) {
	case Skills: return getstr(e.skill); break;
	case Actions: return getstr(e.action); break;
	default: return "No variant";
	}
}

template<> const char* getstr<variant_set>(variant_set e) {
	return getstr(e.type);
}