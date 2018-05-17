#include "main.h"

static unsigned current_minute;

result_s hero::roll(move_s move) {
	switch(move) {
	case FaceAdversityMettle:
	case AssessmentMettle:
	case OpenFire:
		return roll(Mettle);
	case FaceAdversityPhysique:
	case AssessmentPhysique:
	case LaunchAssault:
		return roll(Physique);
	case FaceAdversityInfluence:
	case AssessmentInfluence:
	case Command:
		return roll(Influence);
	case FaceAdversityExpertise:
	case AssessmentExpertise:
	case PatchUp:
		return roll(Expertise);
	case FaceAdversityInterface:
	case AssessmentInterface:
	case Access:
		return roll(Interface);
	default:
		return Fail;
	}
}

result_s hero::roll2d6(int bonus, int* result, bool show_numbers) {
	auto d = xrand(1, 6) + xrand(1, 6);
	auto r = d + bonus;
	if(result)
		*result = r;
	if(r <= 6) {
		if(show_numbers)
			logs::add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	} else if(r <= 9) {
		if(show_numbers)
			logs::add("[!{%1i%+2i=%3i}]", d, bonus, r);
		return PartialSuccess;
	} else {
		if(show_numbers)
			logs::add("[+{%1i%+2i=%3i}]", d, bonus, r);
		return Success;
	}
}

int hero::getarmor() const {
	return attire.getarmor();
}

bool hero::isready() const {
	return !is(Fatal);
}

bool hero::isclumsy() const {
	if(is(Critical))
		return true;
	return attire.isclumsy() || weapon.isclumsy();
}

bool hero::istwohanded() const {
	return attire.istwohanded() || weapon.istwohanded();
}

bool hero::is(kit_s value) const {
	return kit.is(value);
}

bool hero::is(severity_s value) const {
	return damages[0].is(value) || damages[1].is(value);
}

severity_s hero::set(severity_s value) {
	if(skills.is(Toughness)) {
		while(damages[0].is(value) && damages[1].is(value) && value <= Fatal)
			value = (severity_s)(value + 1);
		damages[damages[0].is(value) ? 1 : 0].set(value);
	} else {
		while(damages[0].is(value) && value <= Fatal)
			value = (severity_s)(value + 1);
		damages[0].set(value);
	}
	return value;
}

void hero::set(asset_s value) {
	if(value >= CombatKnife && value <= HullBuster)
		weapon.set(value);
	else if(value >= Jumpsuit && value <= BoardingArmor)
		attire.set(value);
}

void hero::set(kit_s value) {
	kit.set(value);
}

char* hero::getname(char* result, const char* result_maximum) const {
	szprints(result, result_maximum, "�������");
	return result;
}

assets&	hero::get(assets_groups group) {
	switch(group) {
	case GroupAttire: return attire;
	case GroupWeapon: return weapon;
	default: return crew;
	}
}

void hero::clear() {
	memset(stats, 0, sizeof(stats));
	damages[0].clear();
	damages[1].clear();
	debilities.clear();
	weapon.clear();
	attire.clear();
	crew.clear();
	kit.clear();
	spaceship = 0;
	planet = 0;
}

bool hero::acquisition(int market_class, bool specialized) {
	int result, id;
	int bonus = 0;
	if(spaceship) {
		logs::add(1, "������ ������ ��������");
		logs::add(2, "���������� ����� ������ ����� �������������� ��������, ����� �������� ����� �� ������������");
		id = logs::input();
	}
	roll2d6(bonus, &result);
	if(result >= 13) {
		logs::add("��� �������. �� ��� �� ����� ��������, �������� ������� ��� ���������� ��, ��� �� ����������. ������ ������ �������. �������� ������� �������. �� ��������� �� ��� ������.");
		logs::next();
		passtime(60);
		return true;
	}
	if(result >= 10 && specialized) {
		logs::add("�� ����� ��������, ������� ����� ������� ��, ��� ��� ����.");
		logs::add("��������� ������������������� �����, ������ ������ �������. �������� ������� �������.");
		logs::next();
		passtime(3 * 60);
		return true;
	}
	if(result >= 7) {
		logs::add("������ ������ ������� �� ����� ��������, ������� ����� ������� ��, ��� ��� ����.");
		if(market_class == 0)
			logs::add("����� ��� ������������ ���������, ������� �� ������ ��������� ������ ���� �� ����� ����������.");
		else
			logs::add("����� ��������� ���� ������� �� ��������� ���� ������� ������ �������.");
		logs::next();
		passtime(8 * 60);
		return true;
	}
	passtime(24 * 60 * 2);
	logs::add("�� ����������� ���� ������� �����. �� ��� ���� ������� ����� ��, ��� ��� ���� ����������� ��������. ������ ���� ���� �� ������� ��� �����.");
	logs::next();
	return false;
}

