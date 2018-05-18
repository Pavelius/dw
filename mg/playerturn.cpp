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
	static player_option_info answer_data[] = {{RecoverRoll, "����������� ������������ ���� ����.", 1, &hero::isconditions, &hero::recover},
	{BuyEquipment, "������ ��������� ������ ����������.", 1, &hero::isfreegear},
	{FindAlly, "����� ������������ ���������.", 1},
	{StopRest, "��������� �����"}
	};
	auto checks = 0;
	for(auto p : players) {
		if(!p)
			continue;
		checks += 1 + p->checks;
	}
	while(checks > 0) {
		logs::add("��� �������-�� � ��� ��������� ����� ����������� � ������������ ���� ����.");
		logs::add("� ��� �������� [%1i] ��������.", checks);
		for(auto& e : answer_data) {
			if(e.cost > checks)
				continue;
			if(e.test && !hero::ismatch(e.test))
				continue;
			if(e.cost)
				logs::add(&e - answer_data, "%1 ����� [%2i] ��������.", e.text, e.cost);
			else
				logs::add(&e - answer_data, e.text, e.cost);
		}
		auto& e = answer_data[logs::input()];
		checks -= e.cost;
		hero* player = 0;
		if(e.test)
			player = choose(true, e.test);
	}
}

void hero::gonext() {
}