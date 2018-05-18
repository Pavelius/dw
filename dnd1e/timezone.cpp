#include "main.h"

static struct timezone_i {
	const char*	id;
	const char*	name;
	const char*	become;
} timezone_data[] = {
	{"Morning", "����", "��������� ����."},
	{"Noon", "�������", "�������� �������."},
	{"Afternoon", "����� �����", "�������� ����."},
	{"Evening", "�����", "������� �����."},
	{"Midnight", "�������", "������� �������."},
	{"Night", "�������� ����", "������ �������� ����."},
};

void scene::change(bool interactive, timezone_s& timezone) {
	auto tz = getzone();
	if(tz != timezone) {
		if(interactive)
			logs::add(timezone_data[tz].become);
		timezone = tz;
	}
}