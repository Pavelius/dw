#include "crt.h"
#include "grammar.h"
#include "logs_driver.h"

void logs::driver::msg(gender_s gender, char* result, const char* result_max, const char* text_male, const char* text_female) {
	if(gender == Female) {
		if(text_female)
			zcpy(result, text_female);
	} else {
		if(text_male)
			zcpy(result, text_male);
	}
}

void logs::driver::msg(gender_s gender, char* result, const char* result_max, const char* text_male, const char* text_female, const char* text_pluar) {
	if(opponent_count > 1) {
		if(text_pluar)
			zcpy(result, text_pluar);
	} if(gender == Female) {
		if(text_female)
			zcpy(result, text_female);
	} else {
		if(text_male)
			zcpy(result, text_male);
	}
}

void logs::driver::parseidentifier(char* result, const char* result_max, const char* identifier) {
	if(strcmp(identifier, "герой") == 0)
		zcpy(result, name);
	else if(strcmp(identifier, "героя") == 0)
		grammar::of(result, name);
	else if(strcmp(identifier, "оппонент") == 0)
		zcpy(result, opponent_name);
	else if(strcmp(identifier, "оппонента") == 0)
		grammar::of(result, opponent_name);
	else if(strcmp(identifier, "ась") == 0)
		msg(gender, result, result_max, "ся", identifier);
	else if(strcmp(identifier, "а") == 0)
		msg(gender, result, result_max, "", identifier);
	else if(strcmp(identifier, "ая") == 0)
		msg(gender, result, result_max, "ый", identifier);
	else if(strcmp(identifier, "А") == 0)
		msg(opponent_gender, result, result_max, "", "а");
	else if(strcmp(identifier, "ла") == 0)
		msg(gender, result, result_max, "", identifier);
	else if(strcmp(identifier, "ЛА") == 0)
		msg(opponent_gender, result, result_max, "", "ла");
	else if(strcmp(identifier, "она") == 0)
		msg(gender, result, result_max, "он", identifier);
	else if(strcmp(identifier, "ОНА") == 0)
		msg(opponent_gender, result, result_max, "он", "она");
	else if(strcmp(identifier, "ее") == 0)
		msg(gender, result, result_max, "его", identifier);
	else if(strcmp(identifier, "ЕЕ") == 0)
		msg(opponent_gender, result, result_max, "его", "ее");
	else if(strcmp(identifier, "ей") == 0)
		msg(gender, result, result_max, "ему", identifier, "им");
	else if(strcmp(identifier, "нее") == 0)
		msg(gender, result, result_max, "него", identifier, "них");
	else {
		zcat(result, "[-");
		zcat(result, identifier);
		zcat(result, "]");
	}
}