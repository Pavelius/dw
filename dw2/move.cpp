#include "main.h"

static movei hack_and_slash_opt[] = {{HackAndSlash, Success, "Нанести оппоненту +1d6 урона.", {DamageOpponent, 106}, Damage},
{HackAndSlash, PartialSuccess, "Нанести урон врагу и не получить ответного урона.", DamageOpponent}
};
static movei moves[] = {{HackAndSlash, Success, "Хорошо размахнувшись, %герой нанес удар.", {Choose1, hack_and_slash_opt}},
{HackAndSlash, PartialSuccess, "%герой нанес несколько ударов %оппоненту, но тот оказал суровый отпор.", DamageOpponent, Damage}
};

