#include "bsdata.h"
#include "logs.h"
#include "logs_quest.h"

using namespace logs;

bsreq conversation_type[] = {
	BSREQ(conversation, id, text_type),
	BSREQ(conversation, text, conversation_type),
{}};
bsreq action_type[] = {
	BSREQ(action, text, text_type),
	BSREQ(action, next, conversation_type),
{}};

void quest::clear() {
	conversations.clear();
	actions.clear();
}

const conversation* quest::play(const conversation* p) {
	const auto interactive = true;
	logs::add(p->text);
	for(auto& e : p->actions)
		logs::add((int)&e, e.text);
	auto e = (action*)logs::input(interactive);
	if(e)
		p = e->next;
	return p;
}

bool quest::read(const char* url) {
	bsdata action_data("action", actions, action_type);
	bsdata conversation_data("conversation", conversations, conversation_type);
	bsdata* databases[] = {&action_data, &conversation_data, 0};
	return bsdata::read(url, databases);
}