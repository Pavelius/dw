#include "main.h"

BSDATA(actioni) = {{"Attack", "�����", "�������", {IndependedRoll, VersusRoll, IndependedRoll, VersusRoll}},
{"Defend", "������", "����������", {VersusRoll, IndependedRoll, NoRoll, VersusRoll}},
{"Feint", "����", "���������� ����", {NoRoll, IndependedRoll, VersusRoll, IndependedRoll}},
{"Maneuver", "������", "�����������", {VersusRoll, VersusRoll, IndependedRoll, IndependedRoll}},
};
assert_enum(actioni, Maneuver)

action_roll_s hero::get(action_s player, action_s opposition) {
	return bsdata<actioni>::elements[player].rolls[opposition];
}

const char* hero::getnameby(action_s value) {
	return bsdata<actioni>::elements[value].nameby;
}