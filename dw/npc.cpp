#include "main.h"

void npc::create(class_s type)
{
	this->type = type;
	this->race = Human;
	this->gender = (gender_s)(xrand(Male, Female));
	this->alignment = (alignment_s)(xrand(Good, Evil));
	this->level = 1;
	this->name = game::getrandomname(race, gender);
}