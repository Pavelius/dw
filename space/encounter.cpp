#include "main.h"

spaceship* solar::getenemy(const spaceship* s) const {
	for(auto p : *this) {
		if(p->isenemy(s))
			return p;
	}
	return 0;
}