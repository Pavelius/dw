#include "crt.h"
#include "logs_driver.h"

struct gender_change_string {
	const char*	id;
	const char*	female;
	const char*	male;
	const char*	multiply;
};
static gender_change_string player_gender[] = {{"а", "а", "", "и"},
{"ла", "ла", "", "ли"},
{"ась", "ась", "ся", "ись"},
{"ая", "ая", "ый", "ые"},
{"ей", "ей", "ему", "им"},
{"нее", "нее", "него", "них"},
{"она", "она", "он", "они"},
{"ее", "ее", "его", "их"},
};
static gender_change_string opponent_gender_change[] = {{"А", "а", "", "и"},
{"ЛА", "ла", "", "ли"},
{"ОНА", "она", "он", "они"},
{"ЕЕ", "ее", "его", "их"},
};

logs::driver::driver() : gender(), opponent_gender(),
name(), opponent_name(),
count(1), opponent_count(1),
custom(logs::getbuilder().custom) {
	logs::getbuilder().custom = this;
}

logs::driver::~driver() {
	logs::getbuilder().custom = custom;
}

void logs::driver::addidentifier(stringbuilder& sb, const char* identifier) {
	if(strcmp(identifier, "герой") == 0)
		sb.add(name);
	//else if(strcmp(identifier, "героя") == 0)
	//	grammar::of(result, result_max, name);
	else if(strcmp(identifier, "оппонент") == 0)
		sb.add(opponent_name);
	//else if(strcmp(identifier, "оппонента") == 0)
	//	grammar::of(result, result_max, opponent_name);
	//else if(strcmp(identifier, "оппоненту") == 0)
	//	grammar::to(result, result_max, opponent_name);
	else {
		for(auto& e : player_gender) {
			if(strcmp(e.female, identifier) != 0)
				continue;
			if(count > 1)
				sb.add(e.multiply);
			else if(gender == Female)
				sb.add(e.female);
			else
				sb.add(e.male);
			return;
		}
		for(auto& e : opponent_gender_change) {
			if(strcmp(e.female, identifier) != 0)
				continue;
			if(count > 1)
				sb.add(e.multiply);
			else if(gender == Female)
				sb.add(e.female);
			else
				sb.add(e.male);
			return;
		}
		sb.adderror(identifier);
	}
}