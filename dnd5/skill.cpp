#include "main.h"

struct skill_info {
	const char*			id;
	const char*			name;
} skill_data[] = {{"athletics", "атлетика"},
{"acrobatics", "акробатика"},
{"sleight of hands", "ловкость рук"},
{"stealth", "скрытность"},
{"arcana", "тайное"},
{"history", "история"},
{"investigation", "расследование"},
{"nature", "природа"},
{"religion", "религия"},
{"animal handling", "приручение животных"},
{"insight", "проницательность"},
{"medicine", "медицина"},
{"perception", "восприятие"},
{"survival", "выживание"},
{"deception", "обман"},
{"intimidation", "запугивание"},
{"performance", "артистизм"},
{"persuasion", "убеждение"},
};
assert_enum(skill, Persuasion);
getstr_enum(skill);