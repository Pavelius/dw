#include "main.h"

pack_info pack_data[] = {{"Burglar's Pack", "����� ���������", {Rope, HammerLight, Ration, Waterskin}},
{"Diplomat's Pack", "����� ���������", {Book, CalligrapherSupplies, Parchment, Map}},
{"Dungeoneer's Pack", "����� ������������� ����������", {Rope, Torches, Ration, Waterskin}},
{"Entertainer's Pack", "����� �������", {Bedroll, DisguiseKit, Ration, Waterskin}},
{"Explorer's Pack", "����� �����������", {Rope, Bedroll, Ration, Waterskin}},
{"Priest's Pack", "����� ����������", {Bedroll, Ration, Waterskin}},
{"Scholar's Pack", "����� �������", {Book, CalligrapherSupplies, Parchment, Dagger}},
//
{"Artisan's tool proficiency", "�������� ����������� ������������", {AlchemistProficiency, CalligrapherProficiency, CarpenterProficiency, CartographerProficiency, CobblerProficiency, CookProficiency, GlassblowerProficiency, JewelerProficiency, LeatherworkerProficiency, MasonProficiency, PainterProficiency, PotterProficiency, SmithProficiency, TinkerProficiency, WeaverProficiency, WoodcarverProficiency}},
};
getstr_enum(pack);
assert_enum(pack, LastPack);