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