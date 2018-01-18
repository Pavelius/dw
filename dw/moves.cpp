#include "main.h"

struct move_info {
	const char*		id;
	const char*		name;
	stat_s			stat;
} move_data[] = {
	{"Arcane Art"},
	{"Bardic Lore"},
	{"Charming and Open"},
	{"Port in The Storm", "Убежище во время бури"},
	{"Deity", "Божество"},
	{"Divine guidance", "Святое покровительство"},
	{"Turn Undead", "Отпугнуть мертвых"},
	{"Commune", ""},
	{"Cast a Spell", ""},
	{"Born of The Soil", ""},
	{"By Nature Sustained", ""},
	{"Spirit Tongue", ""},
	{"Shapeshifter", ""},
	{"Studied Essence", ""},
	{"Bend Bars Lift Gates", ""},
	{"Armored", ""},
	{"Signature Weapon", "Именное оружие"},
	{"Lay on Hands", "Возложение рук"},
	{"I am The Law", "Я есть закон"},
	{"Quest", "Миссия"},
	{"Hunt and Track", ""},
	{"Called Shot", ""},
	{"Animal Companion", ""},
	{"Command", ""},
	{"Trap Expert", "Эксперт по ловушкам", Dexterity},
	{"Tricks of The Trade", "Фокусы торговли"},
	{"Backstab", "Удар в спину"},
	{"Flexible Morals", "Гибкая мораль"},
	{"Poisoner", ""},
	{"Spellbook", "Книга заклинаний"},
	{"Prepare spells", ""},
	{"Spell defense", ""},
	{"Ritual", "Ритуал"},
	//
	{"Merciless", ""},
	{"Heirloom", ""},
	{"Improved Weapon", ""},
	{"Seeing Red", ""},
	{"Interrogator", ""},
	{"Scent of Blood", ""},
	{"Iron Hide", ""},
	{"Blacksmith", ""},
	{"Superior Warrior", ""},
	//
	{"Prodigy", ""},
	{"Empowered Magic", ""},
	{"Fount of Knowledge", ""},
	{"Known It All", ""},
	{"Expanded Spellbook", ""},
	{"Enchanter", ""},
	{"Logical", ""},
	{"Arcane Ward", ""},
	{"Counterspell", ""},
	{"Quick Study", ""},
	//
	{"Hack and Slash", ""},
	{"Defy Danger", "", Strenght},
	{"Defy Danger", "", Dexterity},
	{"Defy Danger", "", Constitution},
	{"Defy Danger", "", Intellegence},
	{"Defy Danger", "", Wisdow},
	{"Defy Danger", "", Charisma},
	{"Parley", "", Charisma},
	{"Spout Lore", "Покопаться в памяти", Intellegence},
	{"Discern Realities", "Изучить обстановку", Wisdow},
	{"Supply", "", Charisma},
	{"Show charsheet sheet", "Изучить листок персонажа"},
	{"Examine Feature", "Изучить осоенность поближе"},
	{"Go Back", "Двигаться назад"},
	{"Go Next", "Двигаться дальше"},
	{"Make Camp", "Сделать привал"},
	{"All run away", "Всем бежать отсюда прочь"},
};
assert_enum(move, RunAway);
getstr_enum(move);

bool game::isnoplayer(move_s id) {
	if(id >= MakeCamp)
		return true;
	return false;
}

stat_s hero::getstat(move_s id) const {
	switch(id) {
	case CastASpell:
		return (type == Wizard) ? Intellegence : Wisdow;
	default:
		return move_data[id].stat;
	}
}