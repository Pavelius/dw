#include "main.h"

void hero::sheet() {
	logs::add("###%1 %2 (%3i �������)", getname(), getstr(type), level);
	logs::add(1, "��������� ��������.");
	auto id = whatdo();
	switch(id) {
	case 1: return;
	}
}