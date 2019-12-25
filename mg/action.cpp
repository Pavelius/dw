#include "main.h"

actioni bsmeta<actioni>::elements[] = {{"Attack", "�����", "�������", {IndependedRoll, VersusRoll, IndependedRoll, VersusRoll}},
{"Defend", "������", "����������", {VersusRoll, IndependedRoll, NoRoll, VersusRoll}},
{"Feint", "����", "���������� ����", {NoRoll, IndependedRoll, VersusRoll, IndependedRoll}},
{"Maneuver", "������", "�����������", {VersusRoll, VersusRoll, IndependedRoll, IndependedRoll}},
};
assert_enum(action, Maneuver);

action_roll_s hero::get(action_s player, action_s opposition) {
	return bsmeta<actioni>::elements[player].rolls[opposition];
}

const char* hero::getnameby(action_s value) {
	return bsmeta<actioni>::elements[value].nameby;
}