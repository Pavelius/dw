#include "main.h"

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

classi bsmeta<classi>::elements[] = {{},
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

void creature::apply(class_s id, bool interactive) {
	auto& ci = bsmeta<classi>::elements[id];
	auto level = ++classes[id];
	if(level == 1 && getlevel() == 1)
		hp_rolled = ci.hd;
	else
		hp_rolled += xrand(1, ci.hd);
	for(auto e : ci.traits)
		set(e);
	apply(id, level, interactive);
}

static void add_equipment(stringbuilder& sb, creature& player, const variant* elements) {
	const unsigned size = 8;
	for(unsigned i = 0; i < size; i++) {
		if(!elements[i])
			continue;
		if(i>0) {
			if(i == (size-1) || elements[i+1].type==NoVariant)
				sb.add(" и ");
			else
				sb.add(", ");
		}
		if(elements[i].type == Feat) {
			switch(elements[i].value) {
			case MartialWeaponProfiency:
				sb.add("Любое боевое оружие");
				continue;
			case SimpleWeaponProficiency:
				sb.add("Любое простое оружие");
				continue;
			}
		}
		sb.add(getstr(elements[i]));
	}
}

void creature::choose_equipment(class_s type, bool interactive) {
	char temp[512]; stringbuilder sc(temp);
	for(const auto& e : bsmeta<classi>::elements[type].equipment) {
		variant elements[3][8]; memset(elements, 0, sizeof(elements));
		// В каждом шаге предварительно обработаем все вариаты
		// исключив в них преметы, которыми нельзя пользоваться
		unsigned i0 = 0;
		for(auto i = 0; i < sizeof(e) / sizeof(e[0]); i++) {
			if(!e[i][0])
				break;
			auto p = elements[i0];
			auto pe = p + sizeof(elements[i0]) / sizeof(elements[i0][0]);
			for(unsigned j = 0; j < sizeof(e[0]) / sizeof(e[0][0]); j++)
				p = add(p, pe, e[i][j]);
			if(elements[i0][0])
				i0++;
		}
		// Теперь опросим по списку
		for(auto i = 0; i < sizeof(elements) / sizeof(elements[0]); i++) {
			if(!elements[i][0])
				break;
			sc.clear();
			add_equipment(sc, *this, elements[i]);
			an.add(i, temp);
		}
		if(!an)
			continue;
		auto i = an.choose(interactive, false, "Какую экипировку вы выбирете?");
		for(auto it : e[i]) {
			switch(it.type) {
			case Item: add((item_s)it.value); break;
			case Feat: add(choose_absent_item((feat_s)it.value, "Выбирайте точный предмет", interactive)); break;
			default: break;
			}
		}
	}
}