void hero::acquisition(assets& ast, assets_groups group, int market_class) {
	asset_s values[64];
	auto assets_class = ast.getmarket();
	if(ast && assets_class < 3)
		assets_class = assets_class + 1;
	if(assets_class > market_class) {
		logs::add("%1 �� ���� ����� ��������, ����� ����� ����� �������������.", getstr(group));
		logs::next();
	}
	auto value_count = assets::select(values, group, assets_class);
	for(int i = 0; i < value_count; i++)
		logs::add(values[i], getstr(values[i]));
	if(value_count) {
		int id;
		logs::add(1000, "������ �� ����.");
		if(group == GroupCrew)
			id = logs::input(true, false, "%1 ����� ������������� ��� ����������?", getstr(group));
		else
			id = logs::input(true, false, "%1 ����� ������ ��� ����������?", getstr(group));
		if(id == 1000)
			return;
		if(acquisition(assets_class, true))
			ast.set((asset_s)id);
	} else {
		logs::add("�� ������� ����� ��� ������� ��� �����, ������� �� ������ ����������.");
		logs::next();
	}
}

void hero::acquisition(int market_class) {
	int id;
	for(auto n = GroupWeapon; n <= GroupCargo; n = (assets_groups)(n + 1)) {
		if(n == GroupCargo && !spaceship)
			continue;
		logs::add(n, getstr(n));
	}
	id = logs::input(true, false, "��� ������ �� ������ ����������?");
	if(id == 1000)
		return;
	auto group = static_cast<assets_groups>(id);
	switch(group) {
	case GroupWeapon:
		acquisition(weapon, group, market_class);
		break;
	case GroupAttire:
		acquisition(attire, group, market_class);
		break;
	case GroupCrew:
		acquisition(crew, group, market_class);
		break;
	case GroupVehicle:
		acquisition(vehicle, group, market_class);
		break;
	case GroupKit:
		logs::add("����� ��� ������������ ��� ����������?");
		for(auto i = BroadcastKit; i <= WildernessKit; i = (kit_s)(i + 1))
			logs::add(i, assets_kits_text[i][1]);
		id = logs::input();
		logs::add("������� ��������� ��������� � ������������� � ������������� �� ����� �� ��� ������.");
		if(acquisition(1, false))
			set((kit_s)id);
		break;
	case GroupCargo:
		logs::add("�� ������ ��������� ��� ����� �������� ��������?");
		if(logs::yesno()) {
		}
		break;
	}
}

bool hero::openfire(assets& enemy) {
	auto result = roll(OpenFire);
	auto damage = enemy.getseverity();
	logs::add("�� ������� ����� �� �����.");
	logs::add("%1 ���������� � ������� � ������ �������� �������� � ���� �������.", enemy.getname());
	logs::add("��������� ����� �� ������ ���� � �����.");
	if(result == Fail) {
		logs::add("�� ��� �������� ����� ������. ������ ���� �� ���������� ������, ���� ����������� ����� ����.");
		braceimpact(damage);
		logs::add("�� �������� ������ ���� �� ��������� ���� ��������.");
		return false;
	} else if(result == PartialSuccess) {
		logs::add("�������, ��������� ���� ��� �����������.");
		enemy.count = enemy.count / 2;
		braceimpact(damage);
	} else {
		// ����� �� ����
		logs::add("�������, �� ����������� �� ����.");
		enemy.count = 0;
	}
	if(enemy.count < 0)
		enemy.count = 0;
	return true;
}

void hero::braceimpact(severity_s value) {
	int result;
	roll2d6(getarmor(), &result, false);
	if(result >= 13) {
		logs::add("����� ������� ���� �� ����.");
		value = (severity_s)imax(value - 2, 0);
	} else if(result >= 10) {
		logs::add("����� �������� ����.");
		value = (severity_s)imax(value - 1, 0);
	} else if(result >= 7) {
		// Nothing to do
	} else
		value = (severity_s)imin(value + 1, 4);
	value = (severity_s)imax(0, imin((int)value, 5));
	value = set(value);
	switch(value) {
	case Minor: logs::add("�� ���������� �������."); break;
	case Major: logs::add("������ � ��� �� ���� ����."); break;
	case Severe: logs::add("� ��� � ���� �����."); break;
	case Critical: logs::add("��� �������� ����."); break;
	case Fatal: logs::add("��� �������� �� �����."); break;
	}
	damages[0].set(value);
}

void hero::passtime(unsigned minutes) {
	current_minute += minutes;
}