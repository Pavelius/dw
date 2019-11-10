#include "main.h"

using namespace game;

enum flag_s : unsigned char {
	Locked, UseDiscentReality, HiddenTrap, HiddenSecret, Guardians,
};
enum room_s : unsigned char {
	Corridor, Secret,
};
struct action {
	tid				id;
	const char*		text;
	effect_s		effect; // ������ � ������ ������ ��� ���������� ������
};
struct roominfo {
	room_s			type;
	const char*		name;
	const char*		text;
	aref<action>	actions;
};
struct featureinfo {
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
static action strange_feature[] = {
	{DiscernRealities, "�� ����� �� ������ �� �������� �������� �������. ������ ����� ���� ���� � ������� ����� ���������� ���������. ���� ��� � ���, ��� �������� �������� ����� [�������]."},
};
static featureinfo place_data[] = {{"��������", "����� ����� ��������� ������� �������� ��������.", "������ ��� ������ ���� ������� �� �����-�� ���������� �����.", "�������� �������� �����-�� ������ ����������� ����������� � ��� ������ �� �����."},
{"������", "� ���� ������ ��������� ��������, ��������� �������.", "����� ��� ���� ������� � ��� �� ���� ������ �������, �� �� �����, ����� ������� ����� �������� �������� �����.", "������ ��� �������� � ����� ������������� ��������."},
{"����������", "��������� ������ ����� ������� ����������� ����� � ������� ������ ��������� ���.", 0, "���������� ��� ������ �� ������� �����. �� �������� ������ ����������� � �������."},
{"�����", "� ���� ���������� ������� ���� ������, �������� ������ ������. �� ���� ������� ������� ������.", 0, "����� ������ ���� ����� ��������� ������ �������� ���. ������ �������� � ������ ���������� �����-�� ���� ��� �������. ���� ���� �����������."},
{"�������", "��������� ����� �������� �������.", 0, "�������� ������ �� ������� ��� �� ���������� 2-3 ����� ������� ����. ��� ������� �����."},
{"����", "������� ���� ������� ������ � ���������� ������. ����� ��������� ����� ������� ����, ������� ������� ����������.", 0, "���� ��� ������� � � �������� ������� ���������."},
};
static roominfo room_data[] = {{Corridor, "�������", "�� ���������� � ��������� �������, �������� 4 �� 4 �����.", strange_feature},
{Corridor, "���", "�� ���� � �������� ����, ������ ���������� ��������."},
{Corridor, "�������", "������ ������� �������� 10 ������ �������. ���� �� �������� ����������� ����� �����-�� ���� �������."},
{Corridor, "����������", "������ ��� ���� ������� ������� � ��������������� ������ ���� ������� ����������. ������ �����-�� ����� ������ �����, �� ������ ����� �� ���������."},
{Corridor, "��� � ��������", "�� ������ � ����, � ������ ���������� ��������. �� ������ ���� ����� �������, ������� ���������� ���������� ����� ��������."},
};
static roominfo secret_room_data[] = {{Secret, "�������", "�� ������� � ��������� ��������, ������� ����� 3 ������. ������� ��� ����� ������, ������� ������ �� ���� ���� � ��� �� ����������."},
{Secret, "�������", "�� ��������� � ������� �������. ������ ������� ����� ���� ������ ����� ������ ���������������� �����."},
};
static trapinfo trap_data[] = {{"�� ����� �� ���� ���������� ��������� ��� ����� ������ � ������������ ����������.", "�� ��������� ����� �� ���� �������� ������.", false, Dexterity, {1, 6}},
{"�� ���� ���� ��� ��������� �� ������� ��������� ������ ���� �������.", "�������� �� ���� ������� ������.", true, Dexterity, {2, 6}},
};
static secretinfo secret_data[] = {{"�� ����� �� ���� %����� �������%� �������������� ��������� ������. ��� ������ �������� �� �� �����. � ���� ������ �������� ������� ������ � ����� ����� �������� �������� �����, ������� ����� ������ ������� � �������.", "�� ����� �� ���� ��� ����� ����� �������� ������, �������� ����-�� � �������.", "�� ����� ��������� ������, ������� � ������� ��������."},
{"%����� �������%�, ��� ������������ ��������� � ���� ������ �������� ���������. ������� �� ���� %��� ������%� ��� ����� ����� �� ��������� ������������, ������� �������� ������.", "����� ����� ���� ���������� � �� ��� ��� ����� �������� ������.", "�� ����� ���������� ����� ������� � ��������."},
{"��������� ��� ����� %����� �������%�, ��� ��� ���� ���-�� ����. ����� ����� �� ���� �� ���������� ��� �������� ���. �������� ������ �� ��� ������� � ������� ����� �������� �������.", "�� ���� ��������� ��� ��������� ���������.", "�� ������� ���������� ���������, ����� ������� �� ���� ����������."},
{"%����� ���������%�, ��� ���� �� ������ �������� ���-�� �������������. ������� ���, �� ������, ��� �� ������������. ��� ����� ��������� ��� �� ���������� ��������� ����."},
};

struct room : cflags<flag_s, unsigned char> {

