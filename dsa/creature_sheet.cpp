#include "main.h"

class dialog_sheet : public dialog {
	
	creature&	player;

	int ability(int x, int y, int width) const {
		auto y0 = y;
		y += headof(x, y, width, "Атрибуты");
		for(auto a = Courage; a <= Strenght; a = (ability_s)(a + 1)) {
			y += detail(x, y, width, bsmeta<abilityi>::elements[a].name, 48, player.get(a));
		}
		return y - y0;
	}
	int parameters(int x, int y, int width) const {
		auto y0 = y;
		y += headof(x, y, width, "Параметры");
		for(auto a = LE; a <= Level; a = (ability_s)(a + 1)) {
			auto v1 = player.get(a);
			if(a == LE || a == AE) {
				auto v2 = player.getmaximum(a);
				if(!v2)
					continue;
				y += detail(x, y, width, bsmeta<abilityi>::elements[a].name, 48, v1, v2);
			} else if(a == PVC) {
				if(!v1)
					continue;
				y += detail(x, y, width, bsmeta<abilityi>::elements[a].name, 48, v1);
			} else
				y += detail(x, y, width, bsmeta<abilityi>::elements[a].name, 48, v1);
		}
		return y - y0;
	}
	void clicking(int id, int param) {
		if(id == Strenght) {

		}
	}
	int render(int x, int y, int width) const override {
		auto y0 = y;
		y += ability(x, y, 200);
		y += parameters(x, y, 200);
		return y - y0;
	}

public:

	dialog_sheet(creature& player) : player(player) {}

};

void creature::sheet() {
	dialog_sheet ctx(*this);
	ctx.choose();
}