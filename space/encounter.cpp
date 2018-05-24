#include "main.h"

spaceship* encounter::getenemy(const spaceship* s) const {
	for(auto p : source) {
		if(p->isenemy(s))
			return p;
	}
	return 0;
}