#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"", 0, 0, {}, "%����� �����%�� ���� �����."},
{"���������", 0, 0, {Close, Reload}, "%����� ��������%� ��������� � ���������%� � %���������."},
{"��������", 0, 0, {Close}, "%����� �������%� �������� � ���������%�."},
{"�����", 0, 0, {Close, Far}, "%����� �������%� ����� � ������%� ������ �������."},
{"��������", 0, 0, {Close, Messy, Reload}, "%����� �������%� �������� � � �������� ��������%� ���."},
{"������", 1, 0, {Close}, "%����� �������%� �������� � ��������� �������."},
{"���������", 1, 0, {Messy, Reload}, "������ ������������� %����� ������%� �������� ����������. ���� ����� ������."},
{"SMG", 0, 0, {Close, Area}, "%����� ���%� �������� ������� �������� ������ ��������-�������."},
//
{"���", 0, 0, {Light}, "%����� �����%�� ��������� ������ ������ �����."},
{"�����", 0, 0, {Light, Area}, "%����� ������%� ���� ������� ������ �������."},
{"�����", 0, 0, {}, "%����� ��������%� ������ %���������."},
{"����", 0, 0, {Light, Area}, "������ ��������� ������� %����� ����� ���� �����."},
{"����������", 0, 0, {}, "������ ������������� %����� �����%�� ���� �����������."},
{"�������", 1, 0, {Close, Area}, "������ ���� %����� �����%� �������. �������� �����."},
{"������", 1, 0, {Close, Area}, "� ������ %����� �����%�� ������ ���� �������."},
//
{"�������� � ��������", 0, 0, {Far, Scope}, "%����� �������%� �������� � ������%� ������ �������."},
{"�������", 2, 0, {Close, Area}, "%����� �������� ������ ������� � ���%� ������� �������."},
{"�������", 1, 0, {Close, Far, Area}, "%����� �������%� ������� � ���%� ������� �������."},
{"����������", 3, 0, {Far, Area, Reload}, "%����� �������%� ���������� � ������%� �������. ������� ����� ������ ����������� � ����. �������� �����."},
};
assert_enum(item, GrenadeLauncher);

void item::clear() {
	type = NoItem;
	upgrade = 0;
}

dice item::getharm() const {
	dice result = {1, 6, bsmeta<itemi>::elements[type].harm};
	if(is(Light))
		result.d = 3;
	return result;
}

bool item::is(label_s value) const {
	return bsmeta<itemi>::elements[type].tag.is(value);
}

const char* item::getname() const {
	return bsmeta<itemi>::elements[type].name;
}

const char* item::gettextsuccess() const {
	return bsmeta<itemi>::elements[type].success;
}

char* item::getname(char* result, bool description) {
	result[0] = 0;
	//for(auto e = Blade; e <= Valuable; e = (upgrade_s)(e + 1)) {
	//	if(upgrade_data[e].ending)
	//		continue;
	//	if(is(e)) {
	//		zcat(result, upgrade_data[e].name);
	//		zcat(result, " ");
	//	}
	//}
	zcpy(result, getstr(type));
	//for(auto e = Blade; e <= Valuable; e = (upgrade_s)(e + 1)) {
	//	if(!upgrade_data[e].ending)
	//		continue;
	//	if(is(e)) {
	//		zcat(result, " ");
	//		zcat(result, upgrade_data[e].name);
	//	}
	//}
	return result;
}