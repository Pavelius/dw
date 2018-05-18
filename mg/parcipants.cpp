#include "main.h"

void parcipants::act(const char* format, ...) const {
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