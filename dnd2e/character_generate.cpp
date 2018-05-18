#include "main.h"

static struct multiclass {
	classa		classes;
	racea		races;
} multiclass_data[] = {
	{{Cleric}, {Human, HalfElf, HalfOrc}},
	{{Druid}, {Human, HalfElf}},
	{{Fighter}, {Human, Dwarf, Elf, Gnome, HalfElf, Halfling, HalfOrc}},
	{{Paladin}, {Human}},
	{{Ranger}, {Human, HalfElf}},
	{{MagicUser}, {Human, Elf, HalfElf}},
	{{Illusionist}, {Human, Gnome}},
	{{Theif}, {Human, Dwarf, Elf, Gnome, HalfElf, Halfling, HalfOrc}},
	//
	{{Fighter, Cleric}, {HalfElf, HalfOrc}},
	{{Fighter, Cleric, MagicUser}, {HalfElf}},
	{{Ranger, Cleric}, {HalfElf}},
	{{Cleric, MagicUser}, {HalfElf}},
	{{Cleric, Theif}, {HalfElf}},
	{{Fighter, MagicUser}, {Elf, HalfElf}},
	{{Fighter, Illusionist}, {Gnome}},
	{{Fighter, Theif}, {Dwarf, Elf, Gnome, HalfElf, Halfling, HalfOrc}},
	{{Fighter, MagicUser, Theif}, {Elf, HalfElf}},
	{{MagicUser, Theif}, {Elf, HalfElf}},
	{{Illusionist, Theif}, {Gnome}},
};

static bool match(const char* a, const char* mv) {
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(mv[i] && a[i] < mv[i])
			return false;
	}
	return true;
}

static bool match(const char* a, const char* mv, const char* mm) {
	if(!match(a, mv))
		return false;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(mv[i] && a[i] > mm[i])
			return false;
	}
	return true;
}

void character::chooseability(bool interactive, char* abilities) {
	if(!interactive) {
		for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
			auto v1 = dice::roll(3, 6);
			auto v2 = dice::roll(3, 6);
			abilities[i] = imax(v1, v2);
		}
	} else {
		do {
			for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
				auto v1 = dice::roll(3, 6);
				auto v2 = dice::roll(3, 6);
				abilities[i] = imax(v1, v2);
			}
			logs::add("������ ��� ����������� � ��� D&D, �� ������ ������� ������ ���������. ��������� ���� �������� - ��� ���� alter ego � �������������� ����� ���� ����, ������������ ��������, ����������� ���, � ������� ������� �� ������������� ���������� ���, ��������� ��������.\n");
			logs::add("������ �������� � D&D �������� ������ ������������� : ����, ��������, ������������, ���������, �������� � �������.��� ������ ����������� ������������� ���������� ����������� ���������, � ��� ������ - ��� ���������� ����������� � ������ ��������.\n");
			logs::add("���� �����������: ");
			for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
				if(i != Strenght)
					logs::add(", ");
				logs::add("%1 [%2i]", getstr(i), abilities[i]);
			}
			logs::add(".");
			logs::add(1, "����������");
			logs::add(2, "�����������");
		} while(logs::input(interactive) == 2);
	}
}

static bool israce(class_s c, race_s r) {
	for(auto e : character::getraces(c)) {
		if(!e)
			break;
		if(e == r)
			return true;
	}
	return false;
}

static bool match(char* abilities, classa& classes) {
	for(auto e : classes) {
		if(!match(abilities, character::getminimum(e)))
			return false;
	}
	return true;
}

static char* getclassname(char* temp, classa& ai) {
	temp[0] = 0;
	for(auto e : ai) {
		if(!e)
			break;
		if(temp[0])
			zcat(temp, "/");
		zcat(temp, getstr(e));
	}
	return temp;
}

const class_s* character::chooseclass(bool interactive, race_s race, char* abilities) {
	static classa empthy = {};
	char temp[260];
	if(!abilities)
		return empthy;
	for(auto& e : multiclass_data) {
		if(!zchr(e.races, race))
			continue;
		if(!match(abilities, e.classes))
			continue;
		logs::add((int)&e.classes, getclassname(temp, e.classes));
	}
	if(logs::getcount() == 0)
		return empthy;
	logs::sort();
	return (class_s*)logs::input(interactive, false, "����� ����������� ���� ��������� �� ��������� ��� �����. ����� ��������� - ��� ����� ����� ��� ��������� ��� ���� �������. ��� ��� ��� ������������, ������� �������� ��������� ��� �������� �������� � ������. ���� �� �������� ����� ������, �� �� ������� ����� �� ���� � ���������� ������ ��������. ������� ��� ����� ���������� ��������������� �����������. �� �� ����� ����� ������� � ������� ������� ���������� � AD&D. ��������������, ��� ����� ���, ��� ������ ���� ��������������� ������������, �������� ������ ������������ ��������������� �������� � ����������. ������, ����������� ���������� �������� � ��������, ��� �������� ����� ����������� ���� ������ ��� � �����.");
}

static char* szrating(char* result, const char* text, int level) {
	zcpy(result, text);
	auto p = zend(result);
	for(int i = 1; i < level; i++)
		*p++ = '+';
	*p = 0;
	return result;
}

race_s character::chooserace(bool interactive, char* abilities) {
	for(auto i = Human; i <= Halfling; i = (race_s)(i + 1)) {
		if(!match(abilities, getminimum(i), getmaximum(i)))
			continue;
		logs::add(i, "[%1]: %2", getstr(i), getinfo(i));
	}
	if(logs::getcount() == 0)
		return Human;
	logs::sort();
	return (race_s)logs::input(interactive, false, "����� ����������� ����������� ������������ ������ ��������� �� ������ ������� ��� ����. ��� �� �� �� �����, ��� ���� � ������������ ������ ����� �����: �����������, ������������ ��� ����������. � ������ ������ ������� � ���� ������������ ������������� ��� ������ ��������� - �������, ����, ��������, ������, ���� ��� ������. ������ ���� ������� ���������� �� ������. ������ ���� �������� ������� �������������� � ����� ���� ������ �������, ��������� ��� ������.");
}

void character::equip(class_s type) {
	switch(classes[0]) {
	case Fighter:
		add(LongSword);
		add(LeatherArmor);
		add(Shield);
		break;
	case Paladin:
	case Ranger:
		add(LongSword);
		add(LeatherArmor);
		add(Shield);
		break;
	case MagicUser:
		add(Staff);
		break;
	case Cleric:
		add(Mace);
		add(LeatherArmor);
		break;
	default:
		add(Dagger);
		add(LeatherArmor);
		break;
	}
}

character::character(bool interactive) {
	char abilities[Charisma + 1]; chooseability(interactive, abilities);
	auto race = chooserace(interactive, abilities);
	auto type = chooseclass(interactive, race, abilities);
	create(interactive, race, Male, type, abilities, true);
}