#include "main.h"

actioni bsmeta<actioni>::elements[] = {{"MakeAttack", "Атаковать врага", HostileCreature, "Выбирайте цель"},
{"MakeMove", "Двигаться", Posable},
{"ChangeWeapon", "Сменить оружие"},
{"Dash", "Рывок вперед"},
{"Dodge", "Уклоняться от ударов врага"},
{"Disengage", "Маневрировать, уклоняясь от ударов"},
{"Hide", "Попытаться спрятаться"},
{"Help", "Помочь союзнику", FriendlyCreature, "Кому хотите помочь?"},
{"Search", "Обыскать это место"},
{"StandUp", "Подняться на ноги"},
};
assert_enum(action, StandUp);

action_s actioni::getid() const {
	return action_s(this - bsmeta<actioni>::elements);
}