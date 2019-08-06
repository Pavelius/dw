#include "main.h"

void playeri::apply(effect_s effect, int param) {
	switch(effect) {
	case Damage: sufferharm(param); break;
	case DamageIA: sufferharm(param, 100); break;
	}
}