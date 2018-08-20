#include "main.h"

void thing::act(const char* format, ...) {
	logs::driver printer;
	printer.gender = getgender();
	printer.name = getname();
	logs::addv(printer, format, xva_start(format));
}

void thing::act(const thing& opponent, const char* format, ...) {
	logs::driver printer;
	printer.gender = getgender();
	printer.name = getname();
	printer.opponent_gender = opponent.getgender();
	printer.opponent_name = opponent.getname();
	logs::addv(printer, format, xva_start(format));
}

void thing::act(const thinga& opponents, const char* format, ...) {
	struct local_driver : logs::driver {
		const thinga& opponents;
		local_driver(const thinga& opponents) : opponents(opponents) {}
		void parseidentifier(char* result, const char* result_max, const char* identifier) override {
			if(strcmp(identifier, "оппоненты") == 0) {
				auto p = zend(result);
				int maximum = opponents.getcount();
				for(auto i = 0; i < maximum; i++) {
					p = zend(p);
					if(maximum > 1 && i == maximum - 1)
						szprints(p, result_max, " и ");
					else if(i > 0)
						szprints(p, result_max, ", ");
					p = zend(p); szprints(result, result_max, opponents[i]->getname());
				}
			}
			else
				logs::driver::parseidentifier(result, result_max, identifier);
		}
	};
	if(!opponents || !*opponents[0])
		return;
	local_driver printer(opponents);
	printer.gender = getgender();
	printer.name = getname();
	printer.opponent_gender = opponents[0]->getgender();
	printer.opponent_name = opponents[0]->getname();
	printer.opponent_count = opponents.getcount();
	logs::addv(printer, format, xva_start(format));
}

void thing::ask(int id, const char* format, ...) {
	logs::driver printer;
	printer.gender = getgender();
	printer.name = getname();
	logs::addv(id, printer, format, xva_start(format));
}

void thing::actv(aref<char> result, const char* format, const char* format_param) {
	logs::driver printer;
	printer.gender = getgender();
	printer.name = getname();
	printer.printv(result.data, result.data + result.count, format, format_param);
}