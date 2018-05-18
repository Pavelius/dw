#include "main.h"

static stage border_scent_scientist = {
	"Теперь необходимо правильно разместить зелье.",
	0, 0,
	Scientist
};
static stage border_scent_pathfinder = {
	"Ваш отряд пробирался по высокой траве, в поисках подходящего места куда можно заложить зелье для пометки территории.",
	&border_scent_scientist, 0,
	Pathfinder
};

void hero::quest(stage* start) {
	while(start) {
		if(passtest(start->skill, 4))
			start = start->next;
		else {
			// Произошла смена сюжета
		}
	}
}