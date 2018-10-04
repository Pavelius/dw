#include "main.h"

void scene::clear() {
	for(auto& p : creatures) {
		if(p->israndom()) {
			delete p;
			p = 0;
		}
	}
}
