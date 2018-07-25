#include "bsreq.h"
#include "logs.h"
#include "logs_quest.h"

using namespace logs;

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