#include "main.h"

struct skill_info {
	const char*			id;
	const char*			name;
} skill_data[] = {{"No skill", "Нет навыка"},
{"Athletics", "Атлетика"},
{"Acrobatics", "Акробатика"},
{"Sleight of hands", "Ловкость рук"},
{"Stealth", "Скрытность"},
{"Arcana", "Тайный знания"},
{"History", "История"},
{"Investigation", "Анализ"},
{"Nature", "Природа"},
{"Religion", "Религия"},
{"Animal handling", "Дрессировка"},
{"Insight", "Интуиция"},
{"Medicine", "Медицина"},
{"Perception", "Восприятие"},
{"Survival", "Выживание"},
{"Deception", "Обман"},
{"Intimidation", "Запугивание"},
{"Performance", "Представление"},
{"Persuasion", "Убеждение"},
};
assert_enum(skill, Persuasion);
getstr_enum(skill);