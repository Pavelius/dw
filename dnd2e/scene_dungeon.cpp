#include "logs/archive.h"
#include "logs/io.h"
#include "main.h"

using namespace game;

enum flag_s : unsigned char {
	Locked, HiddenTrap, HiddenSecret, Guardians,
};
struct placeflags {
	constexpr placeflags() : data(0) {}
	constexpr bool	is(flag_s v) const { return (data & (1 << v)) != 0; }
	void			remove(flag_s v) { data &= ~(1 << v); }
	void			set(flag_s v) { data |= 1 << v; }
private:
	unsigned char	data;
	friend struct archive;
};
struct roominfo {
	const char*		name;
	const char*		text;
};
struct placeinfo {
	const char*		name;
	const char*		text;
	const char*		locked;
	const char*		examine;
};
struct trapinfo {
	struct thinfo {
		char		thac0;
	};
	const char*		text;
	const char*		activate;
	saveinfo		save;
	damageinfo		damage;
	thinfo			thi;
};
static placeinfo place_data[] = {{"саркофаг", "Около стены находился большой каменный саркофаг.", "Похоже его крышка была закрыта на какой-то хитроумный замок.", "Саркофаг содержал какие-то фрески непонятного содержимого и был сделан из камня."},
{"сундук", "В углу стояло несколько сундуков, окованных железом.", "Почти все были открыты и там не было ничего ценного, но на одном, самом большом висел огромный железный замок.", "Сундук был огромный и оббит металическими прутьями."},
{"жертвенник", "Посредине стояло некое подобие жертвенника рядом с которым стояло несколько урн.", 0, "Жертвенник был сделан из черного камня. Со временем камень потрескался и треснул."},
{"мусор", "В углу находилась большая куча мусора, покрытая вончей слизью. От кучи исходил сильный аромат.", 0, "Среди мусора было видно множество гнилых остатков еды. Вполне возможно в мусоре копошились какие-то жуки или букашки. Вонь была невыносимая."},
{"колодец", "Посредине стоял каменный колодец.", 0, "Заглянув внутрь вы увидели что на расстоянии 2-3 метра блестит вода. Она черного цвета."},
{"стол", "Повсюду были остатки старой и прогнившей мебели. Прямо посредине стоял дубовый стол, который неплохо сохранился.", 0, "Стол был крепкий и в довольно хорошем состоянии."},
};
static roominfo room_data[] = {{"комната", "Вы находились в небольшой комнате, размером 4 на 4 метра."},
{"зал", "Вы были в огромном зале, слегка освещенным факелами."},
{"комната", "Вокруг комната примерно 10 метров шириной. Судя по обломкам интрументов здесь когда-то была темница."},
{"библиотека", "Вокруг вас была круглая комната с расставленнмыми вокруг стен гнилыми стеллажами. Похоже когда-то здесь стояли книги, но мощный пожар их уничтожил."},
{"зал", "Вы стояли в зале, с белыми мраморными колонами. На стенах была видна мозаика, которая изображала брутальные сцены убийства."},
};
static trapinfo trap_data[] = {{"На одной из стен находились отверстия для пуска стрелы в неудачливого посетителя.", "Из отверстия одной из стен вылетела стрела.", {}, {Piercing, {1, 6}}, {15}},
{"На полу были три отверстия из которых вылезжали лезвия метр длинной.", "Внезапно из пола выехали лезвия.", {SaveVsParalization, Negate}, {Slashing, {2, 6}}},
};

struct room : placeflags {

	roominfo*	type;
	trapinfo*	trap;
	placeinfo*	feature;
	aref<item>	loots;

	struct log : stringcreator {
		struct variable {
			const char*	id;
			void		(log::*proc)(char* result, const char* result_maximum);
		};
		const room*		object;
		constexpr log(room* object) : object(object) {}
		void loots(char* result, const char* result_maximum) {
			item::getdescription(result, result_maximum, object->loots);
		}
		static variable* find(const char* identifier) {
			static variable methods[] = {
				{"предметы", &loots},
			};
			for(auto& e : methods) {
				if(strcmp(e.id, identifier) == 0)
					return &e;
			}
			return 0;
		}
		void parseidentifier(char* result, const char* result_max, const char* identifier) override {
			auto p = find(identifier);
			if(p)
				(this->*(p->proc))(result, result_max);
			else {
				zcat(result, "[-");
				zcat(result, identifier);
				zcat(result, "]");
			}
		}
	};

	room() : type(0), trap(0) {
	}

	placeflags& getflags() {
		return *this;
	}

	unsigned getitemcount() const {
		auto result = 0;
		for(auto& i : loots) {
			if(i)
				result++;
		}
		return 0;
	}

	void lookaround() {
		logs::add(type->text);
		if(feature)
			act(feature->text);
		if(trap && !is(HiddenTrap))
			logs::add(trap->text);
	}

