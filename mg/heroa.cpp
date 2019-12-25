#include "main.h"

void heroa::addn(stringbuilder& sb) {
	unsigned index = 0;
	for(auto p : *this) {
		if(index>0) {
			if(index < count - 1)
				sb.add(", ");
			else
				sb.add(" è ");
		}
		sb.add(p->getname());
	}
}

void heroa::select() {
	auto pa = data;
	for(auto p : players) {
		if(!p || !p->isalive())
			continue;
		*pa++ = p;
	}
	count = pa - data;
}

void heroa::act(const char* format, ...) const {
	char result[512];
	result[0] = 0;
	for(unsigned i = 0; i < count; i++) {
		if(result[0]) {
			if(i+1<count)
				zcat(result, ", ");
			else
				zcat(result, " è ");
		}
		zcat(result, data[i]->getname());
	}
}