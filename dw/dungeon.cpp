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
	{"��������", "����� ����� ��������� ������� �������� ��������.", "������ ��� ������ ���� ������� �� �����-�� ���������� �����.", "�������� �������� �����-�� ������ ����������� ����������� � ��� ������ �� �����."},
	{"������", "� ���� ������ ��������� ��������, ��������� �������.", "����� ��� ���� ������� � ��� �� ���� ������ �������, �� �� �����, ����� ������� ����� �������� �������� �����.", "������ ��� �������� � ����� ������������� ��������."},
	{"����������", "��������� ������ ����� ������� ����������� ����� � ������� ������ ��������� ���.", 0, "���������� ��� ������ �� ������� �����. �� �������� ������ ����������� � �������."},
	{"�����", "� ���� ���������� ������� ���� ������, �������� ������ ������. �� ���� ������� ������� ������.", 0, "����� ������ ���� ����� ��������� ������ �������� ���. ������ �������� � ������ ���������� �����-�� ���� ��� �������. ���� ���� �����������."},
	{"�������", "��������� ����� �������� �������.", 0, "�������� ������ �� ������� ��� �� ���������� 2-3 ����� ������� ����. ��� ������� �����."},
	{"����", "������� ���� ������� ������ � ���������� ������. ����� ��������� ����� ������� ����, ������� ������� ����������.", 0, "���� ��� ������� � � �������� ������� ���������."},
};
static roominfo room_data[] = {
	{"�������", "�� ���������� � ��������� �������, �������� 4 �� 4 �����."},
	{"���", "�� ���� � �������� ����, ������ ���������� ��������."},
	{"�������", "������ ������� �������� 10 ������ �������. ���� �� �������� ����������� ����� �����-�� ���� �������."},
	{"����������", "������ ��� ���� ������� ������� � ��������������� ������ ���� ������� ����������. ������ �����-�� ����� ������ �����, �� ������ ����� �� ���������."},
	{"���", "�� ������ � ����, � ������ ���������� ��������. �� ������ ���� ����� �������, ������� ���������� ���������� ����� ��������."},
};
static trapinfo trap_data[] = {
	{"�� ����� �� ���� ���������� ��������� ��� ����� ������ � ������������ ����������.", "�� ��������� ����� �� ���� �������� ������.", false, Dexterity, {1, 6}},
	{"�� ���� ���� ��� ��������� �� ������� ��������� ������ ���� �������.", "�������� �� ���� ������� ������.", true, Dexterity, {2, 6}},
};
static secretinfo secret_data[] = {
	{"�� ����� �� ���� ���������� �������������� ��������� ������."},
	{"����� ����� ������ ��������������� � �������� �� ��� ���������� ������� ���������."},
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
			e.act("%����� ����%�� ���������� � �������.");
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
		player->act("%����� �������%� ������� � ");
		auto find = 0;
		if(secret && result >= Success) {
			if(find == 0)
				player->act("���������%�");
			else
				player->act(" � ");
			player->act("[������]");
			remove(HiddenSecret);
			find++;
		}
		if(trap && result >= PartialSuccess) {
			if(!find)
				player->act("���������%�");
			else
				player->act(" � ");
			player->act("[�������]");
			remove(HiddenTrap);
			find++;
		}
		if(!find)
			player->act("�� ���������%� ������ �����������");
		player->act(".");
		if(result==Fail)
			encounter();
	}

	void removetraps() {
		auto player = choose(TrapExpert);
		if(!player)
			return;
		auto result = player->roll(TrapExpert);
		player->act("%����� ������%� ����� � �������� � �������%��� �� �����������.");
		passtime(Duration10Minute);
		if(result>=PartialSuccess) {
			player->act("������ ������� ���� �����������.");
			trap = 0;
			if(result == PartialSuccess) {
				logs::add("�� �� �������� ��� ���������.");
				trapeffect(*player);
			}
		}
		if(result==Fail)
			encounter();
	}

	void picklock() {
		//if(result) {
		//	player->act("%����� ������%� �����.");
		//	remove(Locked);
		//	if(player->get(Theif))
		//		player->addexp(true, 100);
		//} else
		//	player->act("%����� �� �����%� ������� �����.");
		//checkencounter();
	}

	void takeall() {
	}

	void featurefocus() {
		while(!isgameover()) {
			act(feature->examine);
			if(is(Locked) && feature->locked)
				act(feature->locked);
			ask(GoBack, "������ �����");
			if(is(Locked))
				ask(TricksOfTheTrade, "���������� ������� �����");
			auto id = (move_s)logs::input(true, false, "��� ������ ������?");
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
		r.ask(ExamineFeature, "��������� [%1] �������.", r.feature->name);
		if(room_index > 0)
			logs::add(GoBack, "��������� �����");
		if(room_index < rooms.count - 1)
			logs::add(GoNext, "��������� ������");
		r.ask(TrapExpert, "����������� ������� �������.");
		if(r.trap && !r.is(HiddenTrap))
			r.ask(TricksOfTheTrade, "����������� �������.");
		logs::add(MakeCamp, "������� ����� ������.");
		logs::add(Charsheet, "���������� ������ ���������.");
		auto id = (move_s)logs::input(true, false, "��� ������ ������?");
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
			r.act("�� ������� � %1 �������.", grammar::to(temp, r.feature->name));
			r.checktrap();
			r.featurefocus();
			break;
		case GoBack:
			if(room_index == 0)
				return;
			logs::add("�� ����� �� %1 � ��������� ����� �� ������ �������.",
				grammar::of(temp, rooms[room_index].type->name));
			room_index--; passtime(Duration10Minute);
			rooms[room_index].checkguard();
			logs::add("�� ��������� � %1.", rooms[room_index].type->name);
			break;
		case GoNext:
			if(room_index >= (rooms.count - 1))
				break;
			logs::add("�� ����� �� %1 � ��������� ������ �� ������ ����������� �������.",
				grammar::of(temp, rooms[room_index].type->name));
			room_index++; passtime(Duration10Minute);
			rooms[room_index].checkguard();
			logs::add("�� ����� � %1.", rooms[room_index].type->name);
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