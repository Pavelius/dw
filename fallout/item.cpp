#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"", 0, 0, {}, "%герой нанес%ла удар рукой."},
{"револьвер", 0, 0, {Close, Reload}, "%герой выставил%а револьвер и выстрелил%а в %оппонента."},
{"пистолет", 0, 0, {Close}, "%герой вскинул%а пистолет и выстрелил%а."},
{"ружье", 0, 0, {Close, Far}, "%герой вскинул%а ружье и сделал%а меткий выстрел."},
{"дробовик", 0, 0, {Close, Messy, Reload}, "%герой вскинул%а дробовик и с грохотом разр€дил%а его."},
{"магнум", 1, 0, {Close}, "%герой вскинул%а пистолет и прогремел выстрел."},
{"бензопила", 1, 0, {Messy, Reload}, "Ўироко размахнувшись %герой сделал%а полукруг бензопилой. ѕила адски взвыла."},
{"SMG", 0, 0, {Close, Area}, "%герой дал%а короткую очередь выставив вперед пистолет-пулемет."},
//
{"нож", 0, 0, {Light}, "%герой нанес%ла несколько метких ударов снизу."},
{"посох", 0, 0, {Light, Area}, "%герой сделал%а пару быстрых ударов посохом."},
{"копье", 0, 0, {}, "%герой проткнул%а копьем %оппонента."},
{"цепь", 0, 0, {Light, Area}, "—делав несколько взмахов %герой нанес удар цепью."},
{"монтировка", 0, 0, {}, "—ильно размахнувшись %герой нанес%ла удар монтировкой."},
{"гранаты", 1, 0, {Close, Area}, "—орвав чеку %герой кинул%а гранату. –аздалс€ взрыв."},
{"мачете", 1, 0, {Close, Area}, "— криком %герой нанес%ла мощный удар наотмаш."},
//
{"винтовка с прицелом", 0, 0, {Far, Scope}, "%герой вскинул%а винтовку и сделал%а меткий выстрел."},
{"пулемет", 2, 0, {Close, Area}, "%герой выставил вперед пулемет и дал%а длинную очередь."},
{"автомат", 1, 0, {Close, Far, Area}, "%герой вскинул%а автомат и дал%а длинную очередь."},
{"гранатомет", 3, 0, {Far, Area, Reload}, "%герой вскинул%а гранатомет и сделал%а выстрел. ќставив шлейф ракета устремилась к целе. –аздалс€ взрыв."},
};
assert_enum(item, GrenadeLauncher);

void item::clear() {
	type = NoItem;
	upgrade = 0;
}

dice item::getharm() const {
	dice result = {1, 6, bsmeta<itemi>::elements[type].harm};
	if(is(Light))
		result.d = 3;
	return result;
}

bool item::is(label_s value) const {
	return bsmeta<itemi>::elements[type].tag.is(value);
}

const char* item::getname() const {
	return bsmeta<itemi>::elements[type].name;
}

const char* item::gettextsuccess() const {
	return bsmeta<itemi>::elements[type].success;
}

char* item::getname(char* result, bool description) {
	result[0] = 0;
	//for(auto e = Blade; e <= Valuable; e = (upgrade_s)(e + 1)) {
	//	if(upgrade_data[e].ending)
	//		continue;
	//	if(is(e)) {
	//		zcat(result, upgrade_data[e].name);
	//		zcat(result, " ");
	//	}
	//}
	zcpy(result, getstr(type));
	//for(auto e = Blade; e <= Valuable; e = (upgrade_s)(e + 1)) {
	//	if(!upgrade_data[e].ending)
	//		continue;
	//	if(is(e)) {
	//		zcat(result, " ");
	//		zcat(result, upgrade_data[e].name);
	//	}
	//}
	return result;
}