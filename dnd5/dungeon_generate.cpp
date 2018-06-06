#include "main.h"

enum shape_s : unsigned char {
	RoomSquare20x20, RoomSquare40x40, RoomSquare80x20, RoomSquare20x40,
	RoomCircle40,
	Passage10,
};

// 5 = ����� 2 ������
// 10 = 4 �����
// 20 = 8 ������
// 40 = 16 ������
static struct shape_info {
	const char*		name;
} shape_data[] = {{"������� �������� 8 �� 8 ������"},
{"������� �������� 16 �� 16 ������"}, {"��� �������� 32 �� 8 ������"}, {"������� �������� 8 �� 16 ������"},
{"������� ������� ��������� 16 ������"},
{"������ ������� 4 �����"},
};
assert_enum(shape, Passage10);
getstr_enum(shape);