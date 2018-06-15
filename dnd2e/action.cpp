#include "main.h"

struct action {
	tag				id;
	const char*		text;
	duration_s		duration;
	unsigned		experience;
	void			(character::*success)();
	void			(character::*fail)();
	operator bool() const { return text != 0; }
};

static action forest_action[] = {{Tracking, "�������� ����� ����� ��������", Duration3Turn, 0},
{Wisdow, "���������� ����� �������� ����� � ��������", Duration4Hours, 0},
};