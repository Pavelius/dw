#include "main.h"

movei bsmeta<movei>::elements[] = {{"ArcaneArt"},
{"BardicLore"},
{"CharmingAndOpen"},
{"PortInTheStorm", "Убежище во время бури"},
{"Deity", "Божество"},
{"DivineGuidance", "Святое покровительство"},
{"TurnUndead", "Отпугнуть мертвых"},
{"Commune", ""},
{"CastASpell", ""},
{"BornOfTheSoil", ""},
{"ByNatureSustained", ""},
{"SpiritTongue", ""},
{"Shapeshifter", ""},
{"StudiedEssence", ""},
{"BendBarsLiftGates", ""},
{"Armored", ""},
{"SignatureWeapon", "Именное оружие"},
{"LayOnHands", "Возложение рук"},
{"IAmTheLaw", "Я есть закон"},
{"Quest", "Миссия"},
{"HuntAndTrack", ""},
{"CalledShot", ""},
{"AnimalCompanion", ""},
{"Command", ""},
{"TrapExpert", "Эксперт по ловушкам", Dexterity},
{"TricksOfTheTrade", "Фокусы торговли", Dexterity},
{"Backstab", "Удар в спину", Dexterity},
{"FlexibleMorals", "Гибкая мораль"},
{"Poisoner", ""},
{"Spellbook", "Книга заклинаний"},
{"PrepareSpells", ""},
{"SpellDefense", ""},
{"Ritual", "Ритуал"},
//
{"Merciless", ""},
{"Heirloom", ""},
{"ImprovedWeapon", ""},
{"SeeingRed", ""},
{"Interrogator", ""},
{"ScentOfBlood", ""},
{"IronHide", ""},
{"Blacksmith", ""},
{"SuperiorWarrior", ""},
//
{"Prodigy", ""},
{"EmpoweredMagic", ""},
{"FountOfKnowledge", ""},
{"KnownItAll", ""},
{"ExpandedSpellbook", ""},
{"Enchanter", ""},
{"Logical", ""},
{"ArcaneWard", ""},
{"Counterspell", ""},
{"QuickStudy", ""},
//
{"HackAndSlash", "Рубить и крушить", Strenght},
{"Volley", "Дать залп", Dexterity},
{"DefyDangerStrenght", "", Strenght},
{"DefyDangerDexterity", "", Dexterity},
{"DefyDangerConstitution", "", Constitution},
{"DefyDangerIntellegence", "", Intellegence},
{"DefyDangerWisdow", "", Wisdow},
{"DefyDangerCharisma", "", Charisma},
{"Parley", "", Charisma},
{"SpoutLore", "Покопаться в памяти", Intellegence},
{"DiscernRealities", "Изучить обстановку", Wisdow},
{"Supply", "", Charisma},
};
assert_enum(move, Supply);

stat_s hero::getstat(move_s id) const {
	switch(id) {
	case CastASpell:
		return (type == Wizard) ? Intellegence : Wisdow;
	case HackAndSlash:
		if(weapon.is(Precise)
			|| (race == Elf && type == Fighter && weapon == SwordLong))
			return Dexterity;
		return Strenght;
	default:
		return bsmeta<movei>::elements[id].stat;
	}
}