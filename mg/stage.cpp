#include "main.h"

static stage border_scent_scientist = {
	"������ ���������� ��������� ���������� �����.",
	0, 0,
	Scientist
};
static stage border_scent_pathfinder = {
	"��� ����� ���������� �� ������� �����, � ������� ����������� ����� ���� ����� �������� ����� ��� ������� ����������.",
	&border_scent_scientist, 0,
	Pathfinder
};

void hero::quest(stage* start) {
	while(start) {
		if(passtest(start->skill, 4))
			start = start->next;
		else {
			// ��������� ����� ������
		}
	}
}