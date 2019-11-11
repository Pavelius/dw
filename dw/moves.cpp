#include "main.h"

movei bsmeta<movei>::elements[] = {{"ArcaneArt"},
{"BardicLore"},
{"CharmingAndOpen"},
{"PortInTheStorm", "������� �� ����� ����"},
{"Deity", "��������"},
{"DivineGuidance", "������ ���������������"},
{"TurnUndead", "��������� �������"},
{"Commune", ""},
{"CastASpell", ""},
{"BornOfTheSoil", ""},
{"ByNatureSustained", ""},
{"SpiritTongue", ""},
{"Shapeshifter", ""},
{"StudiedEssence", ""},
{"BendBarsLiftGates", ""},
{"Armored", ""},
{"SignatureWeapon", "������� ������"},
{"LayOnHands", "���������� ���"},
{"IAmTheLaw", "� ���� �����"},
{"Quest", "������"},
{"HuntAndTrack", ""},
{"CalledShot", ""},
{"AnimalCompanion", ""},
{"Command", ""},
{"TrapExpert", "������� �� ��������", Dexterity},
{"TricksOfTheTrade", "������ ��������", Dexterity},
{"Backstab", "���� � �����", Dexterity},
{"FlexibleMorals", "������ ������"},
{"Poisoner", ""},
{"Spellbook", "����� ����������"},
{"PrepareSpells", ""},
{"SpellDefense", ""},
{"Ritual", "������"},
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
{"HackAndSlash", "������ � �������", Strenght},
{"Volley", "���� ����", Dexterity},
{"DefyDangerStrenght", "", Strenght},
{"DefyDangerDexterity", "", Dexterity},
{"DefyDangerConstitution", "", Constitution},
{"DefyDangerIntellegence", "", Intellegence},
{"DefyDangerWisdow", "", Wisdow},
{"DefyDangerCharisma", "", Charisma},
{"Parley", "", Charisma},
{"SpoutLore", "���������� � ������", Intellegence},
{"DiscernRealities", "������� ����������", Wisdow},
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