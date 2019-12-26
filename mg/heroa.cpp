#include "main.h"

namespace {
class stringd : public driver {
	const heroa& source;
	void addidentifier(const char* identifier) override {
		if(equal(identifier, "герой"))
			source.addn(*this);
		else
			driver::addidentifier(identifier);
	}
public:
	stringd(const heroa& source, const stringbuilder& sb) : driver(sb), source(source) {}
};
}

void heroa::addn(stringbuilder& sb) const {
	unsigned index = 0;
	for(auto p : *this) {
		if(index>0) {
			if(index < count - 1)
				sb.add(", ");
			else
				sb.add(" и ");
		}
		sb.add(p->getname());
		index++;
	}
}

void heroa::select() {
	auto pa = data;
	for(auto p : party) {
		if(!p || !p->isalive())
			continue;
		*pa++ = p;
	}
	count = pa - data;
}

void heroa::add(hero* p) {
	if(is(p))
		return;
	adat::add(p);
}

void heroa::act(const char* format, ...) const {
	actv(sb, format, xva_start(format));
}

void heroa::actv(stringbuilder& sc, const char* format, const char* format_param) const {
	stringd sb(*this, sc);
	sb.addsep(' ');
	sb.addv(format, format_param);
	sc = sb;
}