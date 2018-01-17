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
struct trapinfo {
	const char*		text;
	const char*		activate;
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
	{"�� ����� �� ���� ���������� ��������� ��� ����� ������ � ������������ ����������.", "�� ��������� ����� �� ���� �������� ������."},
	{"�� ���� ���� ��� ��������� �� ������� ��������� ������ ���� �������.", "�������� �� ���� ������� ������."},
};

struct room : placeflags {

	roominfo*	type;
	trapinfo*	trap;
	placeinfo*	feature;

	room() : type(0), trap(0) {
	}

	void lookaround() {
		logs::add(type->text);
		if(feature)
			act(feature->text);
		if(trap && !is(HiddenTrap))
			logs::add(trap->text);
	}

	void act(const char* format, ...) {
		stringcreator sc;
		logs::addv(sc, format, xva_start(format));
	}

	void ask(int id, const char* format, ...) {
	}

	void checkencounter() {
		if(d10() <= 1) {
		}
	}

	void checkguard() {
		if(is(Guardians)) {
			remove(Guardians);
		}
	}

	void checktrap() {
		if(!trap)
			return;
		// player->act(trap->activate);
		remove(HiddenTrap);
	}

	void findsecrets() {
		//player->act("%����� �������%� ������� �");
		//if(result) {
		//	player->act("���������%� [��������� �����].");
		//	remove(HiddenSecret);
		//	if(player->get(Theif))
		//		player->addexp(true, 25);
		//} else
		//	player->act("�� ���������%� ������ �����������.");
		//checkencounter();
	}

	void findtraps() {
		//player->act("%����� �������%� ������� �");
		//if(result && trap) {
		//	remove(HiddenTrap);
		//	player->act("���������%� [�������].");
		//	player->addexp(true, 20);
		//} else
		//	player->act("�� ���������%� ������� �������.");
		//checkencounter();
	}

	void removetraps() {
		//player->act("%����� ������%� ����� � �������� � �������%��� �� �����������.");
		//passtime(true, Duration1Turn);
		//if(result) {
		//	player->act("������ ������� ���� �����������.");
		//	if(player->get(Theif))
		//		player->addexp(true, 80);
		//	trap = 0;
		//} else
		//	player->act("������ �� �����.");
		//checkencounter();
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
			//ask(GoBack, "������ �����");
			//if(is(Locked))
			//	ask(OpenLocks, "���������� ������� �����");
			auto id = logs::input(true, false, "��� ������ ������?");
			logs::clear(true);
			//switch(id) {
			//case tg(OpenLocks):
			//	passtime(true, Duration1Turn);
			//	picklock(player, result);
			//	break;
			//case tg(GoBack):
			//	return;
			//}
		}
	}

	void clear() {
		memset(this, 0, sizeof(*this));
	}

};
typedef adat<room, 12> rooma;

static void generate(rooma& rooms) {
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
		// Set trap
		if(d100() < 50)
			e.trap = ti[i%trap_maximum];
		// Set guard
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
		//if(r.feature)
		//	r.ask(ExamineFeature, "��������� [%1] �������.", r.feature->name);
		if(room_index > 0)
			logs::add(GoBack, "��������� �����");
		if(room_index < rooms.count - 1)
			logs::add(GoNext, "��������� ������");
		//if(r.is(HiddenTrap))
		//	r.ask(FindRemoveTraps, "�������� ������� � ������� ����� �������.");
		//else if(r.trap)
		//	r.ask(FindRemoveTraps, "���������� ����������� �������.");
		//if(r.is(HiddenSecret))
		//	logs::add(tg(FindSecretDoors), "�������� ������� �� ������� ��������� ������.");
		logs::add(MakeCamp, "������� ����� ������.");
		logs::add(Charsheet, "���������� ������ ���������.");
		auto id = (move_s)logs::input(true, false, "��� ������ ������?");
		auto player = choose(id);
		auto result = player->roll(id);
		logs::clear(true);
		switch(id) {
		//case FindSecretDoors:
		//	passtime(Duration10Minute);
		//	r.findsecrets(player, result);
		//	break;
		//case tg(FindRemoveTraps):
		//	if(r.is(HiddenTrap)) {
		//		passtime(true, Duration1Turn);
		//		r.findtraps(player, result);
		//	} else
		//		r.removetraps(player, result);
		//	break;
		//case tg(ExamineFeature):
		//	passtime(true, Duration1Round);
		//	r.act("�� ������� � %1 �������.", grammar::to(temp, r.feature->name));
		//	r.checktrap(player);
		//	r.featurefocus();
		//	break;
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
		}
	}
}

void game::dungeon() {
	rooma rooms; generate(rooms);
	dungeon_adventure(rooms);
}