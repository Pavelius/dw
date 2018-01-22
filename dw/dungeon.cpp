#include "main.h"

using namespace game;

enum flag_s : unsigned char {
	Locked, UseDiscentReality, HiddenTrap, HiddenSecret, Guardians,
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
	const char*		activate;
	const char*		text;
	const char*		text_back;
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
static roominfo secret_room_data[] = {
	{"комната", "Вы залезли в небольшую компанту, шириной около 3 метров. Потолок был очень низкий, поэтому стоять во весь рост у вас не получиться."},
	{"комната", "Вы оказались в круглой комнате. Вокруг комнаты вдоль стен стояло шесть статуй человекообразных фигур."},
};
static trapinfo trap_data[] = {
	{"На одной из стен находились отверстия для пуска стрелы в неудачливого посетителя.", "Из отверстия одной из стен вылетела стрела.", false, Dexterity, {1, 6}},
	{"На полу были три отверстия из которых вылезжали лезвия метр длинной.", "Внезапно из пола выехали лезвия.", true, Dexterity, {2, 6}},
};
static secretinfo secret_data[] = {
	{"На одной из стен %герой заметил%а подозрительную маленькую кнопку. Без долгих колеаний он ее нажал. В этот момент раздался скрежет камней и часть стены напротив отъехала вверх, обножив узкий проход ведущий в темноту.", "На одной из стен был виден узкий потайной проход, уходящий куда-то в темноту.", "На стене находился проход, ведущий в главный корридор."},
	{"%герой заметил%а, что декоративное украшение в виде факела является подвижным. Потянув за него %она увидел%а как часть стены со скрежетом провернулась, обнажив потайной проход.", "Часть стены была провернута и за ней был виден потайной проход.", "На стене находилась дырка ведущая в корридор."},
	{"%герой обнаружил%а, что один из камней выглядит как-то неестественно. Пошатав его, вы поняли, что он отовигается. Без труда отодвинув его вы обнаружили некоторые вещи."},
};
struct room : placeflags {

	unsigned char	level;
	roominfo*		type;
	trapinfo*		trap;
	secretinfo*		secret;
	placeinfo*		feature;
	lootinfo		loot;
	unsigned char	hidden_pass;

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
		monster e(Zombie);
		e.distance = Close;
		combat(e);
	}

	bool checkguard() {
		if(is(Guardians)) {
			logs::add("Внезапно впереди послышался шерох.");
			monster e(Zombie);
			e.distance = Close;
			if(!combat(e))
				return false;
			remove(Guardians);
		}
		return true;
	}

	void mastermove() {
		logs::add("Ваши действия привлекли нежелательное внимание.");
		encounter();
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
		if(d100() < 20) {
			logs::add("Ловушку заклинило и она больше не сработает.");
			trap = 0;
		}
	}

	void takeloot(int level) {
		lootinfo te; te.clear();
		te.generate(xrand(level, level + 8));
		logs::add("Здесь лежало ");
		te.pickup();
	}

	void discernreality() {
		auto player = choose(DiscernRealities);
		if(!player)
			return;
		auto result = player->roll(DiscernRealities);
		set(UseDiscentReality);
		passtime(Duration10Minute);
		if(is(HiddenSecret) && secret && result >= PartialSuccess) {
			remove(HiddenSecret);
			player->act(secret->activate);
			if(!secret->text)
				takeloot(1);
			else
				logs::next();
		} else
			player->act("%герой изучил%а комнату и не онаружил%а никаких секретов.");
		if(result >= Success) {
			player->act("Внимательное изучение настенных надписей вам некоторую информацию об этом лабиринте.");
			player->set(AnyRoll, player->get(AnyRoll) + 1);
		}
		if(result == Fail)
			mastermove();
	}

	void findtraps() {
		auto player = choose(TrapExpert);
		if(!player)
			return;
		auto result = player->roll(TrapExpert);
		passtime(Duration1Minute);
		player->act("%герой бегло осмотрел%а комнату и ");
		auto find = 0;
		if(trap && result >= PartialSuccess) {
			if(find == 0)
				player->act("обнаружил%а");
			else
				player->act(" и ");
			player->act("[ловушку]");
			remove(HiddenTrap);
			find++;
		}
		if(!find)
			player->act("не обнаружил%а никаких ловушек");
		player->act(".");
		if(result == Fail)
			mastermove();
	}

	void removetraps() {
		if(!trap)
			return;
		auto player = choose(TrapExpert);
		if(!player)
			return;
		auto result = player->roll(TrapExpert);
		player->act("%герой присел%а рядом с ловушкой и попытал%ась ее обезвредить.");
		passtime(Duration10Minute);
		if(result >= PartialSuccess) {
			player->act("Вскоре ловушка была обезврежена.");
			if(result == PartialSuccess) {
				logs::add("Но на последок она сработала.");
				trapeffect(*player); // Только на текущего игрока
			}
			trap = 0;
		}
		if(result == Fail)
			mastermove();
	}

	void picklock() {
		auto player = choose(TricksOfTheTrade);
		if(!player)
			return;
		auto result = player->roll(TricksOfTheTrade);
		if(result >= Success) {
			passtime(Duration1Minute);
			player->act("%герой без проблем вскрыл%а замок.");
			remove(Locked);
		} else if(result >= PartialSuccess) {
			passtime(Duration30Minute);
			player->act("%герой вскрыл%а замок, хотя пришлось с ним повозиться.");
			remove(Locked);
		} else {
			player->act("%герой не сумел%а вскрыть замок.");
			mastermove();
		}
	}

