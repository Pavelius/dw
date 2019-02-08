#include "main.h"

static struct name_info {
	race_s			kin;
	gender_s		gender;
	const char*		name;
} name_data[] = {{Human, Male, "Бринд"},
{Human, Male, "Хардар"},
{Human, Male, "Оровальд"},
{Human, Male, "Песиндер"},
{Human, Male, "Вергивел"},
{Human, Female, "Гармельда"},
{Human, Female, "Халинд"},
{Human, Female, "Нирмена"},
{Human, Female, "Синдия"},
{Human, Female, "Талина"},
{Elf, Male, "Дорм"},
{Elf, Male, "Харакронд"},
{Elf, Male, "Оргодан"},
{Elf, Male, "Раднар"},
{Elf, Male, "Вергелло"},
{Elf, Female, "Блейнелла"},
{Elf, Female, "Эрими"},
{Elf, Female, "Крибленда"},
{Elf, Female, "Саймени"},
{Elf, Female, "Воровалья"},
{HalfElf, Male, "Гаверин"},
{HalfElf, Male, "Халиван"},
{HalfElf, Male, "Хордеран"},
{HalfElf, Male, "Жирман"},
{HalfElf, Male, "Сандмэн"},
{HalfElf, Female, "Гивена"},
{HalfElf, Female, "Холерва"},
{HalfElf, Female, "Корена"},
{HalfElf, Female, "Сонилия"},
{HalfElf, Female, "Тримелия"},
{Dwarf, Male, "Бодло"},
{Dwarf, Male, "Гандемэн"},
{Dwarf, Male, "Харгамар"},
{Dwarf, Male, "Тиргар"},
{Dwarf, Male, "Вульфред"},
{Dwarf, Female, "Хамхельда"},
{Dwarf, Female, "Холмиста"},
{Dwarf, Female, "Скоринда"},
{Dwarf, Female, "Торбения"},
{Dwarf, Female, "Тринди"},
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