#include "main.h"

const char* variant::getname() const {
	switch(type) {
	case Skills: return getstr((skill_s)subtype); break;
	case Actions: return getstr((action_s)subtype); break;
	default: return "No variant";
	}
}