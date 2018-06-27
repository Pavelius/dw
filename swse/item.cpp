#include "main.h"

static struct item_i {
	struct weapon {
		dice			damage;
		item_s			ammo;
	};
	struct armor {
		char			defences[Will + 1];
	};
	const char*			id;
	const char*			name;
	const char*			descritpion;
	feat_s				group;
	int					cost;
	int					weight;
	weapon				weapon_stats;
	cflags<wear_s>		slots;
	armor				armor_stats;
	bool				is(wear_s id) const { return slots.is(id); }
} item_data[] = {{"", "", ""},
{"Vibro Dagger", "�����-������", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Vibro Blade", "�����-���", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Vibro boatan", "�����-����", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Power spear", "������� �����", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Power staff", "�������-�����", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Vibro axe", "�����-�����", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Atlati", "������", "", WeaponProficiencyExoticWeapons, 0, 0, {}, {Melee}},
{"Emfy staff", "����-�����", "", WeaponProficiencyExoticWeapons, 0, 0, {}, {Melee}},
{"Cesta", "�����", "", WeaponProficiencyExoticWeapons, 0, 0, {}, {Melee}},
{"Light dagger", "�������� ������", "", WeaponProficiencyLightsabers, 0, 0, {{2, 6}}, {Melee}},
{"Light saber", "�������� ���", "", WeaponProficiencyLightsabers, 0, 0, {{2, 8}}, {Melee}},
{"Light saber, double", "�������� ���, �������", "", WeaponProficiencyLightsabers, 0, 0, {}, {Melee}},
// ������� ������
{"Knife", "���", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Club", "������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Baton", "���������� �����", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Mace", "������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Spear", "�����", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Boatan", "���� �� ��������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Staff", "�����", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Gauntlets", "��������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Gauntlets", "��������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
// ������������� ������
{"Firebat", "�������", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Plasmogun", "���������", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Granade Launcher", "����������", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Blaster Machinegun", "������� �������� �������", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Blaster Cannon", "�������� �����", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Rocket Launcher", "���������", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Blaster Turrel E-web", "�������� ��������� E-Web", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Mini Blaster", "����-�������", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Blaster", "�������", "", WeaponProficiencyPistols, 0, 0, {{3, 6}}, {Ranged}},
{"Sport Blaster", "���������� �������", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Ion Blaster", "���������� �������", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Gun", "��������", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Heavy Blaster", "������� �������", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Blaster Shotgun", "�������� �������", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Blaster Rifle", "�������� ��������", "", WeaponProficiencyRifles, 0, 0, {{3, 8}}, {Ranged}},
{"Sport Blaster Rifle", "���������� �������� ��������", "", WeaponProficiencyRifles, 0, 0, {{3, 6}}, {Ranged}},
{"Ion Rifle", "���������� ��������", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Rifle", "��������", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Blaster Minigun", "�������� �������", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Heavy Blaster Rifle", "������� �������� ��������", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Plasma Sphere", "���������� ���", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Ranged}},
{"Grenade", "���������� �������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Throwing}},
{"Grenade, ion", "���������� �������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Throwing}},
{"Grenade, shock", "���������� �������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Throwing}},
{"Thermal detonator", "���������� ���������", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Throwing}},
{"Sling", "�����", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Ranged}},
{"Bow", "���", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Ranged}},
{"Net", "����", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Ranged}},
// ����������
{"Trotil", "����������", "", WeaponProficiencySimpleWeapons},
{"Detonator", "���������", "", WeaponProficiencySimpleWeapons},
// ������ �����
{"Blast helmet and vest", "���� � ������", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Flight suit", "������ ������", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Armor, jumping", "����� � ��������� ����������", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Flight suit, armored", "������ ������, �������������", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Vondoon crabshell armor", "����������� �������� �����", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Armor, trooper", "����� ����������", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
// ������� �����
{"Ceremonial armour", "�������������� �����", "", ArmourProficienceMedium, 0, 0, {}, {Armor}},
{"Power suit", "������-�����", "", ArmourProficienceMedium, 0, 0, {}, {Armor}},
{"Combat armour", "������ �����", "", ArmourProficienceMedium, 0, 0, {}, {Armor}},
// ������� �����
{"Space suit, armored", "������������� ����������� ��������", "", ArmourProficienceHeavy, 0, 0, {}, {Armor}},
{"Combat armor, heavy", "������� ������ �����", "", ArmourProficienceHeavy, 0, 0, {}, {Armor}},
// ����������
{"Portable computer", "���������� ���������", ""},
{"Code cylinder", "�������������� �������", ""},
{"Credit chip", "��������� ��������", ""},
{"Holoproject", "������������", ""},
{"Data card", "������", ""},
{"Data pad", "��������� ���������", ""},
// ���������� �����������
{"Electro binocular", "�������-�������", "������� ��������� �������� ���������� � ����������, �������, ������� ��������, � ����� �������� ��������� ������� �������. ��������� ����� ���������� �� -1 �� ������ 10 ���������, ������ -5 �� ������ 10 ���������."},
{"Glow rod", "���������� �����", "���������� ����������, ������� ���������� �����, ���������� ��� ��������� 6 ���������."},
{"Fusion latern", "������� �������", "������� ������������ ���� � �����. �������� 6 ��������� �������."},
{"Audio-recorder", "��������", "������ 100 ����� ����� � �������� ��������."},
{"Holo-recorder", "������������", "������ 1 ��� ������������ ����������."},
{"Video-recorder", "�����������", "������ 10 ����� ����� � �������� ��������."},
{"Sensor pack", "����������� �����", "����������� ������� � ��������, ������������� ���������� � �����������. ��������� ����������� ��������� � �������� 1 ���������� �� ������� ���� �����, �������������, �������� ��� ������ �����."},
// �����
{"Comlink", "�������", ""},
{"Pocket decipher", "��������� ��������", "������� ����������, ������� ����� ���� ���������� � ������������ � ���������� ����������, ����� ��� �������."},
{"Voxbox", "��������� ����", ""},
};
assert_enum(item, VoxBox);
getstr_enum(item);

int item::getreflexes() const {
	return 0;
}

const dice& item::getdice() const {
	return item_data[type].weapon_stats.damage;
}

bool item::is(wear_s id) const {
	return item_data[type].is(id);
}

void item::clear() {
	type = NoItem;
	count = 0;
}

void item::setcount(int count) {
	if(!count)
		clear();
	else {
		if(count > 255)
			count = 255;
		this->count = count;
	}
}