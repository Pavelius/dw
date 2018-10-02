#include "main.h"

pack_info pack_data[] = {{"Burglar's Pack", "Набор взломщика", {Rope, HammerLight, Ration, Waterskin}},
{"Diplomat's Pack", "Набор дипломата", {Book, CalligrapherSupplies, Parchment, Map}},
{"Dungeoneer's Pack", "Набор исследователя подземелий", {Rope, Torches, Ration, Waterskin}},
{"Entertainer's Pack", "Набор артиста", {Bedroll, DisguiseKit, Ration, Waterskin}},
{"Explorer's Pack", "Набор приключенца", {Rope, Bedroll, Ration, Waterskin}},
{"Priest's Pack", "Набор священника", {Bedroll, Ration, Waterskin}},
{"Scholar's Pack", "Набор ученого", {Book, CalligrapherSupplies, Parchment, Dagger}},
//
{"Gaming set", "Игровой набор", {Dices, PlayingCards}},
};
getstr_enum(pack);
assert_enum(pack, LastPack);