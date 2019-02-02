#include "main.h"

void character::clear() {
	memset(this, 0, sizeof(*this));
}

char character::getmaximum(ability_s v) const {
	auto r = 4;
	if(getkey(race) == v)
		r++;
	if(getkey(profession) == v)
		r++;
	return r;
}

char character::getminimum(ability_s v) const {
	return 2;
}

void character::apply_talents() {
	for(auto i = FirstTalent; i <= LastTalent; i = (talent_s)(i + 1)) {
		if(getkey(i) == variant(race))
			talents[i] = 1;
	}
}

int	character::roll(skill_s id, int modifier, bool interactive) {
	auto attribute = getkey(id);
	auto s = get(id) + modifier;
	auto b = get(attribute);
	diceroll r; r.clear();
	r.roll(Attributes, b, 6);
	r.roll(Skills, s, 6);
	auto sixth = 0;
	auto p = logs::getptr();
	auto pushed = false;
	while(r) {
		for(unsigned i = 0; i < r.count; i++) {
			if(p == logs::getptr())
				logs::add("������ %1: ", getstr(id));
			else
				logs::add(", ");
			auto& e = r.data[i];
			switch(e.type) {
			case Attributes: logs::add("[%1i]", e.result); break;
			case Skills: logs::add("[%+1i]", e.result); break;
			default: logs::add("%1i", e.result); break;
			}
		}
		logs::add(".");
		sixth = r.getsix();
		if(sixth>0)
			logs::add(1, "������� �������� ���������.");
		else {
			logs::add(1, "��������� � ����������� �������.");
			if(pride>=1)
				logs::add(3, "������������ ��������.");
		}
		if(!pushed && r.getreroll()>0)
			logs::add(2, "���������� ����.");
		auto result = logs::input(interactive, false);
		p[0] = 0;
		if(result == 1)
			break;
		else if(result == 2) {
			pushed = true;
			r.pushroll();
			auto ones = r.getone(Attributes);
			logs::add("\n�� �������� [-%1i] ���� %2.", ones, getnameof(attribute));
			logs::add("\n�� �������� [%1i] ���� ���� ����.", ones);
			logs::add(1, "����������");
			logs::input(interactive, false, 0);
			p[0] = 0;
		} else if(result == 3) {
			r.roll(Talents, 1, 12);
			if(r.getsix() >= 0)
				pride = 0;
			else
				pride = -1;
		}
	}
	return r.getsix();
}