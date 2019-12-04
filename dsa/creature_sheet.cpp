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
	void clicking(int id, int param) {
		if(id == Strenght) {

		}
	}
	int render(int x, int y, int width) const override {
		return ability(x, y, 200);
	}

public:

	dialog_sheet(creature& player) : player(player) {}

};

void creature::sheet() {
	dialog_sheet ctx(*this);
	ctx.choose();
}