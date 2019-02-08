#include "main.h"

static struct name_info {
	race_s			kin;
	gender_s		gender;
	const char*		name;
} name_data[] = {{Human, Male, "�����"},
{Human, Male, "������"},
{Human, Male, "��������"},
{Human, Male, "��������"},
{Human, Male, "��������"},
{Human, Female, "���������"},
{Human, Female, "������"},
{Human, Female, "�������"},
{Human, Female, "������"},
{Human, Female, "������"},
{Elf, Male, "����"},
{Elf, Male, "���������"},
{Elf, Male, "�������"},
{Elf, Male, "������"},
{Elf, Male, "��������"},
{Elf, Female, "���������"},
{Elf, Female, "�����"},
{Elf, Female, "���������"},
{Elf, Female, "�������"},
{Elf, Female, "���������"},
{HalfElf, Male, "�������"},
{HalfElf, Male, "�������"},
{HalfElf, Male, "��������"},
{HalfElf, Male, "������"},
{HalfElf, Male, "�������"},
{HalfElf, Female, "������"},
{HalfElf, Female, "�������"},
{HalfElf, Female, "������"},
{HalfElf, Female, "�������"},
{HalfElf, Female, "��������"},
{Dwarf, Male, "�����"},
{Dwarf, Male, "��������"},
{Dwarf, Male, "��������"},
{Dwarf, Male, "������"},
{Dwarf, Male, "��������"},
{Dwarf, Female, "���������"},
{Dwarf, Female, "��������"},
{Dwarf, Female, "��������"},
{Dwarf, Female, "��������"},
{Dwarf, Female, "������"},
};

static const char* choose_name(race_s kin, gender_s gender) {
	const char* source[sizeof(name_data) / sizeof(name_data[0])];
	auto pb = source;
	auto pe = source + (sizeof(name_data) / sizeof(name_data[0]));
	for(auto& e : name_data) {
		if(e.kin != kin || e.gender != gender)
			continue;
		if(pb < pe)
			*pb++ = e.name;
	}
	auto count = pb - source;
	if(!count)
		return 0;
	return source[rand() % count];
}

static const char* choose_name(gender_s gender) {
	const char* source[sizeof(name_data) / sizeof(name_data[0])];
	auto pb = source;
	auto pe = source + (sizeof(name_data) / sizeof(name_data[0]));
	for(auto& e : name_data) {
		if(e.gender != gender)
			continue;
		if(pb < pe)
			*pb++ = e.name;
	}
	auto count = pb - pe;
	if(!count)
		return 0;
	return source[rand() % count];
}

const char* character::getrandomname(race_s kin, gender_s gender) {
	auto p = choose_name(kin, gender);
	if(!p)
		p = choose_name(gender);
	return p;
}