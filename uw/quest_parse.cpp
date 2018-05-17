#include "cface/crt.h"
#include "cface/xsref.h"
#include "quest.h"

xsfield quest_elements_type[] = {
	BSREQ(quest::elements, start, number_type),
	BSREQ(quest::elements, count, number_type),
	{0}
};
xsfield quest_range_type[] = {
	BSREQ(quest::range, from, number_type),
	BSREQ(quest::range, to, number_type),
	BSREQ(quest::range, text, number_type),
	{0}
};
xsfield quest_parameter_type[] = {
	BSREQ(quest::parameter, id, number_type),
	BSREQ(quest::parameter, text, number_type),
	BSREQ(quest::parameter, value, number_type),
	BSREQ(quest::parameter, minimum, number_type),
	BSREQ(quest::parameter, maximum, number_type),
	BSREQ(quest::parameter, show, number_type),
	BSREQ(quest::parameter, trigger, number_type),
	BSREQ(quest::parameter, limit, number_type),
	BSREQ(quest::parameter, ranges, quest_elements_type),
	{0}
};
xsfield quest_method_type[] = {
	BSREQ(quest::method, object, number_type),
	BSREQ(quest::method, value, number_type),
	{0}
};
xsfield quest_jumper_type[] = {
	BSREQ(quest::jumper, id, number_type),
	BSREQ(quest::jumper, text, number_type),
	BSREQ(quest::jumper, condition, number_type),
	BSREQ(quest::jumper, change, quest_method_type),
	{0}
};
xsfield quest_function_type[] = {
	BSREQ(quest::function, id, number_type),
	BSREQ(quest::function, text, number_type),
	BSREQ(quest::function, params, number_type),
	{0}
};
xsfield quest_scene_type[] = {
	BSREQ(quest::scene, id, number_type),
	BSREQ(quest::scene, text, number_type),
	BSREQ(quest::scene, art, number_type),
	BSREQ(quest::scene, change, quest_method_type),
	BSREQ(quest::scene, jumpers, quest_elements_type),
	{0}
};
xsfield quest_table_type[] = {
	BSREQ(quest::table, id, number_type),
	BSREQ(quest::table, columns, number_type),
	BSREQ(quest::table, rows, quest_elements_type),
	{0}
};
xsfield quest_row_type[] = {
	BSREQ(quest::row, params, quest_elements_type),
	{0}
};
static const char* questtags_names[] = {"error", "win", "fail", "death", "continue"};

static const char* skipws(const char* p)
{
	while(p[0] == 9 || p[0] == 0x20)
		p++;
	return p;
}

static const char* skipline(const char* p)
{
	while(p[0] && p[0] != 10 && p[0] != 13)
		p++;
	return szskipcr(p);
}

static const char* read_text(const char* p, quest& q, int& result)
{
	char temp[8196];
	auto pb = temp;
	auto pe = pb + sizeof(temp) / sizeof(temp[0]) - 1;
	while(true)
	{
		auto sym = *p;
		if(!sym)
			break;
		if(sym == '\n' || sym == '\r')
		{
			while(*p == '\n' || *p == '\r')
				p = zskipsp(szskipcr(p));
			if(*p=='#')
				break;
			if(pb < pe)
				*pb++ = '\n';
			continue;
		}
		if(pb < pe)
			*pb++ = sym;
		p++;
	}
	*pb = 0;
	if(temp[0] == 0)
		result = 0;
	else
		result = getsid(temp);
	return p;
}

static const char* read_text(const char* p, quest& q, xsref e, const char* name)
{
	int result = 0;
	p = read_text(p, q, result);
	e.set(name, result);
	return p;
}

static int find_token(int id, const char** names, const char* value)
{
	for(auto p = names; *p; p++)
	{
		if(strcmp(*p, value) == 0)
			return id + (p - names);
	}
	return 0;
}

static const char* read_field(const char* p, quest& q, int& result)
{
	result = 0;
	char temp[8196]; temp[0] = 0;
	if(isnum(p[0]) || p[0]=='-')
		result = sz2num(p, &p);
	else if(p[0] == '\"')
	{
		p++;
		auto pb = temp;
		auto pe = pb + sizeof(temp) / sizeof(temp[0]) - 1;
		while(true)
		{
			auto sym = *p;
			if(!sym)
				break;
			if(sym == '\"')
			{
				p++;
				break;
			}
			if(pb < pe)
				*pb++ = sym;
			p++;
		}
		*pb = 0;
	}
	else
	{
		p = psidn(p, temp);
		result = find_token(QuestError, questtags_names, temp);
		if(result)
			temp[0] = 0;
	}
	if(temp[0])
		result = getsid(temp);
	return skipws(p);
}

static const char* read_field(const char* p, quest& q, xsref e, const char* name)
{
	int n = 0;
	p = read_field(p, q, n);
	e.set(name, n);
	return skipws(p);
}

