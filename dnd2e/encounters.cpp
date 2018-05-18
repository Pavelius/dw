#include "main.h"

enum encounter_s : unsigned char {
	Attack, Hide, Retreat, Wait, Conversation
};

static void roll_party_surprise(int bonus) {
	for(auto player : party) {
		if(!player->isready())
			continue;
		player->surprise(bonus);
	}
}

void game::encounter() {
	// Create group of monsters
	auto type = ElfFolk;
	character monsters(type);
	monsters.setcount(xrand(2, 12));
	encounter(monsters);
}

void game::encounter(character& monsters) {
	char temp[260];
	// Test surprise
	monsters.surprise(getminimum(&character::getsurpriseother));
	roll_party_surprise(monsters.getsurpriseother());
	// Promt
	logs::add("Внезапно, впереди вы заметили %1.", monsters.getname(temp, zendof(temp)));
	while(true) {
		//switch(reaction) {
		//case Hostile:
		//	logs::add("Достав оружие, %1 бросились в атаку.", monsters.getname(temp));
		//	logs::add(Attack, "Достать оружие и приготовится к битве.");
		//	break;
		//case Threatening:
		//	monsters.say("- Пошли прочь отсюда! - воскликнул%а %герой. - Здесь наша земля. Убирайтесь прочь или умрете!");
		//	askencounter();
		//	break;
		//case Flight:
		//	logs::add("Только лишь завидив вас они бросились бежать.");
		//	askencounter();
		//	break;
		//case Cautions:
		//	logs::add("Они тоже заметили вас и остановились в нерешительности. Видно как они не доверяют вам.");
		//	askencounter();
		//	break;
		//case Friendly:
		//	logs::add("Они заметили вас и было заметно их дружелюбное отношение.");
		//	askencounter();
		//	break;
		//default:
		//	logs::add("Они тоже заметили вас и остановились в нерешительности.");
		//	askencounter();
		//	break;
		//}
		auto id = (encounter_s)logs::inputsg(true, true, "Что будете делать?");
		switch(id) {
		case Attack:
			logs::add("Достав оружие вы бросились на %1.", monsters.getname(temp, zendof(temp)));
			combat(true, monsters);
			break;
		}
		break;
	}
}