	void takeall() {
		if(loot.coins) {
			hero::addcoins(loot.coins, true);
			logs::next();
		}
		for(auto& e : loot.items) {
			if(e)
				game::pickup(e);
		}
		loot.clear();
	}

	void featurefocus() {
		while(!isgameover()) {
			act(feature->examine);
			if(is(Locked) && feature->locked)
				act(feature->locked);
			if(!is(Locked) && loot) {
				logs::add("Здесь лежит: ");
				loot.getitems(logs::getptr(), false);
			}
			ask(GoBack, "Отойти назад");
			if(is(Locked))
				ask(TricksOfTheTrade, "Попытаться вскрыть замок");
			if(!is(Locked) && loot)
				logs::add(ExamineFeature, "Взять все вещи.");
			auto id = (move_s)logs::input(true, false, "Что будете делать?");
			logs::clear(true);
			switch(id) {
			case TricksOfTheTrade:
				passtime(Duration1Minute);
				picklock();
				break;
			case ExamineFeature:
				takeall();
				break;
			case GoBack:
				return;
			}
		}
	}

	bool issecretpass() const {
		return secret && !is(HiddenSecret) && secret->text && hidden_pass;
	}

	void clear() {
		memset(this, 0, sizeof(*this));
	}

};
typedef adat<room, 32> rooma;

static void dungeon_adventure(rooma& rooms) {
	char temp[260];
	unsigned char room_index = 0;
	while(!isgameover()) {
		room& r = rooms[room_index];
		logs::add(r.type->text);
		if(r.feature)
			r.act(r.feature->text);
		if(r.secret && r.secret->text && !r.is(HiddenSecret))
			r.act(r.secret->text);
		if(r.trap && !r.is(HiddenTrap))
			logs::add(r.trap->text);
		unsigned char hidden_pass_back = 0;
		for(unsigned char i = 0; i < rooms.count; i++) {
			if(rooms.data[i].issecretpass() && rooms.data[i].hidden_pass == room_index) {
				hidden_pass_back = i;
				break;
			}
		}
		if(hidden_pass_back && rooms.data[hidden_pass_back].secret && rooms.data[hidden_pass_back].secret->text_back)
			r.act(rooms.data[hidden_pass_back].secret->text_back);
		r.ask(ExamineFeature, "Осмотреть [%1] поближе.", r.feature->name);
		if(room_index > 0)
			logs::add(GoBack, "Вернуться назад.");
		else if(room_index==0) {
			logs::add("В дальнем углу находилась лестница, ведущая наружу.");
			logs::add(GoBack, "Подняться вверх по лестнице.");
		}
		if(room_index < rooms.count - 1)
			logs::add(GoNext, "Двигаться вперед");
		if(!r.is(UseDiscentReality))
			r.ask(DiscernRealities, "Внимательно изучить комнату.");
		if(r.is(HiddenTrap))
			r.ask(TrapExpert, "Поискать ловушки.");
		if(r.trap && !r.is(HiddenTrap))
			r.ask(TricksOfTheTrade, "Обезвредить ловушку.");
		if(r.issecretpass())
			logs::add(GoHiddenPass, "Пройти по тайному проходу.");
		if(hidden_pass_back && rooms.data[hidden_pass_back].secret->text_back)
			logs::add(GoHiddenPassBack, "Вернуться назад по тайному проходу.");
		logs::add(MakeCamp, "Сделать здесь привал.");
		logs::add(Charsheet, "Посмотреть листок персонажа.");
		auto id = (move_s)logs::input(true, false, "Что будете делать?");
		logs::clear(true);
		switch(id) {
		case DiscernRealities: r.discernreality(); break;
		case TricksOfTheTrade: r.removetraps(); break;
		case TrapExpert: r.findtraps(); break;
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
			if(rooms[room_index].checkguard()) {
				room_index++; passtime(Duration10Minute);
				logs::add("Вы вышли в %1.", rooms[room_index].type->name);
			} else
				logs::add("Пришлось вернуться назад.");
			break;
		case GoHiddenPass:
			logs::add("Вы залезли в тайный проход.");
			if(rooms[r.hidden_pass].checkguard()) {
				passtime(Duration1Minute);
				room_index = r.hidden_pass;
			} else
				logs::add("Пришлось вернуться назад.");
			break;
		case GoHiddenPassBack:
			logs::add("Вы вернулись назад по тайному проходу.");
			room_index = hidden_pass_back;
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

static void generate(rooma& rooms) {
	auto level = 1;
	auto chance_locked = 60;
	auto chance_trapped = 40;
	auto chance_guarded = 40;
	auto chance_secret = 60;
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
	auto secret_start = rooms.count;
	for(unsigned i = 0; i < rooms.count; i++) {
		auto& e = rooms.data[i];
		e.clear();
		e.set(HiddenTrap);
		e.set(HiddenSecret);
		e.type = ri[i%room_maximum];
		e.feature = pi[i%place_maximum];
		auto current_chance_loot = 60;
		if(d100() < chance_locked && e.feature->locked) {
			current_chance_loot = 100;
			e.set(Locked);
		}
		if(d100() < chance_trapped)
			e.trap = ti[i%trap_maximum];
		if(d100() < chance_guarded)
			e.set(Guardians);
		if(d100() < current_chance_loot)
			e.loot.generate(xrand(level, level + 9));
		if(d100() < chance_secret && rooms.count < lenghtof(rooms.data)) {
			e.secret = si[i%secret_maximum];
			if(e.secret->text)
				e.hidden_pass = rooms.count;
		}
	}
}

void game::dungeon() {
	rooma rooms; generate(rooms);
	dungeon_adventure(rooms);
}