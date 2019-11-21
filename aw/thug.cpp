#include "main.h"

thugi bsmeta<thugi>::elements[] = {{"biker", "байкер", Male, {Harm2, Loud}},
};
assert_enum(thug, Biker);

thing::thing(thug_s v) : variant(v), tagable(bsmeta<thugi>::elements[v].tags), health(gethealthmax()) {}