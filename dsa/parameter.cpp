#include "main.h"

parameteri bsmeta<parameteri>::elements[] = {{"LP", "Жизнь", "ОЗ", ViewCurrentAndMaximum},
{"AP", "Магия", "ОА", ViewCurrentAndMaximum},
{"AV", "Атака", "Ат", ViewStandart},
{"PV", "Парирование", "Пр", ViewStandart},
{"PVC", "Парировано атак", "ПрК", ViewStandart},
{"RS", "Доспех", "Бр", ViewStandart},
{"Level", "Уровень", "Ур", ViewStandart},
};
assert_enum(parameter, Level);