#include "main.h"

enum player_option_s : unsigned char {
	RecoverRoll, BuyEquipment, FindAlly,
	StopRest,
};
struct player_option_info {
	player_option_s	id;
	const char*		text;
	char			cost;
	bool			(hero::*test)() const;
	void			(hero::*action)();
};

void hero::playersturn() {
	static player_option_info answer_data[] = {{RecoverRoll, "Попробывать восстановить свои силы.", 1, &hero::isconditions, &hero::recover},
	{BuyEquipment, "Купить некоторую нужную экипировку.", 1, &hero::isfreegear},
	{FindAlly, "Найти определенных личностей.", 1},
	{StopRest, "Закончить отдых"}
	};
	auto checks = 0;
	for(auto p : party) {
		if(!p)
			continue;
		checks += 1 + p->checks;
	}
	while(checks > 0) {
		sb.addn("Вот наконец-то у вас появилось время передохнуть и восстановить свои силы.");
		sb.adds("У вас осталось [%1i] проверок.", checks);
		for(auto& e : answer_data) {
			if(e.cost > checks)
				continue;
			if(e.test && !hero::ismatch(e.test))
				continue;
			if(e.cost)
				an.add((int)&e, "%1 Стоит [%2i] проверок.", e.text, e.cost);
			else
				an.add((int)&e, e.text, e.cost);
		}
		auto p = (player_option_info*)an.choose();
		checks -= p->cost;
		hero* player = 0;
		if(p->test)
			player = choose(true, p->test);
	}
}

void hero::gonext() {
}