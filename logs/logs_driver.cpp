#include "crt.h"
#include "grammar.h"
#include "logs_driver.h"

static void msg(gender_s gender, int count, char* result, const char* result_max, const char* text_male, const char* text_female, const char* text_pluar) {
	if(count > 1) {
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
	else if(strcmp(identifier, "�") == 0)
		msg(gender, count, result, result_max, "", identifier, "�");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, count, result, result_max, "", identifier, "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, count, result, result_max, "��", identifier, "���");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, count, result, result_max, "��", identifier, "��");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, count, result, result_max, "���", identifier, "��");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, count, result, result_max, "����", identifier, "���");
	else if(strcmp(identifier, "���") == 0)
		msg(gender, count, result, result_max, "��", identifier, "���");
	else if(strcmp(identifier, "��") == 0)
		msg(gender, count, result, result_max, "���", identifier, "��");
	else if(strcmp(identifier, "�") == 0)
		msg(opponent_gender, opponent_count, result, result_max, "", "�", "�");
	else if(strcmp(identifier, "��") == 0)
		msg(opponent_gender, opponent_count, result, result_max, "", "��", "��");
	else if(strcmp(identifier, "��") == 0)
		msg(opponent_gender, opponent_count, result, result_max, "���", "��", "��");
	else if(strcmp(identifier, "���") == 0)
		msg(opponent_gender, opponent_count, result, result_max, "��", "���", "���");
	else {
		zcat(result, "[-");
		zcat(result, identifier);
		zcat(result, "]");
	}
}