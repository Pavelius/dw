#include "main.h"

BSDATA(actioni) = {{"Attack", "Атака", "атакует", {IndependedRoll, VersusRoll, IndependedRoll, VersusRoll}},
{"Defend", "Защита", "защищается", {VersusRoll, IndependedRoll, NoRoll, VersusRoll}},
{"Feint", "Финт", "использует финт", {NoRoll, IndependedRoll, VersusRoll, IndependedRoll}},
{"Maneuver", "Маневр", "маневрирует", {VersusRoll, VersusRoll, IndependedRoll, IndependedRoll}},
};
assert_enum(actioni, Maneuver)

action_roll_s hero::get(action_s player, action_s opposition) {
	return bsdata<actioni>::elements[player].rolls[opposition];
}

const char* hero::getnameby(action_s value) {
	return bsdata<actioni>::elements[value].nameby;
}