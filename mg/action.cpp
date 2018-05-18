#include "main.h"

static struct action_i {
	const char*	id;
	const char*	name;
	const char*	nameby;
	action_roll_s rolls[Maneuver + 1];
} action_data[] = {{"Attack", "Атака", "атакует", {IndependedRoll, VersusRoll, IndependedRoll, VersusRoll}},
{"Defend", "Защита", "защищается", {VersusRoll, IndependedRoll, NoRoll, VersusRoll}},
{"Feint", "Финт", "использует финт", {NoRoll, IndependedRoll, VersusRoll, IndependedRoll}},
{"Maneuver", "Маневр", "маневрирует", {VersusRoll, VersusRoll, IndependedRoll, IndependedRoll}},
};
assert_enum(action, Maneuver);
getstr_enum(action);

action_roll_s hero::get(action_s player, action_s opposition) {
	return action_data[player].rolls[opposition];
}

const char* hero::getnameby(action_s value) {
	return action_data[value].nameby;
}