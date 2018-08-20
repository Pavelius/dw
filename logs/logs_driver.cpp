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
	if(strcmp(identifier, "�����") == 0)
		zcpy(result, name);
	else if(strcmp(identifier, "�����") == 0)
		grammar::of(result, name);
	else if(strcmp(identifier, "��������") == 0)
		zcpy(result, opponent_name);
	else if(strcmp(identifier, "���������") == 0)
		grammar::of(result, opponent_name);
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, result_max, "��", identifier);
	else if(strcmp(identifier, "�") == 0)
		msg(gender, result, result_max, "", identifier);
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, result_max, "��", identifier);
	else if(strcmp(identifier, "�") == 0)
		msg(opponent_gender, result, result_max, "", "�");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, result_max, "", identifier);
	else if(strcmp(identifier, "��") == 0)
		msg(opponent_gender, result, result_max, "", "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, result_max, "��", identifier);
	else if(strcmp(identifier, "���") == 0)
		msg(opponent_gender, result, result_max, "��", "���");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, result_max, "���", identifier);
	else if(strcmp(identifier, "��") == 0)
		msg(opponent_gender, result, result_max, "���", "��");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, result, result_max, "���", identifier, "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, result, result_max, "����", identifier, "���");
	else {
		zcat(result, "[-");
		zcat(result, identifier);
		zcat(result, "]");
	}
}