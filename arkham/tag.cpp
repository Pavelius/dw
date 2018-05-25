#include "main.h"

static struct tag_info {
	const char*	id;
	const char*	name;
} tag_data[] = {{"Tome", ""},
{"PhysicalWeapon", "Это физическое оружие. "},
{"MagicalWeapon", "Это волшебное оружие. "},
{"CantStealOrLoose", "Этот предмет нельзя потерять, если вы этого не хотите и также его нельзя украсть. "},
{"CombatBonusTwoHand", "+1 к броску, если используется в двух руках. "},
{"ExhaustToRerollDie", "Переверни чтобы перебросить все кубики в броске. "},
{"ExhaustToEffect", "Чтобы выполнить бросок необходимо перевернуть. "},
{"CombatBonusVsUndead", "Дает +2 к броску если используется против мертвых. "},
{"DiscardAfterUse", "Сбрасывается после использования. "},
{"SixDoubleSuccess", "Каждая \"6\" в результате броска дает два успеха. "},
{"MarkTokenToDiscard", "Сбрось. "},
};
assert_enum(tag, MarkTokenToDiscard);
getstr_enum(tag)