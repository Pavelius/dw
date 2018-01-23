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
static roominfo secret_room_data[] = {
	{"�������", "�� ������� � ��������� ��������, ������� ����� 3 ������. ������� ��� ����� ������, ������� ������ �� ���� ���� � ��� �� ����������."},
	{"�������", "�� ��������� � ������� �������. ������ ������� ����� ���� ������ ����� ������ ���������������� �����."},
};
static trapinfo trap_data[] = {
	{"�� ����� �� ���� ���������� ��������� ��� ����� ������ � ������������ ����������.", "�� ��������� ����� �� ���� �������� ������.", false, Dexterity, {1, 6}},
	{"�� ���� ���� ��� ��������� �� ������� ��������� ������ ���� �������.", "�������� �� ���� ������� ������.", true, Dexterity, {2, 6}},
};
static secretinfo secret_data[] = {
	{"�� ����� �� ���� %����� �������%� �������������� ��������� ������. ��� ������ �������� �� �� �����. � ���� ������ �������� ������� ������ � ����� ����� �������� �������� �����, ������� ����� ������ ������� � �������.", "�� ����� �� ���� ��� ����� ����� �������� ������, �������� ����-�� � �������.", "�� ����� ��������� ������, ������� � ������� ��������."},
	{"%����� �������%�, ��� ������������ ��������� � ���� ������ �������� ���������. ������� �� ���� %��� ������%� ��� ����� ����� �� ��������� ������������, ������� �������� ������.", "����� ����� ���� ���������� � �� ��� ��� ����� �������� ������.", "�� ����� ���������� ����� ������� � ��������."},
	{"%����� ���������%�, ��� ���� �� ������ �������� ���-�� �������������. ������� ���, �� ������, ��� �� �����������. ��� ����� ��������� ��� �� ���������� ��������� ����."},
};
struct room : placeflags {

	unsigned char	level;
	roominfo*		type;
	trapinfo*		trap;
	secretinfo*		secret;
	placeinfo*		feature;
	lootinfo		loot;
	room*			passage;
	room*			hidden_passage;

	bool issecret() const {
		return type >= secret_room_data && type <= secret_room_data + lenghtof(secret_room_data);
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
		monster e(Zombie);
		e.distance = Close;
		combat(e);
	}

	bool checkguard() {
		if(is(Guardians)) {
			logs::add("�������� ������� ���������� �����.");
			monster e(Zombie);
			e.distance = Close;
			if(!combat(e))
				return false;
			remove(Guardians);
		}
		return true;
	}

	void mastermove() {
		logs::add("���� �������� ��������� ������������� ��������.");
		encounter();
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
		if(d100() < 20) {
			logs::add("������� ��������� � ��� ������ �� ���������.");
			trap = 0;
		}
	}

