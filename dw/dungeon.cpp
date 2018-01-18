#include "main.h"
#include "stringcreator.h"

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
struct secretinfo {
	const char*		text;
};
struct trapinfo {
	const char*		text;
	const char*		activate;
	bool			all_party;
	stat_s			stat;
	dice			damage;
};
static placeinfo place_data[] = {
	{"саркофаг", "Около стены находился большой каменный саркофаг.", "Похоже его крышка была закрыта на какой-то хитроумный замок.", "Саркофаг содержал какие-то фрески непонятного содержимого и был сделан из камня."},
	{"сундук", "В углу стояло несколько сундуков, окованных железом.", "Почти все были открыты и там не было ничего ценного, но на одном, самом большом висел огромный железный замок.", "Сундук был огромный и оббит металическими прутьями."},
	{"жертвенник", "Посредине стояло некое подобие жертвенника рядом с которым стояло несколько урн.", 0, "Жертвенник был сделан из черного камня. Со временем камень потрескался и треснул."},
	{"мусор", "В углу находилась большая куча мусора, покрытая вончей слизью. От кучи исходил сильный аромат.", 0, "Среди мусора было видно множество гнилых остатков еды. Вполне возможно в мусоре копошились какие-то жуки или букашки. Вонь была невыносимая."},
	{"колодец", "Посредине стоял каменный колодец.", 0, "Заглянув внутрь вы увидели что на расстоянии 2-3 метра блестит вода. Она черного цвета."},
	{"стол", "Повсюду были остатки старой и прогнившей мебели. Прямо посредине стоял дубовый стол, который неплохо сохранился.", 0, "Стол был крепкий и в довольно хорошем состоянии."},
};
static roominfo room_data[] = {
	{"комната", "Вы находились в небольшой комнате, размером 4 на 4 метра."},
	{"зал", "Вы были в огромном зале, слегка освещенным факелами."},
	{"комната", "Вокруг комната примерно 10 метров шириной. Судя по обломкам интрументов здесь когда-то была темница."},
	{"библиотека", "Вокруг вас была круглая комната с расставленнмыми вокруг стен гнилыми стеллажами. Похоже когда-то здесь стояли книги, но мощный пожар их уничтожил."},
	{"зал", "Вы стояли в зале, с белыми мраморными колонами. На стенах была видна мозаика, которая изображала брутальные сцены убийства."},
};
static trapinfo trap_data[] = {
	{"На одной из стен находились отверстия для пуска стрелы в неудачливого посетителя.", "Из отверстия одной из стен вылетела стрела.", false, Dexterity, {1, 6}},
	{"На полу были три отверстия из которых вылезжали лезвия метр длинной.", "Внезапно из пола выехали лезвия.", true, Dexterity, {2, 6}},
};
static secretinfo secret_data[] = {
	{"На одной из стен находилась подозрительная маленькая кнопка."},
	{"Часть стены похоже проворачивалась и возможно за ней находилось скрытое помещение."},
};
struct room : placeflags {

	roominfo*	type;
	trapinfo*	trap;
	secretinfo*	secret;
	placeinfo*	feature;

	room() : type(0), trap(0) {
	}

	void lookaround() {
		logs::add(type->text);
		if(feature)
			act(feature->text);
		if(secret && !is(HiddenSecret))
			act(secret->text);
		if(trap && !is(HiddenTrap))
			logs::add(trap->text);
	}

	void act(const char* format, ...) {
		stringcreator sc;
		logs::addv(sc, format, xva_start(format));
	}

	void ask(move_s id, const char* format, ...) {
		if(!isallow(id))
			return;
		stringcreator sc;
		logs::addv(id, sc, format, xva_start(format));
	}

	void encounter() {
		monster e(Goblin);
		e.distance = Close;
		combat(e);
	}

	void checkguard() {
		if(is(Guardians)) {
			remove(Guardians);
		}
	}

	void trapeffect(hero& e) {
		auto damage = trap->damage.roll();
		switch(e.defydanger(trap->stat)) {
		case Success:
			e.act("%герой смог%ла отпрыгнуть в сторону.");
			break;
		case PartialSuccess:
			e.sufferharm(damage / 2);
			break;
		default:
			e.sufferharm(damage);
			break;
		}
	}

	void checktrap() {
		if(!trap)
			return;
		act(trap->activate);
		if(trap->all_party) {
			for(auto& e : players) {
				if(!e.iscombatable())
					continue;
				trapeffect(e);
			}
		} else {
			auto p = getplayer();
			if(p)
				trapeffect(*p);
		}
		remove(HiddenTrap);
	}

	void discernreality() {
		auto player = choose(DiscernRealities);
		if(!player)
			return;
		auto result = player->roll(DiscernRealities);
		player->act("%герой обыскал%а комнату и ");
		auto find = 0;
		if(secret && result >= Success) {
			if(find == 0)
				player->act("обнаружил%а");
			else
				player->act(" и ");
			player->act("[секрет]");
			remove(HiddenSecret);
			find++;
		}
		if(trap && result >= PartialSuccess) {
			if(!find)
				player->act("обнаружил%а");
			else
				player->act(" и ");
			player->act("[ловушку]");
			remove(HiddenTrap);
			find++;
		}
		if(!find)
			player->act("не обнаружил%а ничего интересного");
		player->act(".");
		if(result==Fail)
			encounter();
	}

