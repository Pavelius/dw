#include "crt.h"
#include "stringcreator.h"
#include "logs.h"
#include "quest.h"

using namespace quest;

static adat<parameter, 64>	parameters;
static adat<range, 1024>	ranges;
static adat<scene, 512>		scenes;
static adat<jumper, 2048>	jumpers;
static adat<row, 2048>		rows;
static adat<table, 64>		tables;

void quest::clear()
{
	parameters.clear();
	ranges.clear();
	scenes.clear();
	jumpers.clear();
	rows.clear();
	tables.clear();
}

const scene* quest::findscene(const char* id)
{
	if(!scenes.count)
		return 0;
	for(auto& e : scenes)
	{
		if(strcmp(e.id, id) == 0)
			return &e;
	}
	return 0;
}

param_types quest::method::apply() const
{
	if(!id)
		return ParameterStandart;
	auto pr = parameters.find(id);
	if(pr)
	{
		pr->add(value);
		return pr->check();
	}
	return ParameterError;
}

param_types quest::play(const char* id, const char** next_block)
{
	auto p = findscene(id);
	if(!p)
		return ParameterError;
	// Fire event for entering location
	auto qe = p->change.apply();
	if(qe != ParameterStandart)
		return qe;
	// Set art
	if(p->art)
		logs::loadart(p->art);
	logs::add(p->text);
	auto index = 1;
	for(auto& j : p->jumpers)
	{
		if(j.condition)
		{
			//calculator e;
			//if(!e.evalute(getstr(j.condition)))
			//	continue;
		}
		auto pt = j.text;
		if(!pt)
			pt = "Продолжить.";
		logs::add(index++, pt);
	}
	auto result = logs::input();
	if(!result)
		return ParameterError;
	auto& jm = jumpers.data[result - 1];
	// Fire event for leaving location by variant
	if(next_block)
		*next_block = jm.id;
	return jm.change.apply();
}