	void act(const char* format, ...) {
		log sc(this);
		logs::addv(sc, format, xva_start(format));
	}

	void ask(tag id, const char* format, ...) {
		if(game::isallow(id)) {
			log sc(this);
			logs::addv(id, sc, format, xva_start(format));
		}
	}

	void ask(tag id, character* player, const char* format, ...) {
		if(game::isallow(id, player)) {
			log sc(this);
			logs::addv(id, sc, format, xva_start(format));
		}
	}

	void checkencounter() {
		if(d10() <= 1) {
			auto pe = getdungeonencounter(1)->roll();
			character enemy(pe->monster);
			enemy.setcount(xrand(pe->count[0], pe->count[1]));
			enemy.act("Внезапно из темноты появилось %группа. Без раздумий они бросились в атаку.");
			combat(true, enemy);
		}
	}

	void checkguard() {
		if(is(Guardians)) {
			auto pe = getdungeonencounter(1)->roll();
			character enemy(pe->monster);
			enemy.setcount(xrand(pe->count[0], pe->count[1]));
			enemy.act("Внезапно из темноты появилось %группа. Без раздумий они бросились в атаку.");
			combat(true, enemy);
			remove(Guardians);
		}
	}

	void checktrap(character* player) {
		if(!trap)
			return;
		player->act(trap->activate);
		remove(HiddenTrap);
		if(trap->thi.thac0 && !game::attack(trap->thi.thac0, player->getAC())) {
			char temp[260];
			logs::add("Но попасть в %1 не удалось.", grammar::of(temp, player->getname()));
			return;
		}
		auto damage = trap->damage.getdamage(player->getsize()).roll();
		player->damage(true, damage, trap->save);
	}

	void findsecrets(character* player, bool result) {
		player->act("%герой обыскал%а комнату и");
		if(result) {
			player->act("обнаружил%а [секретную дверь].");
			remove(HiddenSecret);
			if(player->get(Theif))
				player->addexp(true, 25);
		} else
			player->act("не обнаружил%а ничего интересного.");
		logs::next();
		checkencounter();
	}

	void findtraps(character* player, bool result) {
		player->act("%герой обыскал%а комнату и");
		if(result && trap) {
			remove(HiddenTrap);
			player->act("обнаружил%а [ловушку].");
			if(player->get(Theif))
				player->addexp(true, 20);
		} else
			player->act("не обнаружил%а накаких ловушек.");
		logs::next();
		checkencounter();
	}

	void removetraps(character* player, bool result) {
		player->act("%герой присел%а рядом с ловушкой и попытал%ась ее обезвредить.");
		passtime(true, Duration1Turn);
		if(result) {
			player->act("Вскоре ловушка была обезврежена.");
			if(player->get(Theif))
				player->addexp(true, 80);
			trap = 0;
		} else
			player->act("Ничего не вышло.");
		logs::next();
		checkencounter();
	}

	void picklock(character* player, bool result) {
		if(result) {
			player->act("%герой вскрыл%а замок.");
			remove(Locked);
			if(player->get(Theif))
				player->addexp(true, 100);
		} else
			player->act("%герой не сумел%а вскрыть замок.");
		logs::next();
		checkencounter();
	}

	void takeall(character* player) {
	}

	void featurefocus() {
		while(ispartyready()) {
			act(feature->examine);
			if(is(Locked) && feature->locked)
				act(feature->locked);
			ask(GoBack, "Отойти назад");
			if(is(Locked))
				ask(OpenLocks, "Попытаться вскрыть замок");
			tag id = logs::input(true, false, "Что будете делать?");
			auto player = choose(true, id);
			auto result = player->roll(id);
			logs::clear(true);
			switch(id) {
			case tag(OpenLocks):
				passtime(true, Duration1Turn);
				picklock(player, result);
				break;
			case tag(GoBack):
				return;
			}
		}
	}

	void clear() {
		memset(this, 0, sizeof(*this));
	}

};
typedef adat<room, 12> rooma;

