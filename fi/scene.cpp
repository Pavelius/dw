#include "main.h"

int	scene::getplayercount() const {
	auto result = 0;
	for(auto p : players) {
		if(p)
			result++;
	}
	return result;
}