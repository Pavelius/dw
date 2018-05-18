#include "main.h"

static action tavern[] = {
	{"Пошарить в карманах у местных зевак.", PickPockets, Duration1Turn, 0, {}, {"%герой не смог%ла украсть ничего ценного у местных зевак."}},
	{"Выйти отсюда наружу.", GoAway, Duration1Round, 0, {}, {"Вы вышли наружу."}},
};
static struct location_i {
	const char*		name;
	aref<action>	actions;
} location_data[] = {
	{""},
	{"Вы были в непроходимом лесу. Высокие деревья уходили кудато в небо."},
	{"Прямо возле вас находился вход в подземелье. Он зарос кустарником и травой."},
	{"Вы находились в небольшой комнате, размером 4 на 4 метра."},
	{"Вы были в огромном зале, слегка освещенным факелами."},
	{"В таверне приятно пахло жареным и было много людей, пьющих пиво."},
	{"На земле горел лагерный костер."},
};
assert_enum(location, WildCampfire);
getstr_enum(location);

aref<action> scene::getactions(location_s id) {
	return location_data[id].actions;
}