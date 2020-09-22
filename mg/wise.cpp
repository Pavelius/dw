#include "main.h"

BSDATA(wisei) = {{"Birds-wise", "Знает повадки птиц", Animal},
{"Burrow-wise", "Знает повадки насекомых", Animal},
{"Mammal-wise", "Знает млекопитающихся", Animal},
{"Predator-wise", "Знает хищников", Animal},
//
{"Coast-wise", "Знает побережье", Coast},
{"Forest-wise", "Знает леса", Forest},
{"Lake-wise", "Знает озера", Lake},
{"Rocky terrain-wise", "Знает горы и холмы", Rocks},
{"Swamp-wise", "Знает болота", Swamp},
{"Tall grass-wise", "Знает высокую траву", TallGrass},
//
{"Craft-wise", "Знает все о ремесле"},
{"Crime-wise", "Знает преступников"},
{"Governor-wise", "Знает губернаторов"},
{"Guardmouse-wise", "Знает гвардейцев"},
//
{"Rain-wise", "Знает все о дождях"},
{"Calm weather-wise", "Знает все о хорошей погоде"},
{"Snow-wise", "Знает все о снегопаде"},
//
{"Barkstone-wise", "Знает Корукамень", Barkstone},
{"Cooperwood-wise", "Знает Краснолесье", Cooperwood},
{"Drakheather-wise", "Знает Темные Проходы"},
{"Elmoss-wise", "Знает Дубомох", Elmoss},
{"Ivydale-wise", "Знает Плющедолину", Ivydale},
{"Lockhaven-wise", "Знает Локхавен", Lockhaven},
{"Port Sumac-wise", "Знает Порт Сумрака", PortSumac},
{"Shaleburrow-wise", "Знает Глиноземье", Shaleburrow},
{"Sprucetuck-wise", "Знает Ельник", Sprucetuck},
};
assert_enum(wisei, LastWise)