static void generate(rooma& rooms, treasure& te) {
	// Random rooms preapare
	const unsigned room_maximum = sizeof(room_data) / sizeof(room_data[0]);
	roominfo* ri[room_maximum];
	for(unsigned i = 0; i < room_maximum; i++)
		ri[i] = room_data + i;
	zshuffle(ri, room_maximum);
	// Random place prepare
	const unsigned place_maximum = sizeof(place_data) / sizeof(place_data[0]);
	placeinfo* pi[place_maximum];
	for(unsigned i = 0; i < place_maximum; i++)
		pi[i] = place_data + i;
	zshuffle(pi, place_maximum);
	// Random traps prepare
	const unsigned trap_maximum = sizeof(trap_data) / sizeof(trap_data[0]);
	trapinfo* ti[trap_maximum];
	for(unsigned i = 0; i < trap_maximum; i++)
		ti[i] = trap_data + i;
	zshuffle(ti, trap_maximum);
	// Prepare hoard
	auto current_hoard = te.items;
	auto current_hoard_end = te.items + sizeof(te.items) / sizeof(te.items[0]);
	// Generate dungeon
	rooms.count = 1 + (rand() % sizeof(rooms.data) / sizeof(rooms.data[0]));
	if(rooms.count < 4)
		rooms.count = 4;
	for(unsigned i = 0; i < rooms.count; i++) {
		auto& e = rooms.data[i];
		e.clear();
		e.set(HiddenTrap);
		e.set(HiddenSecret);
		// Set common types of rooms
		e.type = ri[i%room_maximum];
		e.feature = pi[i%place_maximum];
		// Set locked
		if(e.feature->locked && d100() < 60)
			e.set(Locked);
		// Set loot
		e.loots.data = current_hoard;
		e.loots.count = xrand(1, 5);
		if(e.loots.data + e.loots.count > current_hoard_end)
			e.loots.count = current_hoard_end - e.loots.data;
		// Set trap
		if(d100() < 50)
			e.trap = ti[i%trap_maximum];
		// Set guard
		if(d100() < 40)
			e.set(Guardians);
	}
}

static void dungeon_adventure(rooma& rooms) {
	logs::state push;
	logc.information = "%party";
	char temp[260];
	unsigned char room_index = 0;
	while(ispartyready()) {
		room& r = rooms[room_index];
		r.lookaround();
		if(r.feature)
			r.ask(ExamineFeature, "Осмотреть [%1] поближе.", r.feature->name);
		if(room_index > 0)
			r.ask(GoBack, "Вернуться назад");
		if(room_index < rooms.count - 1)
			r.ask(GoNext, "Двигаться вперед");
		if(r.is(HiddenTrap))
			r.ask(FindRemoveTraps, "Обыскать комнату в надежде найти ловушки.");
		else if(r.trap)
			r.ask(FindRemoveTraps, "Попытаться обезвредить ловушку.");
		if(r.is(HiddenSecret))
			logs::add(tag(FindSecretDoors), "Обыскать комнату на наличие секретных дверей.");
		logs::add(tag(Charsheet), "Посмотреть листок персонажа.");
		logs::add(tag(MakeCamp), "Сделать здесь привал.");
		tag id = logs::input(true, false, "Что будете делать?");
		auto player = choose(true, id);
		auto result = player->roll(id);
		logs::clear(true);
		switch(id) {
		case tag(FindSecretDoors):
			passtime(true, Duration1Turn);
			r.findsecrets(player, result);
			break;
		case tag(FindRemoveTraps):
			if(r.is(HiddenTrap)) {
				passtime(true, Duration1Turn);
				r.findtraps(player, result);
			} else
				r.removetraps(player, result);
			break;
		case tag(ExamineFeature):
			passtime(true, Duration1Round);
			r.act("Вы подошли к %1 поближе.", grammar::to(temp, r.feature->name));
			r.checktrap(player);
			r.featurefocus();
			break;
		case tag(GoBack):
			if(room_index == 0)
				return;
			logs::add("Вы вышли из %1 и двинулись назад по узкому проходу.",
				grammar::of(temp, rooms[room_index].type->name));
			room_index--; passtime(true, Duration1Turn);
			rooms[room_index].checkguard();
			logs::add("Вы вернулись в %1.", rooms[room_index].type->name);
			break;
		case tag(GoNext):
			if(room_index >= (rooms.count - 1))
				break;
			logs::add("Вы вышли из %1 и двинулись дальше по узкому извилистому проходу.",
				grammar::of(temp, rooms[room_index].type->name));
			room_index++; passtime(true, Duration1Turn);
			rooms[room_index].checkguard();
			logs::add("Вы вышли в %1.", rooms[room_index].type->name);
			break;
		case tag(Charsheet):
			charsheet();
			break;
		case tag(MakeCamp):
			break;
		}
	}
}

template<> void archive::set<room>(room& value) {
	set(value.type);
	set(value.trap);
	set(value.feature);
	set(value.getflags());
	set(value.loots);
}

static bool serialize(const char* name, bool writemode, treasure& loots, rooma& rooms) {
	archive::dataset datasets[] = {
		place_data, room_data, trap_data, loots.items,
		rooms,
	};
	io::file file(name, writemode ? StreamWrite : StreamRead);
	if(!file)
		return false;
	archive serial(file, writemode, datasets);
	if(!serial.signature("DUN"))
		return false;
	if(!serial.version(0, 8))
		return false;
	serial.set(loots);
	serial.set(rooms);
	return true;
}

void game::dungeon() {
	rooma rooms;
	treasure loots;
	if(!serialize("maps/dn0101.dat", false, loots, rooms)) {
		loots.generate("DEF");
		generate(rooms, loots);
		if(!serialize("maps/dn0101.dat", true, loots, rooms))
			return;
	}
	dungeon_adventure(rooms);
}