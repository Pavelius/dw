#include "main.h"

class_info class_data[] = {{},
{"cleric", "клерик", 8, 2,
{LightArmorProficiency, MediumArmorProficiency, ShieldProficiency, SimpleWeaponProficiency, SaveWisdow, SaveCharisma},
{Wisdow, Charisma, Strenght, Constitution, Dexterity, Intellegence},
{History, Insight, Medicine, Persuasion, Religion},
},
{"fighter", "воин", 10, 2,
{LightArmorProficiency, MediumArmorProficiency, HeavyArmorProficiency, ShieldProficiency, SimpleWeaponProficiency, MartialWeaponProfiency, SaveStrenght, SaveConstitution},
{Strenght, Constitution, Dexterity, Wisdow, Intellegence, Charisma},
{Acrobatics, AnimalHandling, Athletics, History, Insight, Intimidation, Perception, Survival},
},
{"rogue", "брод€га", 8, 4,
{LightArmorProficiency, SaveDexterity, SaveIntellegence, RogueWeaponTrain},
{Dexterity, Intellegence, Strenght, Charisma, Constitution, Wisdow},
{Acrobatics, Athletics, Deception, Insight, Intimidation, Investigation, Perception, Performance, Persuasion, SleightOfHands, Stealth},
},
{"wizard", "волшебник", 6, 2,
{SaveWisdow, SaveIntellegence},
{Intellegence, Wisdow, Dexterity, Strenght, Charisma, Constitution},
{Arcana, History, Insight, Investigation, Medicine, Religion},
}};
assert_enum(class, Wizard);
getstr_enum(class);