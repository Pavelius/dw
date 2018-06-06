#include "main.h"

enum shape_s : unsigned char {
	RoomSquare20x20, RoomSquare40x40, RoomSquare80x20, RoomSquare20x40,
	RoomCircle40,
	Passage10,
};

// 5 = менее 2 метров
// 10 = 4 метра
// 20 = 8 метров
// 40 = 16 метров
static struct shape_info {
	const char*		name;
} shape_data[] = {{"комната размеров 8 на 8 метров"},
{"комната размеров 16 на 16 метров"}, {"зал размером 32 на 8 метров"}, {"комната размером 8 на 16 метров"},
{"круглая комната диаметром 16 метров"},
{"проход шириной 4 метра"},
};
assert_enum(shape, Passage10);
getstr_enum(shape);