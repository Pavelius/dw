#include "main.h"
#include "point.h"

enum shape_s : unsigned char {
	RoomSquare20x20, RoomSquare40x40, RoomSquare80x20, RoomSquare20x40,
	RoomCircle40,
	Passage10,
};

// 5 = менее 2 метров
// 10 = 4 метра
// 20 = 8 метров
// 40 = 16 метров
struct shapei {
	const char*		name;
	point			size;
};

shapei bsmeta<shapei>::elements[] = {{"комната размеров 8 на 8 метров", {8, 8}},
{"комната размеров 16 на 16 метров", {16, 16}},
{"зал размером 32 на 8 метров", {32, 8}},
{"комната размером 8 на 16 метров", {8, 16}},
{"круглая комната диаметром 16 метров", {16, 16}},
{"проход шириной 4 метра", {4}},
};
assert_enum(shape, Passage10);