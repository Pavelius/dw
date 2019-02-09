#include "crt.h"
#include "logs.h"

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

void logs::driver::addidentifier(const char* identifier) {
	if(name && strcmp(identifier, "герой") == 0)
		add(name);
	else if(name && strcmp(identifier, "героя") == 0)
		addof(name);
	else if(opponent_name && strcmp(identifier, "оппонент") == 0)
		add(opponent_name);
	else if(opponent_name && strcmp(identifier, "оппонента") == 0)
		addof(opponent_name);
	else if(opponent_name && strcmp(identifier, "оппоненту") == 0)
		addto(opponent_name);
	else if(weapon && strcmp(identifier, "оружием") == 0)
		addby(weapon);
	else {
		for(auto& e : player_gender) {
			if(strcmp(e.female, identifier) != 0)
				continue;
			if(count > 1)
				add(e.multiply);
			else if(gender == Female)
				add(e.female);
			else
				add(e.male);
			return;
		}
		for(auto& e : opponent_gender_change) {
			if(strcmp(e.female, identifier) != 0)
				continue;
			if(count > 1)
				add(e.multiply);
			else if(gender == Female)
				add(e.female);
			else
				add(e.male);
			return;
		}
		stringbuilder::addidentifier(identifier);
	}
}