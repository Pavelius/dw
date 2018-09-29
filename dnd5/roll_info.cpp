#include "main.h"

void roll_info::set(roll_s type) {
	switch(type) {
	case Advantage: advantage = true; break;
	case Disadvantage: disadvantage = true; break;
	}
}

roll_s roll_info::get() const {
	if(advantage && !disadvantage)
		return Advantage;
	if(!advantage && disadvantage)
		return Disadvantage;
	return RollNormal;
}

roll_info::operator bool() const {
	if(rolled == 1)
		return false;
	else if(rolled >= dc || rolled == 20)
		return true;
	return false;
}