	unsigned char	level;
	roominfo*		type;
	trapinfo*		trap;
	secretinfo*		secret;
	featureinfo*	feature;
	lootinfo		loot;
	room*			passage;
	room*			hidden_passage;

	void act(const char* format, ...) {
		logs::addv(format, xva_start(format));
	}

	void ask(move_s id, const char* format, ...) {
		if(!isallow(id))
			return;
		logs::addv(tid(id), 0, format, xva_start(format));
	}

	const action* getaction(move_s id) const {
		for(auto& e : type->actions) {
			if(e.id.type == Moves && e.id.value == id)
				return &e;
		}
		return 0;
	}

	bool encounter() {
		monster e(getmonster());
		e.distance = Close;
		return combat(e);
	}

	bool checkguard() {
		if(is(Guardians)) {
			logs::add("�������� ������� ���������� �����.");
			if(!encounter())
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
		add(UseDiscentReality);
		passtime(Duration10Minute);
		if(is(HiddenSecret) && secret && result >= PartialSuccess) {
			remove(HiddenSecret);
			player->act(secret->activate);
			if(!secret->text)
				takeloot(level + 1);
			else
				logs::next();
		} else
			player->act("%����� ������%� ������� � �� ��������%� ������� ��������.");
		if(result >= Success) {
			auto pa = getaction(DiscernRealities);
			if(pa) {
				player->act(pa->text);
			} else {
				player->act("������������ �������� ��������� �������� ��� ��������� ���������� �� ���� ���������. ���� ��������� ������ %����� ����� ������ � +1.");
				player->set(AnyRoll, player->get(AnyRoll) + 1);
			}
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
			passtime(Duration10Minute);
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
				loot.getitems(logs::getbuilder(), false);
			}
			logs::add(tid(GoBack), "������ �����");
			if(is(Locked))
				ask(TricksOfTheTrade, "���������� ������� �����");
			if(!is(Locked) && loot)
				logs::add(tid(ExamineFeature), "����� ��� ����.");
			tid id = logs::input(true, true, "��� ������ ������?");
			if(id.type == Moves) {
				switch(id.value) {
				case TricksOfTheTrade: picklock(); break;
				}
			} else if(id.type == DungeonMoves) {
				switch(id.value) {
				case ExamineFeature: takeall(); break;
				case GoBack: return;
				}
			}
		}
	}

	void clear() {
		memset(this, 0, sizeof(*this));
	}

	monster_s getmonster() const {
		static monster_s source[] = {Goblin, Kobold, Bandit, Zombie};
		return source[rand() % lenghtof(source)];
	}

};
typedef adat<room, 32> rooma;
typedef adat<const action*, 16> actiona;

static void select(actiona& result, aref<action> actions) {
	for(auto& e : actions) {
		if(!isallow(e.id))
			continue;
		switch(e.id.type) {
		case Moves:
			if(e.id.value == DiscernRealities) // ��� ��, ��� ���������� �� ����� ���� �� 10+
				continue;
			break;
		}
		result.add(&e);
	}
}

static void ask(actiona& result) {
	char temp[260];
	for(unsigned i = 0; i < result.count; i++) {
		auto p = result.data[i]->text;
		if(!p) {
			switch(result.data[i]->id.type) {
			case Moves:
				p = getstr((move_s)result.data[i]->id.value);
				break;
			case Items:
				szprints(temp, temp + sizeof(temp) / sizeof(temp[0]) - 1, "������������ [%1]", getstr((item_s)result.data[i]->id.value));
				break;
			}
		}
		if(p)
			logs::add(tid(Actions, i), p);
	}
}

static void resolve(move_s id) {
	auto player = choose(id);
	if(!player)
		return;
	auto result = player->roll(id);
	if(result >= Success) {
		passtime(Duration1Minute);
	} else if(result >= PartialSuccess) {
		passtime(Duration30Minute);
	} else {
		passtime(Duration10Minute);
	}
}

static void resolve(action& a) {
	switch(a.id.type) {
	case Moves: resolve((move_s)a.id.value); break;
	}
}

template<> void archive::set<room>(room& e) {
	set(e.data);
	set(e.level);
}

struct dungeon_info {

	rooma rooms;

