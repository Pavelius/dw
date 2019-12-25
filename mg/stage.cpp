#include "main.h"

struct stage {
	const char*	text;
	skill_s		skill;
	item_s		tools[8];
	explicit operator bool() const { return text != 0; }
};
static stage border_scent[] = {{"��� ����� ���������� �� ������� �����, � ������� ����������� ����� ���� ����� �������� ����� ��� ������� ����������. ���������� ��������� �� ������� ��������� ������ � ������ ��� ����� ����� ����� �����.", Pathfinder},
{"������ �������� ����� ������� ����� ��� ���������� �����.", Scientist},
};
static struct stage_info {
	const char*	key;
	aref<stage>	value;
} stage_data[] = {
	{"border_scent", border_scent}
};

static aref<stage> find_quest(const char* quest_id) {
	for(auto& e : stage_data) {
		if(strcmp(e.key, quest_id) == 0)
			return e.value;
	}
	return {};
}

void hero::quest(const char* quest_id) {
	auto source = find_quest(quest_id);
	if(!source)
		return;
	for(auto& e : source) {
		sb.add(e.text);
		if(!passtest(e.skill, 4)) {
			// Fight is possible encounter
			fight(Squirrel);
		}
	}
}