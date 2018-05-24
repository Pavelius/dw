#include "main.h"

template<> const char* getstr<tid>(tid id) {
	switch(id.type) {
	case Stats:
		return getstr((stat_s)id.value);
	default:
		return "[!tid]";
	}
}