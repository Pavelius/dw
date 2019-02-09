#include "crt.h"
#include "logs.h"

struct gender_change_string {
	const char*	id;
	const char*	female;
	const char*	male;
	const char*	multiply;
};
static gender_change_string player_gender[] = {{"�", "�", "", "�"},
{"��", "��", "", "��"},
{"���", "���", "��", "���"},
{"��", "��", "��", "��"},
{"��", "��", "���", "��"},
{"���", "���", "����", "���"},
{"���", "���", "��", "���"},
{"��", "��", "���", "��"},
};
static gender_change_string opponent_gender_change[] = {{"�", "�", "", "�"},
{"��", "��", "", "��"},
{"���", "���", "��", "���"},
{"��", "��", "���", "��"},
};

void logs::driver::addidentifier(const char* identifier) {
	if(name && strcmp(identifier, "�����") == 0)
		add(name);
	else if(name && strcmp(identifier, "�����") == 0)
		addof(name);
	else if(opponent_name && strcmp(identifier, "��������") == 0)
		add(opponent_name);
	else if(opponent_name && strcmp(identifier, "���������") == 0)
		addof(opponent_name);
	else if(opponent_name && strcmp(identifier, "���������") == 0)
		addto(opponent_name);
	else if(weapon && strcmp(identifier, "�������") == 0)
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