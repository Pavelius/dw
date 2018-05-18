#include "main.h"

static unsigned	current_round;

int	game::getmoverate() {
	auto value = getpartyspeed() * 2;
	return value;
}

int	game::gethour() {
	return (getround() / RDay) / (24 * 60);
}

timezone_s game::getzone() {
	return (timezone_s)((getround() % RDay) / (4 * RHour));
}

int	game::getday() {
	return (getround() % RMonth) / (24 * 60);
}

int	game::getyear() {
	return getround() / RYear;
}

int	game::getmonth() {
	return (getround() % RYear) / RMonth;
}

void game::passtime(bool interactive, unsigned rounds) {
	if(!rounds)
		return;
	if(interactive) {
		if(rounds < 2) {
		} else if(rounds <= RHour / 6)
			logs::add("������ %1i �����.", rounds);
		else if(rounds < 40)
			logs::add("������ ����� %1i �����.", ((rounds + 9) / 10) * 10);
		else if(rounds <= RHour)
			logs::add("������ ���.");
		else if(rounds <= RDay / 4)
			logs::add("������ ��������� �����.");
		else if(rounds < RDay)
			logs::add("������ ������ �������� ���.");
		else if(rounds < 2 * RDay)
			logs::add("������ ����.");
		else if(rounds < 5 * RDay)
			logs::add("������ ��������� ����.");
		else
			logs::add("������ ����� ����.");
	}
	current_round += rounds;
}

unsigned game::getround() {
	return current_round;
}

bool game::ispartyready() {
	for(auto p : party) {
		if(p->isready())
			return true;
	}
	return false;
}

bool game::isparty(bool (character::*proc)() const) {
	for(auto p : party) {
		if(p && (p->*proc)())
			return true;
	}
	return false;
}

int	game::getminimum(int (character::*proc)() const) {
	auto result = 100000;
	for(auto p : party) {
		if(!p->isready())
			continue;
		auto i = (p->*proc)();
		if(i < result)
			result = i;
	}
	return result;
}

character* game::getplayer() {
	for(auto p : party) {
		if(p && p->isready())
			return p;
	}
	return 0;
}

reaction_s game::reduce(reaction_s id) {
	switch(id) {
	case Hostile: return Hostile;
	case Threatening: return Hostile;
	case Cautions: return Threatening;
	case Indifferent: return Cautions;
	default: return Indifferent;
	}
}

character* game::choose(bool interactive) {
	for(auto p : party) {
		if(!p->isready())
			continue;
		logs::add((int)p, p->getname());
	}
	return (character*)logs::input(interactive, false, "�������� ���������:");
}

bool game::isallow(const tag id) {
	switch(id.type) {
	case Action:
	case Reaction:
		return true;
	case Timezone: return getzone() != id.value;
	default:
		for(auto p : party) {
			if(!p->isready())
				continue;
			if(p->isallow(id))
				return true;
		}
		return false;
	}
}

bool game::isallow(const tag id, character* player) {
	switch(id.type) {
	case Action:
	case Reaction:
		return true;
	case Timezone: return getzone() != id.value;
	default:
		if(!player->isready())
			return false;
		return player->isallow(id);
	}
}

bool game::attack(int thac0, int ac) {
	auto chance = thac0 - ac;
	auto roll = d20();
	return roll >= chance;
}

character* game::choose(bool interactive, tag id) {
	if(id.type == Action)
		return getplayer();
	if(id.type == Skill) {
		for(auto p : party) {
			if(!p->isallow(id))
				continue;
			logs::add((int)p, "%1 (����� [%2i%%])",
				p->getname(),
				p->get((skill_s)id.value));
		}
		return (character*)logs::input(interactive, false, "��� ������� ������ [%1]?", getstr(id));
	} else if(id.type == Ability) {
		for(auto p : party) {
			if(!p->isallow(id))
				continue;
			logs::add((int)p, "%1 (%2 [%3i])",
				p->getname(),
				getstr((ability_s)id.value),
				p->get((ability_s)id.value));
		}
		return (character*)logs::input(interactive, false, "��� ������� ���� [%1]?", getstr(id));
	}
	for(auto p : party) {
		if(!p->isallow(id))
			continue;
		logs::add((int)p, p->getname());
	}
	return (character*)logs::input(interactive, false, "��� ��� �����?");
}

//void game::loosemoney() {
//	if(player)
//		player->addmoney(player->getmoney());
//}

//void game::pickpockets() {
//	static struct theft_effect {
//		const char*		text;
//		dice			count;
//	} effects[] = {
//		{"�� ����� �� ������ ���-�� ����� ������� �������. %����� ��������%� ��� �������������, ��������� ���������� �� ���� � �������.", {2, 6, 0, CP}},
//		{"���� ������ ������, �������� %����� �����%�� ��������� �� ������ ������� ������ ��������.", {2, 6, 0, SP}},
//		{"�� ����� ����� � ����� ������� ������������ %����� ������%� � ��� �� ����� ������ � ��������.", {3, 6, 0, SP}},
//		{"���� ������� ������, ������� ��� �������� �� ����� ������� ������ ��������.", {2, 6, 0, GP}},
//	};
//	auto& e = maprnd(effects);
//	auto value = e.count.roll();
//	if(value) {
//		logs::add(e.text);
//		player->act("%����� �����%� [%1i] �������.", value);
//		player->addmoney(value);
//	}
//}

//void game::testcatched() {
//	auto opponent_level = 3;
//	auto chance_catch = 100 - opponent_level * 3;
//	if(test.result >= chance_catch) {
//		logs::add("\n - ���� - �������� ���-�� - ����� ����!!\n");
//		logs::add("��������� ����������� �������� �� ��� � ������ ��������.");
//		logs::add("����� ��� �������� ��� ���� ������ � �������� ��� �� �����.");
//		logs::next();
//		badreaction();
//		moveaway();
//	}
//}

void game::charsheet() {
	auto player = choose(true);
	player->charsheet();
}