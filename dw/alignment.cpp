#include "main.h"

struct alignment_info {
	const char* id;
	const char* name;
} alignment_data[] = {{"Good", "������"},
{"Lawful", "���������������"},
{"Neutral", "�����������"},
{"Chaotic", "���������"},
{"Evil", "����"},
};
BSENUM(alignment, Evil);