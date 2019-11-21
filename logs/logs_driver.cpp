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

static void addsquad(stringbuilder& sb, const char* name, int count) {
	if(count <= 1)
		sb.add(name);
	else if(count <= 4) {
		sb.add("%1i ", count);
		sb.addof(name);
	} else {
		sb.add("%1i ", count);
		sb.addof(name);
	}
}

static void addsquadof(stringbuilder& sb, const char* name, int count) {
	if(count <= 1)
		sb.addof(name);
	else if(count <= 4) {
		sb.add("%1i ", count);
		sb.addof(name);
	} else {
		sb.add("%1i ", count);
		sb.addof(name);
	}
}

void logs::driver::addidentifier(const char* identifier) {
	if(name && strcmp(identifier, "�����") == 0)
		add(name);
	else if(name && strcmp(identifier, "�����") == 0)
		addof(name);
	else if(name && strcmp(identifier, "�����") == 0)
		addsquad(*this, name, count);
	else if(name && strcmp(identifier, "�����") == 0)
		addsquadof(*this, name, count);
	else if(opponent_name && strcmp(identifier, "�����_���������") == 0)
		addsquad(*this, opponent_name, count);
	else if(opponent_name && strcmp(identifier, "�����_���������") == 0)
		addsquadof(*this, opponent_name, count);
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
			if(strcmp(e.id, identifier) != 0)
				continue;
			if(opponent_count > 1)
				add(e.multiply);
			else if(opponent_gender == Female)
				add(e.female);
			else
				add(e.male);
			return;
		}
		stringbuilder::addidentifier(identifier);
	}
}