	void removetraps() {
		auto player = choose(TrapExpert);
		if(!player)
			return;
		auto result = player->roll(TrapExpert);
		player->act("%герой присел%а рядом с ловушкой и попытал%ась ее обезвредить.");
		passtime(Duration10Minute);
		if(result>=PartialSuccess) {
			player->act("Вскоре ловушка была обезврежена.");
			trap = 0;
			if(result == PartialSuccess) {
				logs::add("Но на последок она сработала.");
				trapeffect(*player);
			}
		}
		if(result==Fail)
			encounter();
	}

	void picklock() {
		//if(result) {
		//	player->act("%герой вскрыл%а замок.");
		//	remove(Locked);
		//	if(player->get(Theif))
		//		player->addexp(true, 100);
		//} else
		//	player->act("%герой не сумел%а вскрыть замок.");
		//checkencounter();
	}

	void takeall() {
	}

	void featurefocus() {
		while(!isgameover()) {
			act(feature->examine);
			if(is(Locked) && feature->locked)
				act(feature->locked);
			ask(GoBack, "Отойти назад");
			if(is(Locked))
				ask(TricksOfTheTrade, "Попытаться вскрыть замок");
			auto id = (move_s)logs::input(true, false, "Что будете делать?");
			logs::clear(true);
			switch(id) {
			case TricksOfTheTrade:
				passtime(Duration1Minute);
				picklock();
				break;
			case GoBack:
				return;
			}
		}
	}

	void clear() {
		memset(this, 0, sizeof(*this));
	}

};
typedef adat<room, 12> rooma;

static void generate(rooma& rooms) {
	// Random rooms preapare
	const unsigned room_maximum = lenghtof(room_data);
	roominfo* ri[room_maximum];
	for(unsigned i = 0; i < room_maximum; i++)
		ri[i] = room_data + i;
	zshuffle(ri, room_maximum);
	// Random place prepare
	const unsigned place_maximum = lenghtof(place_data);
	placeinfo* pi[place_maximum];
	for(unsigned i = 0; i < place_maximum; i++)
		pi[i] = place_data + i;
	zshuffle(pi, place_maximum);
	// Random traps prepare
	const unsigned trap_maximum = lenghtof(trap_data);
	trapinfo* ti[trap_maximum];
	for(unsigned i = 0; i < trap_maximum; i++)
		ti[i] = trap_data + i;
	zshuffle(ti, trap_maximum);
	// Random secret prepare
	const unsigned secret_maximum = lenghtof(secret_data);
	secretinfo* si[secret_maximum];
	for(unsigned i = 0; i < secret_maximum; i++)
		si[i] = secret_data + i;
	zshuffle(si, secret_maximum);
	// Generate dungeon
	rooms.count = 1 + (rand() % sizeof(rooms.data) / sizeof(rooms.data[0]));
	if(rooms.count < 4)
		rooms.count = 4;
	for(unsigned i = 0; i < rooms.count; i++) {
		auto& e = rooms.data[i];
		e.clear();
		e.set(HiddenTrap);
		e.set(HiddenSecret);
		e.type = ri[i%room_maximum];
		e.secret = si[i%secret_maximum];
		e.feature = pi[i%place_maximum];
		if(e.feature->locked && d100() < 60)
			e.set(Locked);
		if(d100() < 50)
			e.trap = ti[i%trap_maximum];
		if(d100() < 40)
			e.set(Guardians);
	}
}

static void dungeon_adventure(rooma& rooms) {
	char temp[260];
	unsigned char room_index = 0;
	while(!isgameover()) {
		room& r = rooms[room_index];
		r.lookaround();
		r.ask(ExamineFeature, "Осмотреть [%1] поближе.", r.feature->name);
		if(room_index > 0)
			logs::add(GoBack, "Вернуться назад");
		if(room_index < rooms.count - 1)
			logs::add(GoNext, "Двигаться вперед");
		r.ask(TrapExpert, "Внимательно изучить комнату.");
		if(r.trap && !r.is(HiddenTrap))
			r.ask(TricksOfTheTrade, "Обезвредить ловушку.");
		logs::add(MakeCamp, "Сделать здесь привал.");
		logs::add(Charsheet, "Посмотреть листок персонажа.");
		auto id = (move_s)logs::input(true, false, "Что будете делать?");
		logs::clear(true);
		switch(id) {
		case TrapExpert:
			passtime(Duration10Minute);
			r.discernreality();
			break;
		case TricksOfTheTrade:
			r.removetraps();
			break;
		case ExamineFeature:
			passtime(Duration1Minute);
			r.act("Вы подошли к %1 поближе.", grammar::to(temp, r.feature->name));
			r.checktrap();
			r.featurefocus();
			break;
		case GoBack:
			if(room_index == 0)
				return;
			logs::add("Вы вышли из %1 и двинулись назад по узкому проходу.",
				grammar::of(temp, rooms[room_index].type->name));
			room_index--; passtime(Duration10Minute);
			rooms[room_index].checkguard();
			logs::add("Вы вернулись в %1.", rooms[room_index].type->name);
			break;
		case GoNext:
			if(room_index >= (rooms.count - 1))
				break;
			logs::add("Вы вышли из %1 и двинулись дальше по узкому извилистому проходу.",
				grammar::of(temp, rooms[room_index].type->name));
			room_index++; passtime(Duration10Minute);
			rooms[room_index].checkguard();
			logs::add("Вы вышли в %1.", rooms[room_index].type->name);
			break;
		case Charsheet:
			//charsheet();
			break;
		case MakeCamp:
			makecamp();
			passtime(Duration1Hour);
			break;
		}
	}
}

void game::dungeon() {
	rooma rooms; generate(rooms);
	dungeon_adventure(rooms);
}