static void set_field_value(xsref e, const char* name, int* params, unsigned count)
{
	if(name[0] == 0)
		name = "params";
	auto f = e.fields->find(name);
	if(!f)
		return;
	if(f->type == quest_method_type)
	{
		auto r = e.getr(name);
		if(!params[1])
			params[1] = 1;
		r.set("object", params[0]);
		r.set("value", params[1]);
	}
	else if(f->type == number_type && f->count > 1)
	{
		for(unsigned i = 0; i < count; i++)
		{
			if(i >= f->count)
				break;
			e.set(name, params[i], i);
		}
	}
	else
		e.set(name, params[0]);
}

static const char* read_fields(const char* p, quest& q, xsref e, const char* name_default)
{
	char name[4096];
	int params[12] = {0};
	while(p[0] && p[0] != 10 && p[0] != 13)
	{
		p = psidn(p, name);
		if(name[0] == 0)
			zcpy(name, name_default);
		p = skipws(p);
		if(p[0] == '(')
		{
			p = skipws(p + 1);
			int index = 0;
			while(p[0])
			{
				p = read_field(p, q, params[index++]);
				if(index > 2)
					index = 2;
				if(*p == ',')
				{
					p = skipws(p + 1);
					continue;
				}
				if(*p != ')')
					return skipline(p);
				p = skipws(p + 1);
				break;
			}
			set_field_value(e, name, params, index);
		}
	}
	return p;
}

static const char* read_trail(const char* p, quest& q, xsref xs)
{
	if(p[0] != 10 && p[0] != 13)
		return ""; // ERROR: expected end line symbol
	p = szskipcr(p);
	if(p[0] != '#')
		p = read_text(p, q, xs, "text");
	return p;
}

static const char* read_element(const char* p, quest& q, quest::elements* elements)
{
	if(szmatch(p, "#parameter"))
	{
		p = skipws(p + 10);
		quest::parameter e = {0};
		xsref xs = {quest_parameter_type, &e};
		p = read_field(p, q, xs, "id");
		p = read_fields(p, q, xs, "params");
		p = read_trail(p, q, xs);
		if(szmatch(p, "#range"))
			p = read_element(p, q, &e.ranges);
		q.parameters.reserve();
		q.parameters.add(e);
	}
	else if(szmatch(p, "#table"))
	{
		p = skipws(p + 6);
		quest::table e = {0};
		xsref xs = {quest_table_type, &e};
		p = read_field(p, q, xs, "id");
		p = read_fields(p, q, xs, "columns");
		p = read_trail(p, q, xs);
		q.tables.reserve();
		q.tables.add(e);
	}
	else if(szmatch(p, "#function"))
	{
		p = skipws(p + 9);
		quest::function e = {0};
		xsref xs = {quest_function_type, &e};
		p = read_field(p, q, xs, "id");
		p = read_fields(p, q, xs, "params");
		p = read_trail(p, q, xs);
		q.functions.reserve();
		q.functions.add(e);
	}
	else if(szmatch(p, "#scene"))
	{
		p = skipws(p + 6);
		quest::scene e = {0};
		xsref xs = {quest_scene_type, &e};
		p = read_field(p, q, xs, "id");
		p = read_fields(p, q, xs, "params");
		p = read_trail(p, q, xs);
		if(szmatch(p, "#go"))
			p = read_element(p, q, &e.jumpers);
		q.scenes.reserve();
		q.scenes.add(e);
	}
	else if(szmatch(p, "#range"))
	{
		if(elements)
			elements->start = q.ranges.count;
		while(szmatch(p, "#range"))
		{
			p = skipws(p + 6);
			quest::range e = {0};
			xsref xs = {quest_range_type, &e};
			p = read_fields(p, q, xs, "params");
			p = read_trail(p, q, xs);
			q.ranges.reserve();
			q.ranges.add(e);
		}
		if(elements)
			elements->count = q.ranges.count - elements->start;
	}
	else if(szmatch(p, "#go"))
	{
		if(elements)
			elements->start = q.jumpers.count;
		while(szmatch(p, "#go"))
		{
			p = skipws(p + 3);
			quest::jumper e = {0};
			xsref xs = {quest_jumper_type, &e};
			p = read_field(p, q, xs, "id");
			p = read_fields(p, q, xs, "params");
			p = read_trail(p, q, xs);
			q.jumpers.reserve();
			q.jumpers.add(e);
		}
		if(elements)
			elements->count = q.jumpers.count - elements->start;
	}
	else
		return ""; // ERROR: Unrecognized element name
	return p;
}

bool quest::read(const char* url)
{
	char temp[260];
	auto p = (const char*)loadt(szurl(temp, "quest", url, "txt"));
	if(!p)
		return false;
	clear();
	while(true)
	{
		if(p[0] == 0)
			break;
		p = read_element(p, *this, 0);
	}
	delete p;
	return true;
}