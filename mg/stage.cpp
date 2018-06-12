#include "main.h"

struct stage {
	const char*	text;
	skill_s		skill;
	item_s		tools[8];
	explicit operator bool() const { return text != 0; }
};
static stage border_scent[] = {{"Ваш отряд пробирался по высокой траве, в поисках подходящего места куда можно заложить зелье для пометки территории. Необходимо добраться до границы обитаемых земель и только там можно найти такое место.", Pathfinder},
{"Теперь отсалось найти удачное место для размещения зелья.", Scientist},
};
static struct stage_info {
	const char*	key;
	stage*		value;
} stage_data[] = {
	{"border_scent", border_scent}
};

static stage* find_quest(const char* quest_id) {
	for(auto& e : stage_data) {
		if(strcmp(e.key, quest_id) == 0)
			return e.value;
	}
	return 0;
}

void hero::quest(const char* quest_id) {
	auto p = find_quest(quest_id);
	if(!p)
		return;
	while(*p) {
		logs::add(p->text);
		if(passtest(p->skill, 4))
			p++;
		else {
			// Произошла смена сюжета
		}
	}
}