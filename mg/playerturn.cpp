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
	for(auto p : players) {
		if(!p)
			continue;
		checks += 1 + p->checks;
	}
	while(checks > 0) {
		sb.adds("Вот наконец-то у вас появилось время передохнуть и восстановить свои силы.");
		sb.adds("У вас осталось [%1i] проверок.", checks);
		for(auto& e : answer_data) {
			if(e.cost > checks)
				continue;
			if(e.test && !hero::ismatch(e.test))
				continue;
			if(e.cost)
				an.add(&e - answer_data, "%1 Стоит [%2i] проверок.", e.text, e.cost);
			else
				an.add(&e - answer_data, e.text, e.cost);
		}
		auto& e = answer_data[an.choosev(true, true, true, 0)];
		checks -= e.cost;
		hero* player = 0;
		if(e.test)
			player = choose(true, e.test);
	}
}

void hero::gonext() {
}