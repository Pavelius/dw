#include "main.h"

static movei hack_and_slash_opt[] = {{HackAndSlash, Success, "������� ��������� +1d6 �����.", {DamageOpponent, 106}, Damage},
{HackAndSlash, PartialSuccess, "������� ���� ����� � �� �������� ��������� �����.", DamageOpponent}
};
static movei moves[] = {{HackAndSlash, Success, "������ �������������, %����� ����� ����.", {Choose1, hack_and_slash_opt}},
{HackAndSlash, PartialSuccess, "%����� ����� ��������� ������ %���������, �� ��� ������ ������� �����.", DamageOpponent, Damage}
};

