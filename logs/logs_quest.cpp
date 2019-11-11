#include "crt.h"
#include "logs.h"
#include "logs_quest.h"

using namespace logs;

void quest::clear() {
	conversations.clear();
	actions.clear();
}

const conversation* quest::find(const char* id) const {
	if(!id)
		return 0;
	for(auto& e : conversations) {
		if(strcmp(e.id, id) == 0)
			return &e;
	}
	return 0;
}

const conversation* quest::play(const conversation* p) {
	const auto interactive = true;
	sb.add(p->text);
	for(auto& e : p->action)
		an.add((int)&e, e.text);
	auto e = (action*)an.choosev(interactive, true, false, 0);
	if(e)
		p = find(e->next);
	return p;
}

quest::result_s quest::run(const conversation* p) {
	while(p)
		p = play(p);
	return Success;
}