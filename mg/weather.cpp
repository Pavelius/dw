#include "main.h"

template<> weatheri bsmeta<weatheri>::elements[] = {{"Clear and warm weather", "����� � ������ ������", "������ ����� � ������ ������.", "���� ����� ������ � ������������ ����� � ������ ������.", 3, Spring, Spring},
{"Spring snow", "�������� ����", "������ ���� ������ �������� ����.", "�������� ����� ������ ����.", 1, Spring, Spring, {Tired, Sick}, true, 0, 3},
{"Spring rain", "�������� �����", "�� ���� �������� � ������� ������ �����.", "������� ������ �����.", 1, Spring, Spring, {}, true, 3},
{"Spring strom", "������� �����", "�� ����� ���� ������� �������� ������� ������.", "����� ���� ����������� ������� ������. ����������� ��������� �������� �����. ������ �����-�� ����� ����� ����� � �������� ��������� ������, ���������������� ������ � ��������.", 1, Spring, Spring, {Injured}},
{"Unseasonably cold", "�����������", 0, 0, 1, Spring, Winter},
{"Unseasonably warm", "����������", 0, 0, 1, Spring, Summer},
//
{"Warm and humid weather", "������ � ������� ������", "�� ����� ����� ������ � ������� ������.", "���� ����� ������. �� ��� �� ���� �� ������ �������.", 3, Summer, Summer},
{"Summer rain", "������ �����", "�� ���� ����, �� ������ ������� ����������������� ������ �����.", "������ � ���� ����� �����.", 1, Summer, Summer, {}, false, 0, 0, {Pathfinder, Scout}},
{"Thunderstorm", "�����", "�� ���� ���� ��������, ���� ���� ���� �����.", "���� ������ �������� ������� ������. ����� ������� �����. ��������� ����� �����. � ������� ���������� ������.", 1, Summer, Summer},
{"Heat waves", "����", "������ ������ ����������� ����.", 0, 1, Summer, Summer},
//
{"Autum storm", "������� �����", "�� ����� ��� �����, ���� ���� �������� ����� �������.", 0, 2, Autum, Autum},
{"Cold rain", "�������� �����", "���� ����� ������� � ��� �����.", 0, 1, Autum, Autum},
{"Unseasonably cold", "�����������", 0, 0, 1, Autum, Winter},
{"Unseasonably warm", "����������", 0, 0, 1, Autum, Summer},
//
{"Clear and cold weather", "����� � �������� ������", "�� ����� ����� ����, ���� ��� �����, ���� �������� �����.", "���� ����������� � ������ ���������� ������ ������.", 3, Winter, Winter},
{"Snow", "����", "�� ����� ��� ����.", "������ � ���� ����� ������ ����.", 1, Winter, Winter},
{"Blizzard", "������", "������ ���� ��������� ������, ������� ������ ����� ������ ���� �����.", 0, 1, Winter, Winter},
{"Cold Snap", "���������", "�� ����� ���� ����� �������.", 0, 1, Winter, Winter},
{"Ice Storm", "�����", "�� ����� ���� ����� ��������� ���� - �������� ������� ������� ��������� ��� ������.", 0, 1, Winter, Winter},
{"Unseasonably warm", "����������", "", 0, 1, Winter, Autum},
};
assert_enum(weather, WinterUnseasonablyWarm);

weather_s weatheri::getid() const {
	return weather_s(this - bsmeta<weatheri>::elements);
}

bool hero::isfactor(weather_s object, skill_s value) {
	return bsmeta<weatheri>::elements[object].skills.is(value);
}

void hero::weatherwatch() {
	party.addweather();
	sb.adds("�� ������������ � ������� �������, ����� ������ ����� ������.");
	if(passtest(WeatherWatcher, getobstacle(party.getseason()))) {
		auto ni = party.getnext();
		auto ns = party.getseason(ni);
		for(auto& e : bsmeta<weatheri>()) {
			if(e.nonseason())
				continue;
			if(e.season != ns)
				continue;
			an.add(e.getid(), e.name);
		}
		auto nw = (weather_s)an.choosev(true, true, false, "����� ������ ����� ���������?");
		party.set(nw);
	} else {
	}
}

void hero::twistweather(bool interactive, skill_s skill, heroa& helps) {
	auto ns = party.getnext();
	//if(interactive)
	//	sb.add(bsmeta<weatheri>::elements[season_index].start_text);
}