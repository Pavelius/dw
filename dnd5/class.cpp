#include "main.h"

static struct pack_info {
	const char*			id;
	const char*			name;
	item_s				items[4];
} pack_data[] = {{"Burglar's Pack", "Набор взломщика", {Rope, HammerLight, Ration, Waterskin}},
{"Diplomat's Pack", "Набор дипломата", {Book, CalligrapherSupplies, Parchment, Map}},
{"Dungeoneer's Pack", "Набор исследователя подземелий", {Rope, Torches, Ration, Waterskin}},
{"Entertainer's Pack", "Набор артиста", {Bedroll, DisguiseKit, Ration, Waterskin}},
{"Explorer's Pack", "Набор приключенца", {Rope, Bedroll, Ration, Waterskin}},
{"Priest's Pack", "Набор священника", {Bedroll, Ration, Waterskin}},
{"Scholar's Pack", "Набор ученого", {Book, CalligrapherSupplies, Parchment, Dagger}},
};
getstr_enum(pack);
assert_enum(pack, LastPack);

static equipment fighter_equipment[] = {{{ChainMail}, {LeatherArmour, Longbow}},
{{MartialWeaponProfiency, Shield}, {MartialWeaponProfiency, MartialWeaponProfiency}},
{{CrossbowLight}, {Handaxe, Handaxe}},
{{DungeoneerPack}, {ExplorerPack}},
};
static equipment cleric_equipment[] = {{{Mace}, {Warhammer}},
{{ScaleMail}, {ChainMail}, {LeatherArmour}},
{{CrossbowLight}, {SimpleWeaponProficiency}},
{{PriestsPack}, {ExplorerPack}},
{{Shield, HolySymbol}}
};
static equipment rogue_equipment[] = {{{Rapier}, {Shortsword}},
{{Shortbow}, {Shortsword}},
{{BurglarPack}, {DungeoneerPack}, {ExplorerPack}},
{{PriestsPack}, {ExplorerPack}},
{{LeatherArmour, Dagger, Dagger, TheifTools}}
};
static equipment wizard_equipment[] = {{{Staff}, {Dagger}},
{{ComponentPounch}},
{{ExplorerPack}, {ScholarsPack}},
{{Spellbook}},
};

class_info class_data[] = {{},
{"cleric", "клерик", 8, 2,
{LightArmorProficiency, MediumArmorProficiency, ShieldProficiency, SimpleWeaponProficiency, SaveWisdow, SaveCharisma},
{Wisdow, Charisma, Strenght, Constitution, Dexterity, Intellegence},
{History, Insight, Medicine, Persuasion, Religion},
cleric_equipment,
},
{"fighter", "воин", 10, 2,
{LightArmorProficiency, MediumArmorProficiency, HeavyArmorProficiency, ShieldProficiency, SimpleWeaponProficiency, MartialWeaponProfiency, SaveStrenght, SaveConstitution},
{Strenght, Constitution, Dexterity, Wisdow, Intellegence, Charisma},
{Acrobatics, AnimalHandling, Athletics, History, Insight, Intimidation, Perception, Survival},
fighter_equipment,
},
{"rogue", "бродяга", 8, 4,
{LightArmorProficiency, SaveDexterity, SaveIntellegence, RogueWeaponTrain},
{Dexterity, Intellegence, Strenght, Charisma, Constitution, Wisdow},
{Acrobatics, Athletics, Deception, Insight, Intimidation, Investigation, Perception, Performance, Persuasion, SleightOfHands, Stealth},
rogue_equipment,
},
{"wizard", "волшебник", 6, 2,
{SaveWisdow, SaveIntellegence},
{Intellegence, Wisdow, Dexterity, Strenght, Charisma, Constitution},
{Arcana, History, Insight, Investigation, Medicine, Religion},
wizard_equipment,
}};
assert_enum(class, Wizard);
getstr_enum(class);

void creature::apply(class_s id, bool interactive) {
	auto level = ++classes[id];
	if(level == 1 && getlevel() == 1)
		hp_rolled = class_data[id].hd;
	else
		hp_rolled += xrand(1, class_data[id].hd);
	for(auto e : class_data[id].traits)
		set(e);
	apply(id, level, interactive);
}

static const char* getequipment(char* result, const char* result_maximum, creature& player, const variant* elements) {
	result[0] = 0;
	const unsigned size = 8;
	for(unsigned i = 0; i < size; i++) {
		if(!elements[i])
			continue;
		if(i>0) {
			if(i == (size-1) || elements[i+1].type==NoVariant)
				szprints(zend(result), result_maximum, " и ");
			else
				szprints(zend(result), result_maximum, ", ");
		}
		if(elements[i].type == Feat) {
			switch(elements[i].feat) {
			case MartialWeaponProfiency:
				szprints(zend(result), result_maximum, "Любое боевое оружие");
				continue;
			case SimpleWeaponProficiency:
				szprints(zend(result), result_maximum, "Любое простое оружие");
				continue;
			}
		}
		szprints(zend(result), result_maximum, getstr(elements[i]));
	}
	return result;
}

static variant* addequipment(const creature& player, variant* p, variant it) {
	if(!it)
		return p;
	switch(it.type) {
	case Item:
		if(!player.isproficient(it.item))
			return p;
		break;
	case Feat:
		if(!player.is(it.feat))
			return p;
		break;
	case Pack:
		for(auto e : pack_data[it.pack].items)
			p = addequipment(player, p, e);
		return p;
	}
	*p++ = it;
	return p;
}

void creature::choose_equipment(class_s type, bool interactive) {
	char temp[512];
	for(const auto& e : class_data[type].equipment) {
		variant elements[3][8]; memset(elements, 0, sizeof(elements));
		// В каждом шаге предварительно обработаем все вариаты
		// исключив в них преметы, которыми нельзя пользоваться
		unsigned i0 = 0;
		for(auto i = 0; i < sizeof(e) / sizeof(e[0]); i++) {
			if(!e[i][0])
				break;
			auto p = elements[i0];
			for(unsigned j = 0; j < sizeof(e[0]) / sizeof(e[0][0]); j++)
				p = addequipment(*this, p, e[i][j]);
			if(elements[i0][0])
				i0++;
		}
		// Теперь опросим по списку
		for(auto i = 0; i < sizeof(elements) / sizeof(elements[0]); i++) {
			if(!elements[i][0])
				break;
			logs::add(i, getequipment(temp, zendof(temp), *this, elements[i]));
		}
		if(logs::getcount() == 0)
			continue;
		auto i = logs::input(interactive, false, "Какую экипировку вы выбирете?");
		for(auto it : e[i]) {
			switch(it.type) {
			case Item: add(it.item); break;
			case Feat: add(choose_absent_item(it.feat, "Выбирайте точный предмет", interactive)); break;
			default: break;
			}
		}
	}
}