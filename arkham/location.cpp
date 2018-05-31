#include "main.h"

location location_data[YeOldeMagickShoppe + 1] = {{"Lost in Time and Space", "Потерянные во времени и пространстве"},
{"Administration Building", "Здание Администрации"},
{"Arkham Asylum", "Лечебница Аркхэма", "В здании большницы Аркхема было тускло и даже несколько зловеще. Время от времени слышались крики лежащих здесь больных. Немногочисленный медперсонал зловеще улыбался вам, стараясь соблюдать правила гостеприимства."},
{"Bank of Arkham", "Банк Аркхэма"},
{"Black Cave", "Темная пещера"},
{"Curiositie Shoppe", "Магазин диковинных вещей"},
{"GeneralStore", "Магазин"},
{"Graveyard", "Кладбище"},
{"HibbsRoadhouse", "Закусочная Гиббса"},
{"HistoricalSociety", "Историческое общество"},
{"IndependenceSquare", "Площадь независимости"},
{"Library", "Библиотека"},
{"MasBoardingHouse", ""},
{"Newspaper", "Офис газеты"},
{"PoliceStation", "Полицейский участок"},
{"RiverDocks", "Доки"},
{"ScienceBuilding", "Лаборатория"},
{"SilverTwilightLodge", ""},
{"SouthChurch", "Южная церковь"},
{"StMarysHospital", "Госпиталь Святой Марии"},
{"TheUnnamable", ""},
{"TheWitchHouse", ""},
{"TrainStation", "Вокзал"},
{"UnvisitedIsle", "Безлюдный остров"},
{"VelmasDiner", ""},
{"Woods", "Леса"},
{"YeOldeMagickShoppe", "Магазин магии"},
};
assert_enum(location, YeOldeMagickShoppe);
getstr_enum(location);