	void adventure() {
		char temp[260];
		auto pr = rooms.data;
		actiona actions;
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
				logs::add(tid(GoNext), "��������� ������ �� �������");
			if(back_passage)
				logs::add(tid(GoBack), "��������� ����� �� �������.");
			else if(isexit) {
				logs::add("� ������� ���� ���������� ��������, ������� ������.");
				logs::add(tid(GoBack), "��������� ����� �� ��������.");
			}
			// ����������� �������
			if(pr->feature) {
				pr->act(pr->feature->text);
				logs::add(tid(ExamineFeature), "��������� [%1] �������.", pr->feature->name);
			}
			// ������ ������� � ��������� �����
			if(pr->secret && pr->secret->text && !pr->is(HiddenSecret)) {
				pr->act(pr->secret->text);
				logs::add(tid(GoHiddenPass), "������ �� ������� �������.");
			}
			if(back_hidden_passage && back_hidden_passage->secret && back_hidden_passage->secret->text) {
				pr->act(back_hidden_passage->secret->text_back);
				logs::add(tid(GoHiddenPassBack), "��������� ����� �� ������� �������.");
			}
			// �������
			if(pr->is(HiddenTrap))
				pr->ask(TrapExpert, "�������� �������.");
			else if(pr->trap) {
				pr->act(pr->trap->text);
				pr->ask(TricksOfTheTrade, "����������� �������.");
			}
			if(!pr->is(UseDiscentReality))
				pr->ask(DiscernRealities, "����������� ������� �������.");
			// ��������
			actions.clear();
			select(actions, pr->type->actions); ask(actions);
			logs::add(tid(MakeCamp), "������� ����� ������.");
			logs::add(tid(Charsheet), "���������� ������ ���������.");
			tid id = logs::input(true, false, "��� ������ ������?");
			logs::clear(true);
			if(id.type == Moves) {
				switch(id.value) {
				case DiscernRealities: pr->discernreality(); break;
				case TricksOfTheTrade: pr->removetraps(); break;
				case TrapExpert: pr->findtraps(); break;
				}
			} else if(id.type == DungeonMoves) {
				switch(id.value) {
				case ExamineFeature:
					passtime(Duration1Minute);
					pr->act("�� ������� � %1 �������.",
						stringbuilder::addto(temp, zendof(temp), pr->feature->name));
					pr->checktrap();
					pr->featurefocus();
					break;
				case GoBack:
					if(!back_passage)
						return;
					logs::add("�� ����� �� %1 � ��������� ����� �� ������ �������.",
						stringbuilder::addof(temp, zendof(temp), pr->type->name));
					pr = back_passage;  passtime(Duration10Minute);
					pr->checkguard();
					logs::add("�� ��������� � %1.", pr->type->name);
					break;
				case GoNext:
					if(!pr->passage)
						break;
					logs::add("�� ����� �� %1 � ��������� ������ �� ������ ����������� �������.",
						stringbuilder::addof(temp, zendof(temp), pr->passage->type->name));
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
					sheets();
					break;
				case MakeCamp:
					makecamp();
					passtime(Duration1Hour);
					break;
				}
			} else if(id.type == Actions) {

			}
		}
	}

	void generate() {
		auto level = 1;
		auto chance_locked = 60;
		auto chance_trapped = 40;
		auto chance_guarded = 30;
		auto chance_secret = 30;
		// Random rooms preapare
		const unsigned room_maximum = lenghtof(room_data);
		roominfo* ri[room_maximum];
		for(unsigned i = 0; i < room_maximum; i++)
			ri[i] = room_data + i;
		zshuffle(ri, room_maximum);
		// Random place prepare
		const unsigned place_maximum = lenghtof(place_data);
		featureinfo* pi[place_maximum];
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
			e.level = level;
			e.add(HiddenTrap);
			e.add(HiddenSecret);
			if(i < secret_start - 1)
				e.passage = rooms.data + i + 1;
			e.type = ri[i%room_maximum];
			if(i >= secret_start)
				e.type = sr[i%secret_room_maximum];
			e.feature = pi[i%place_maximum];
			auto current_chance_loot = 60;
			if(d100() < chance_locked && e.feature->locked) {
				current_chance_loot = 100;
				e.add(Locked);
			}
			if(d100() < chance_trapped)
				e.trap = ti[i%trap_maximum];
			if(d100() < chance_guarded)
				e.add(Guardians);
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

};

char* getfn(char* result, const char* result_maximum, short unsigned index) {
	zcpy(result, "maps/");
	szprints(zend(result), result_maximum, "dn%1i.map", index);
	return result;
}

bool write_dungeon(short unsigned index, rooma& rooms) {
	char temp[260];
	io::file file(getfn(temp, temp + sizeof(temp) - 1, index), StreamWrite);
	if(!file)
		return false;
	archive e(file, true);
	e.set(rooms);
	return true;
}

void game::dungeon() {
	dungeon_info e;
	e.generate();
	write_dungeon(101, e.rooms);
	e.adventure();
}