	void takeloot(int level) {
		lootinfo te; te.clear();
		te.generate(xrand(level, level + 8));
		logs::add("����� ������ ");
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
			player->act("%����� ������%� ������� � �� ��������%� ������� ��������.");
		if(result >= Success) {
			player->act("������������ �������� ��������� �������� ��� ��������� ���������� �� ���� ���������. ���� ��������� ������ %����� ����� ������ � +1.");
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
		player->act("%����� ����� ��������%� ������� � ");
		auto find = 0;
		if(trap && result >= PartialSuccess) {
			if(find == 0)
				player->act("���������%�");
			else
				player->act(" � ");
			player->act("[�������]");
			remove(HiddenTrap);
			find++;
		}
		if(!find)
			player->act("�� ���������%� ������� �������");
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
		player->act("%����� ������%� ����� � �������� � �������%��� �� �����������.");
		passtime(Duration10Minute);
		if(result >= PartialSuccess) {
			player->act("������ ������� ���� �����������.");
			if(result == PartialSuccess) {
				logs::add("�� �� �������� ��� ���������.");
				trapeffect(*player); // ������ �� �������� ������
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
			player->act("%����� ��� ������� ������%� �����.");
			remove(Locked);
		} else if(result >= PartialSuccess) {
			passtime(Duration30Minute);
			player->act("%����� ������%� �����, ���� �������� � ��� ����������.");
			remove(Locked);
		} else {
			player->act("%����� �� �����%� ������� �����.");
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
				logs::add("����� �����: ");
				loot.getitems(logs::getptr(), false);
			}
			ask(GoBack, "������ �����");
			if(is(Locked))
				ask(TricksOfTheTrade, "���������� ������� �����");
			if(!is(Locked) && loot)
				logs::add(ExamineFeature, "����� ��� ����.");
			auto id = (move_s)logs::input(true, false, "��� ������ ������?");
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
		return hidden_passage && !is(HiddenSecret);
	}

	void clear() {
		memset(this, 0, sizeof(*this));
	}

};
typedef adat<room, 32> rooma;

static void dungeon_adventure(rooma& rooms) {
	char temp[260];
	auto pr = rooms.data;
	while(!isgameover()) {
		bool isexit = (pr == rooms.data);
		room* back_passage = 0;
		room* back_hidden_passage = 0;
		for(unsigned char i = 0; i < rooms.count; i++) {
			if(rooms.data[i].passage == pr)
				back_passage = rooms.data + i;
			if(!rooms.data[i].is(HiddenSecret) && rooms.data[i].hidden_passage == pr)
				back_hidden_passage = rooms.data + i;
		}
		logs::add(pr->type->text);
		// ������� ������ � �����
		if(pr->passage)
			logs::add(GoNext, "��������� ������ �� �������");
		if(back_passage)
			logs::add(GoBack, "��������� ����� �� �������.");
		else if(isexit) {
			logs::add("� ������� ���� ���������� ��������, ������� ������.");
			logs::add(GoBack, "��������� ����� �� ��������.");
		}
		// ����������� �������
		if(pr->feature) {
			pr->act(pr->feature->text);
			pr->ask(ExamineFeature, "��������� [%1] �������.", pr->feature->name);
		}
		if(pr->secret && pr->secret->text && !pr->is(HiddenSecret))
			pr->act(pr->secret->text);
		// �������
		if(pr->is(HiddenTrap))
			pr->ask(TrapExpert, "�������� �������.");
		else if(pr->trap) {
			pr->act(pr->trap->text);
			pr->ask(TricksOfTheTrade, "����������� �������.");
		}
		if(back_hidden_passage && back_hidden_passage->secret && back_hidden_passage->secret->text)
			pr->act(back_hidden_passage->secret->text_back);
		if(!pr->is(UseDiscentReality))
			pr->ask(DiscernRealities, "����������� ������� �������.");
		if(pr->issecretpass())
			logs::add(GoHiddenPass, "������ �� ������� �������.");
		if(back_hidden_passage)
			logs::add(GoHiddenPassBack, "��������� ����� �� ������� �������.");
		logs::add(MakeCamp, "������� ����� ������.");
		logs::add(Charsheet, "���������� ������ ���������.");
		auto id = (move_s)logs::input(true, false, "��� ������ ������?");
		logs::clear(true);
		switch(id) {
		case DiscernRealities: pr->discernreality(); break;
		case TricksOfTheTrade: pr->removetraps(); break;
		case TrapExpert: pr->findtraps(); break;
		case ExamineFeature:
			passtime(Duration1Minute);
			pr->act("�� ������� � %1 �������.", grammar::to(temp, pr->feature->name));
			pr->checktrap();
			pr->featurefocus();
			break;
		case GoBack:
			if(!back_passage)
				return;
			logs::add("�� ����� �� %1 � ��������� ����� �� ������ �������.",
				grammar::of(temp, pr->type->name));
			pr = back_passage;  passtime(Duration10Minute);
			pr->checkguard();
			logs::add("�� ��������� � %1.", pr->type->name);
			break;
		case GoNext:
			if(!pr->passage)
				break;
			logs::add("�� ����� �� %1 � ��������� ������ �� ������ ����������� �������.",
				grammar::of(temp, pr->passage->type->name));
			if(pr->passage->checkguard()) {
				pr = pr->passage; passtime(Duration10Minute);
				logs::add("�� ����� � %1.", pr->type->name);
			} else
				logs::add("�������� ��������� �����.");
			break;
		case GoHiddenPass:
			passtime(Duration1Minute);
			logs::add("�� ������� � ������ ������.");
			if(pr->hidden_passage->checkguard())
				pr = pr->hidden_passage;
			else
				logs::add("�������� ��������� �����.");
			break;
		case GoHiddenPassBack:
			passtime(Duration1Minute);
			logs::add("�� ��������� ����� �� ������� �������.");
			pr = back_hidden_passage;
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
	auto chance_secret = 80;
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
	// Random secret room prepare
	const unsigned secret_room_maximum = lenghtof(secret_room_data);
	roominfo* sr[secret_room_maximum];
	for(unsigned i = 0; i < secret_room_maximum; i++)
		sr[i] = secret_room_data + i;
	zshuffle(sr, secret_room_maximum);
	// Generate dungeon
	rooms.count = 1 + (rand() % sizeof(rooms.data) / sizeof(rooms.data[0]));
	//if(rooms.count < 4)
		rooms.count = 4;
	auto secret_start = rooms.count;
	for(unsigned i = 0; i < rooms.count; i++) {
		auto& e = rooms.data[i];
		e.clear();
		e.set(HiddenTrap);
		e.set(HiddenSecret);
		if(i < secret_start - 1)
			e.passage = rooms.data + i + 1;
		e.type = ri[i%room_maximum];
		if(i >= secret_start)
			e.type = sr[i%secret_room_maximum];
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
				e.hidden_passage = rooms.data + rooms.count;
			rooms.count++;
		}
	}
}

void game::dungeon() {
	rooma rooms; generate(rooms);
	dungeon_adventure(rooms);
}