#include "main.h"

struct skill_info {
	const char*			id;
	const char*			name;
} skill_data[] = {{"Athletics", "атлетика"},
{"Acrobatics", "акробатика"},
{"Sleight of hands", "ловкость рук"},
{"Stealth", "скрытность"},
{"Arcana", "тайное"},
{"History", "история"},
{"Investigation", "расследование"},
{"Nature", "природа"},
{"Religion", "религия"},
{"Animal handling", "приручение животных"},
{"Insight", "проницательность"},
{"Medicine", "медицина"},
{"Perception", "восприятие"},
{"Survival", "выживание"},
{"Deception", "обман"},
{"Intimidation", "запугивание"},
{"Performance", "артистизм"},
{"Persuasion", "убеждение"},
};
assert_enum(skill, Persuasion);
getstr_enum(skill);