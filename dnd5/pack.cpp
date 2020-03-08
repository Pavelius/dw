#include "main.h"

packi bsmeta<packi>::elements[] = {{"Burglar's Pack", "Набор взломщика", {Rope, HammerLight, Ration, Waterskin}},
{"Diplomat's Pack", "Набор дипломата", {Book, CalligrapherSupplies, Parchment, Map}},
{"Dungeoneer's Pack", "Набор исследователя подземелий", {Rope, Torches, Ration, Waterskin}},
{"Entertainer's Pack", "Набор артиста", {Bedroll, DisguiseKit, Ration, Waterskin}},
{"Explorer's Pack", "Набор приключенца", {Rope, Bedroll, Ration, Waterskin}},
{"Priest's Pack", "Набор священника", {Bedroll, Ration, Waterskin}},
{"Scholar's Pack", "Набор ученого", {Book, CalligrapherSupplies, Parchment, Dagger}},
//
{"Artisan's tool proficiency", "Владение ремесленным иснтрументом", {AlchemistProficiency, CalligrapherProficiency, CarpenterProficiency, CartographerProficiency, CobblerProficiency, CookProficiency, GlassblowerProficiency, JewelerProficiency, LeatherworkerProficiency, MasonProficiency, PainterProficiency, PotterProficiency, SmithProficiency, TinkerProficiency, WeaverProficiency, WoodcarverProficiency}},
};
assert_enum(pack, ArtisanToolsProficiency);