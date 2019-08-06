#include "main.h"

void monsteri::sufferharm(int value, int pierce, int* result_value, int* killed) {
	if(count <= 0)
		return;
	auto a = getarmor();
	if(pierce > 0) {
		a -= pierce;
		if(a < 0)
			a = 0;
	}
	value -= a;
	if(value <= 0)
		return;
	if(result_value)
		*result_value = value;
	hits -= value;
	if(hits <= 0) {
		if(killed)
			*killed++;
		count--;
	}
	hits = 0;
}

void monsteri::heal(int value, int* result_value) {
	if(count <= 0)
		return;
	hits += value;
	if(hits > hits_maximum)
		hits = hits_maximum;
}

int	monsteri::rolldamage() const {
	if(!damage)
		return 0;
	auto r = 1 + (rand() % damage);
	r += getdamage();
	if(r < 0)
		r = 1;
	return r;
}

void monsteri::act(const char* format, ...) const {
	auto& sb = logs::getbuilder();
	sb.gender = getgender();
	sb.name = getname();
	sb.count = count;
	sb.addv(format, xva_start(format));
}