#include "main.h"

unsigned char equipment::getexpend() const {
	switch(manufactor) {
	case SardKar: return 50;
	default: return 40; // ���� ������� ������������ ��-���������
	}
}