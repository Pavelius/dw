#include "main.h"

void hero::sheet() {
	logs::add("###%1 %2 (%3i уровень)", getname(), getstr(type), level);
	logs::add(1, "Закончить просмотр.");
	auto id = whatdo();
	switch(id) {
	case 1: return;
	}
}