#include "main.h"

wisei bsmeta<wisei>::elements[] = {{"Birds-wise", "Знает повадки птиц"},
{"Burrow-wise", "Знает повадки насекомых"},
{"Mammal-wise", "Знает млекопитающихся"},
{"Predator-wise", "Знает хищников"},
//
{"Coast-wise", "Знает побережье"},
{"Forest-wise", "Знает леса"},
{"Lake-wise", "Знает озера"},
{"Rocky terrain-wise", "Знает горы и холмы"},
{"Swamp-wise", "Знает болота"},
{"Tall grass-wise", "Знает высокую траву"},
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
{"Barkstone-wise", "Знает Корукамень"},
{"Cooperwood-wise", "Знает Краснолесье"},
{"Drakheather-wise", "Знает Темные Проходы"},
{"Elmoss-wise", "Знает Дубомох"},
{"Ivydale-wise", "Знает Плющедолину"},
{"Lockhaven-wise", "Знает Локхавен"},
{"Port Sumac-wise", "Знает Порт Сумрака"},
{"Shaleburrow-wise", "Знает Глиноземье"},
{"Sprucetuck-wise", "Знает Ельник"},
};
assert_enum(wise, LastWise);