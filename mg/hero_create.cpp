#include "main.h"

static struct rang_i {
	struct skillset {
		skill_s		key;
		char		value;
	};
	const char*		id;
	const char*		name;
	unsigned char	age[2];
	skillset		skills[16];
	char			talented;
	char			convice;
	char			mentors;
	char			specialization;
	char			wises;
	char			trait_tender;
	char			trait_leader;
} rang_data[] = {{"Tenderpaws", "����������", {14, 17}, {Nature, 3, Will, 2, Health, 6, Circles, 1, Resources, 1, Pathfinder, 2, Scout, 2, Laborer, 2}, 2, 1, 2, 0, 1, 1, 0},
{"Guardmouse", "��������", {18, 25}, {Nature, 3, Will, 3, Health, 5, Circles, 2, Resources, 2, Fighter, 3, Haggler, 2, Scout, 2, Pathfinder, 3, Survivalist, 2}, 1, 1, 1, 1, 2, 0, 0},
{"Patrol guard", "���������� ��������", {21, 50}, {Nature, 3, Will, 4, Health, 4, Circles, 3, Resources, 3, Cook, 2, Fighter, 3, Hunter, 3, Scout, 2, Healer, 2, Pathfinder, 2, Survivalist, 2, WeatherWatcher, 2}, 1, 1, 1, 1, 3, 0, 1},
{"Patrol leader", "����� �������", {21, 60}, {Nature, 3, Will, 5, Health, 4, Circles, 4, Resources, 3, Fighter, 3, Hunter, 3, Instructor, 2, Loremouse, 2, Persuader, 2, Pathfinder, 3, Scout, 2, Survivalist, 3, WeatherWatcher, 2}, 1, 2, 2, 1, 4, 0, 1},
{"Guard capitan", "������� ����������", {41, 60}, {Nature, 3, Will, 6, Health, 3, Circles, 5, Resources, 4, Administrator, 3, Fighter, 3, Healer, 2, Hunter, 3, Instructor, 2, Militarist, 3, Orator, 2, Pathfinder, 3, Scout, 3, Survivalist, 3, WeatherWatcher, 3}, 2, 2, 1, 1, 6, 0, 1},
};
assert_enum(rang, GuardCapitan);
getstr_enum(rang);

static location_s homeland_locations[] = {Lockhaven, Sprucetuck, Barkstone, Ivydale, Cooperwood, PortSumac, Shaleburrow, Elmoss};
static skill_s trade_skills[] = {Potter, Smith, Weaver, Brewer};
static skill_s communication_skills[] = {Deceiver, Orator, Persuader};
static skill_s artisan_skills[] = {
	Apiarist, Archivist, Armorer, Baker, Brewer,
	Carpenter, Cartographer, Glazier, Harvester, Insectrist,
	Miller, Potter, Smith, Stonemason, Weaver
};
static skill_s parent_skills[] = {
	Apiarist, Archivist, Armorer, Baker, Boatcrafter,
	Brewer, Carpenter, Cartographer, Glazier, Harvester,
	Insectrist, Miller, Potter, Smith, Stonemason,
	Weaver
};
static skill_s talent_skills[] = {
	Administrator, Apiarist, Archivist, Armorer, Baker,
	Boatcrafter, Brewer, Carpenter, Cartographer, Cook,
	Deceiver, Fighter, Glazier, Haggler, Harvester,
	Healer, Hunter, Insectrist, Instructor, Laborer,
	Loremouse, Militarist, Miller, Orator, Pathfinder,
	Persuader, Potter, Scientist, Scout, Smith,
	Stonemason, Survivalist, WeatherWatcher, Weaver
};
static skill_s mentor_skills[] = {
	Fighter, Healer, Hunter, Instructor, Pathfinder,
	Scout, Survivalist, WeatherWatcher
};
static skill_s experience_skills[] = {
	Fighter, Healer, Hunter, Instructor, Pathfinder,
	Scout, Survivalist, WeatherWatcher
};
static skill_s speciality_skills[] = {
	Fighter, Healer, Hunter, Instructor, Pathfinder,
	Scout, Survivalist, WeatherWatcher
};
static trait_s start_traits[] = {
	Bigpaw, Bitter, Bodyguard, Bold, Brave,
	Calm, Clever, Compassionate, Cunning, Curious,
	DeepEar, Defender, Determined, Driven, EarlyRiser,
	Extrovert, Fat, Fearful, Fearless, Fiery,
	Generous, Graceful, GuardsHonor, Innocent, Jaded,
	Leader, Longtail, Lost, NaturalBearings, Nimble,
	Nocturnal, Oldfur, QuickWitted, Quiet, Scarred,
	SharpEyed, Sharptooth, Short, Skeptical, Skinny,
	Stoic, Stubborn, Suspicious, Tall, Thoughtful,
	Tough, WeatherSense, Wise, WolfsSnout, Young
};
static trait_s tenderpaws_traits[] = {
	Bigpaw, Brave, Calm, Clever, Compassionate,
	Curious, DeepEar, Defender, Determined, EarlyRiser,
	Extrovert, Fearful, Fearless, Fiery, Generous,
	Graceful, Longtail, Lost, NaturalBearings, Nimble,
	QuickWitted, Quiet, Scarred, Sharptooth, Short,
	Skeptical, Skinny, Stubborn, Suspicious, Tall,
	Tough, WolfsSnout,
};
static trait_s leader_traits[] = {
	Bitter, Bodyguard, Brave, Calm, Clever,
	Compassionate, Cunning, Curious, Defender, Driven,
	EarlyRiser, Fearful, Fearless, Jaded, Leader,
	NaturalBearings, Nocturnal, Oldfur, Quiet,
	Scarred, SharpEyed, Skeptical, Skinny, Stoic,
	Thoughtful, Tough, WeatherSense, Wise
};
struct outcome_info {
	const char*		text;
	skilla			plus;
	skilla			minus;
	traita			traits;
	bool(*allow)(hero* player);
	void(*action)(hero* player);
};
struct question_info {
	const char*		text;
	outcome_info*	result;
};
static outcome_info nature_1[] = {{"��������� �� ����, ���� ���� ��� ��������, ��� ������ ��� �������� ����.", {Nature}},
{"����������� ��, ��� � ��� ����, ����� ����� ��� ����.", {}, {}, {Bold, Generous}},
};
static outcome_info nature_2[] = {{"��������� � ��������."},
{"������ � ���������.", {Nature}, {Fighter}},
};
static outcome_info nature_3[] = {{"��.", {Nature}},
{"���.", {}, {}, {Brave, Fearless}},
};
static question_info nature_questions[] = {{"��...", nature_1},
{"���� ��������� ��������� ���, ��...", nature_2},
{"�� ������� ���, ����� � ������?", nature_3},
{0}
};
static bool is_you_trader(hero* player) {
	for(auto e1 : trade_skills) {
		if(player->get(e1))
			return true;
	}
	return false;
}
static outcome_info resource_1[] = {{"��.", {Resources}},
{"���.", {}, {}, {Leader}},
};
static bool is_parent_traders(hero* player) {
	if(!player->getparent())
		return false;
	for(auto e1 : trade_skills) {
		if(e1 == player->getparent()->specialization)
			return true;
	}
	return false;
}
static outcome_info resource_2[] = {{"��.", {Resources}, {}, {}, is_parent_traders},
{"���."},
};
static outcome_info resource_3[] = {{"��.", {Circles}, {Resources}, {Generous}},
{"���."},
};
static outcome_info resource_4[] = {{"��.", {Resources}, {}, {Generous}},
{"���.", {Circles}},
};
static void make_debt(hero* player) {
}
static outcome_info resource_5[] = {{"��.", {}, {Resources}},
{"���.", {}, {}, {}, 0, make_debt},
};
static outcome_info resource_6[] = {{"��.", {Resources}, {}, {Bold, Fiery}},
{"���."},
};
static void make_criminal(hero* player) {
	player->set(CrimeWise, player->get(CrimeWise) + 1);
}
static outcome_info resource_7[] = {{"��.", {}, {Circles}, {}, 0, make_criminal},
{"���."},
};
static question_info resource_questions[] = {{"����� �� ������ �������� � �����������? �� ������, ���� ��� ������?", resource_1},
{"���� �������� �������, ��������, ����� ��� ������������?", resource_2},
{"��� ��������� �������� ������� ���� � ����� �������?", resource_3},
{"�� ������?", resource_4},
{"�� �����-�� ����� ������ � ����? ��� ������ � ��� ����� � ��������?", resource_5},
{"�� ������ ������������ ���������� � �����������, ����������� ���� ���� �����������?", resource_6},
{"�� �����-�� ���� ������� � ������������� ������������?", resource_7},
{0}
};
static outcome_info circle_1[] = {{"��.", {Circles}},
{"���."},
};
static question_info circle_questions[] = {{"�� ����������� ����? ������ ����� ������?", circle_1},
{0}
};

static char* add_block(char* result, const char* result_max, hero* player, skill_s i1, skill_s i2, const char* name, bool line_feed) {
	result[0] = 0;
	auto p = result;
	for(auto i = i1; i <= i2; i = (skill_s)(i + 1)) {
		auto value = player->get(i);
		if(!value)
			continue;
		if(p == result) {
			if(line_feed)
				zcat(p, "\n");
			zcat(p, name);
			zcat(p, ": ");
		} else
			zcat(p, ", ");
		szprints(zend(p), result_max, "%1 %2i", getstr(i), value);
		p = zend(p);
	}
	if(p != result)
		zcat(p, ".");
	return zend(p);
}

static char* add_block(char* result, const char* result_max, hero* player, trait_s i1, trait_s i2, const char* name, bool line_feed) {
	result[0] = 0;
	auto p = result;
	for(auto i = i1; i <= i2; i = (trait_s)(i + 1)) {
		auto value = player->get(i);
		if(!value)
			continue;
		if(p == result) {
			if(line_feed)
				zcat(p, "\n");
			zcat(p, name);
			zcat(p, ": ");
		} else
			zcat(p, ", ");
		szprints(zend(p), result_max, "%1 %2i", getstr(i), value);
		p = zend(p);
	}
	if(p != result)
		zcat(p, ".");
	return zend(p);
}

static char* add_block(char* result, const char* result_max, hero* player, wise_s i1, wise_s i2, const char* name, bool line_feed) {
	result[0] = 0;
	auto p = result;
	for(auto i = i1; i <= i2; i = (wise_s)(i + 1)) {
		auto value = player->get(i);
		if(!value)
			continue;
		if(p == result) {
			if(line_feed)
				zcat(p, "\n");
			zcat(p, name);
			zcat(p, ": ");
		} else
			zcat(p, ", ");
		szprints(zend(p), result_max, "%1 %2i", getstr(i), value);
		p = zend(p);
	}
	if(p != result)
		zcat(p, ".");
	return zend(p);
}

static char* add_info(char* result, const char* result_max, hero* player) {
	result[0] = 0; auto p = result;
	p = add_block(p, result_max, player, Nature, Circles, "��������", p != result);
	p = add_block(p, result_max, player, Administrator, Weaver, "������", p != result);
	p = add_block(p, result_max, player, Bigpaw, Rational, "�����", p != result);
	p = add_block(p, result_max, player, FirstWise, LastWise, "������", p != result);
	if(p != result)
		zcat(p, "\n");
	return zend(p);
}

static void add_info(hero* player) {
	char temp[2048]; add_info(temp, zendof(temp), player);
	logs::add(temp);
}

static void choose_question(hero* player, bool interactive, question_info* questions) {
	for(auto p = questions; p->text; p++) {
		add_info(player);
		logs::add(p->text);
		for(auto i = 0; i < 2; i++) {
			auto& answer = p->result[i];
			// ��������� ������� ������� ������ �� �����
			if(answer.allow && !answer.allow(player))
				continue;
			logs::add(i, answer.text);
		}
		auto id = logs::input(interactive);
		auto& answer = p->result[id];
		for(auto e : answer.plus)
			player->set(e, player->get(e) + 1);
		for(auto e : answer.minus)
			player->set(e, player->get(e) - 1);
		if(answer.traits.count > 1) {
			add_info(player);
			logs::add("����� �� ��������� ���� ������ ����� ��� ��������?");
			for(auto e : answer.traits) {
				if(player->get(e) >= 3)
					continue;
				logs::add(e, getstr(e));
			}
			auto result = (trait_s)logs::input(interactive);
			player->set(result, player->get(result) + 1);
		} else {
			for(auto e : answer.traits) {
				if(player->get(e) >= 3)
					continue;
				player->set(e, player->get(e) + 1);
			}
		}
		if(answer.action)
			answer.action(player);
	}
}

static skill_s choose(hero* player, bool interactive, skill_s* source, unsigned count) {
	if(interactive) {
		for(unsigned i = 0; i < count; i++) {
			if(player->get(source[i]) >= 5)
				continue;
			logs::add(source[i], getstr(source[i]));
		}
		logs::sort();
		return (skill_s)logs::input(interactive);
	} else {
		logs::clear(true);
		skill_s source_temp[LastSkill + 1];
		auto p = source_temp;
		for(unsigned i = 0; i < count; i++) {
			if(player->get(source[i]) >= 5)
				continue;
			*p++ = source[i];
		}
		count = p - source_temp;
		if(!count)
			return Nature;
		else if(count == 1)
			return source_temp[0];
		auto fighter_chance = 100 - player->get(Fighter) * 30;
		if(fighter_chance >= 0 && d100() < fighter_chance) {
			for(unsigned i = 0; i < count; i++) {
				if(source_temp[i] == Fighter)
					return Fighter;
			}
		}
		return (skill_s)source_temp[rand() % count];
	}
}

static trait_s choose(hero* player, bool interactive, trait_s* source, unsigned count) {
	for(unsigned i = 0; i < count; i++) {
		if(player->get(source[i]) >= 3)
			continue;
		logs::add(source[i], getstr(source[i]));
	}
	logs::sort();
	return (trait_s)logs::input(interactive);
}

static wise_s choose(hero* player, bool interactive) {
	for(auto i = FirstWise; i <= LastWise; i = (wise_s)(i + 1)) {
		if(player->get(i) >= 2)
			continue;
		logs::add(i, getstr(i));
	}
	logs::sort();
	return (wise_s)logs::input(interactive);
}

static void choose_homeland_skills(hero* player, bool interactive) {
	add_info(player);
	logs::add("��� � ����������� ������� [%1] �� ���� ���� ���...", getstf(player->homeland));
	for(auto e : getskills(player->homeland))
		logs::add(e, getstr(e));
	logs::sort();
	auto result = (skill_s)logs::input(interactive);
	player->set(result, player->get(result) + 1);
}

static void choose_homeland_traits(hero* player, bool interactive) {
	add_info(player);
	logs::add("��� � � ����������� ������� [%1] � ��� ����� ������� ��� ��...", getstf(player->homeland));
	for(auto e : gettraits(player->homeland))
		logs::add(e, getstr(e));
	logs::sort();
	auto result = (trait_s)logs::input(interactive);
	player->set(result, player->get(result) + 1);
}

static void choose_homeland(hero* player, bool interactive) {
	add_info(player);
	logs::add("��� �� ��������?");
	for(auto e : homeland_locations)
		logs::add(e, getstr(e));
	logs::sort();
	player->homeland = (location_s)logs::input(interactive);
}

static void choose_skills_talent(hero* player, bool interactive, rang_s rang) {
	int count = rang_data[rang].talented;
	for(int i = 0; i < count; i++) {
		add_info(player);
		logs::add("� ���� � ��� ��� ������ � ������ ��������?");
		if(count > 1)
			logs::add("(�������� %1i)", count - i);
		auto result = choose(player, interactive, talent_skills, sizeof(talent_skills) / sizeof(talent_skills[0]));
		player->set(result, player->get(result) + 1);
	}
}

static void choose_parents(hero* player, bool interactive, rang_s rang) {
	gender_s genders[2] = {Male, Female};
	auto gender = genders[rand() % 2];
	add_info(player);
	if(gender == Male)
		logs::add("��� �� ��������� ��� [����]?");
	else
		logs::add("��� �� ��������� ���� [����]?");
	auto result = choose(player, interactive, parent_skills, sizeof(parent_skills) / sizeof(parent_skills[0]));
	player->set(result, player->get(result) + 1);
	player->family = new hero(player->type, gender, result, player->homeland);
}

static void choose_convice(hero* player, bool interactive, rang_s rang) {
	int count = rang_data[rang].convice;
	for(int i = 0; i < count; i++) {
		add_info(player);
		logs::add("��� �� ��������� ������� ������ ����� ������� ���� ����� ������?");
		if(count > 1)
			logs::add("(�������� %1i)", count - i);
		auto result = choose(player, interactive, communication_skills, sizeof(communication_skills) / sizeof(communication_skills[0]));
		player->set(result, player->get(result) + 1);
	}
}

static void choose_artisan(hero* player, bool interactive, rang_s rang) {
	add_info(player);
	logs::add("����� �� ������ ������ � �������� ������� ��� ���������� � �������� ������� � ������ �� �������������� ������������� %1. �� ���� ������, ������� ������ � ���� � ���� ���������� ��������� �������. ��� ��� ����� [�������������]?", getstf(Lockhaven));
	auto result = choose(player, interactive, artisan_skills, sizeof(artisan_skills) / sizeof(artisan_skills[0]));
	player->set(result, player->get(result) + 1);
}

static void choose_mentor(hero* player, bool interactive, rang_s rang) {
	int count = rang_data[rang].mentors;
	for(int i = 0; i < count; i++) {
		add_info(player);
		logs::add("����� ���� ��� �� ���������� ������������ ��� ������ ��� ����������� ������ ����������. �� ������ ��� ������������ ������ ��������� ���������. � ����������� ������� ������� ��������� ��� �������� ������ � ���������� ���� ��� ����� �������� ���������� ��������� �� ������������� �������. ��� ��������� ��� ������ � ���������� � ��� ��������� ���� ��� ������ ���� � ��������. ��� �� �������� �� ���� ������?");
		if(count > 1)
			logs::add("(�������� %1i)", count - i);
		auto result = choose(player, interactive, mentor_skills, sizeof(mentor_skills) / sizeof(mentor_skills[0]));
		player->set(result, player->get(result) + 1);
	}
}

static void choose_specialization(hero* player, bool interactive, rang_s rang) {
	int count = rang_data[rang].specialization;
	for(int i = 0; i < count; i++) {
		add_info(player);
		logs::add("������ ������� �������� ����� ���� �������������. ������ � ������ ��� ���� ���������� � ���������� ��������������. ������ ���� [�������������]?");
		if(count > 1)
			logs::add("(�������� [%1i])", count - i);
		auto result = choose(player, interactive, speciality_skills, sizeof(speciality_skills) / sizeof(speciality_skills[0]));
		player->set(result, player->get(result) + 1);
		player->specialization = result;
	}
}

static void choose_wises(hero* player, bool interactive, rang_s rang) {
	int count = rang_data[rang].wises;
	for(int i = 0; i < count; i++) {
		add_info(player);
		if(interactive)
			logs::add("������ ���� [������]?");
		if(count > 1) {
			if(interactive)
				logs::add("(�������� [%1i])", count - i);
		}
		auto result = choose(player, interactive);
		player->set(result, player->get(result) + 1);
	}
}

static void choose_traits(hero* player, bool interactive, rang_s rang) {
	add_info(player);
	logs::add("������ ���� ���������� �����?");
	auto result = choose(player, interactive, start_traits, sizeof(start_traits) / sizeof(start_traits[0]));
	player->set(result, player->get(result) + 1);
	int count = rang_data[rang].trait_tender;
	for(int i = 0; i < count; i++) {
		add_info(player);
		logs::add("����� ����� ������� ��� ���� ��������?");
		auto result = choose(player, interactive, tenderpaws_traits, sizeof(tenderpaws_traits) / sizeof(tenderpaws_traits[0]));
		player->set(result, player->get(result) + 1);
	}
	count = rang_data[rang].trait_leader;
	for(int i = 0; i < count; i++) {
		add_info(player);
		logs::add("����� ����� ��� ������� ����� � ������?");
		auto result = choose(player, interactive, leader_traits, sizeof(leader_traits) / sizeof(leader_traits[0]));
		player->set(result, player->get(result) + 1);
	}
}

void hero::set(rang_s value) {
	rang = value;
	for(auto& e : rang_data[value].skills) {
		if(!e.value)
			continue;
		skills[e.key] = e.value;
	}
}

rang_s hero::chooserang(bool interactive) {
	logs::add("������ ����� ����� ���� ����?");
	for(auto i = Tenderpaws; i <= GuardCapitan; i = (rang_s)(i + 1))
		logs::add(i, getstr(i));
	return (rang_s)logs::input(interactive);
}

hero* hero::choose(skill_s skill) {
	for(unsigned i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
		auto p = players[i];
		if(!p)
			continue;
		if(!p->get(skill))
			continue;
		logs::add(i, "%1 (����� %2 %3i)", p->getname(), getstr(skill), p->get(skill));
	}
	if(!logs::getcount())
		return 0;
	return players[logs::input(true, false, "��� ����� ������ ������ ������ [%1]?", getstr(skill))];
}

hero* hero::choose(bool interactive, bool (hero::*proc)() const) {
	for(auto p : players) {
		if(!p)
			continue;
		if(!(p->*proc)())
			continue;
		logs::add((int)p, p->getname());
	}
	if(!logs::getcount())
		return 0;
	return (hero*)logs::input(interactive, false, "��� ����� ��� ������?");
}

hero::hero(rang_s rang, item_s weapon, bool interactive, bool playable) {
	this->type = Mouse;
	this->gender = Male;
	this->set(rang);
	this->age = xrand(rang_data[rang].age[0], rang_data[rang].age[1]);
	// ������
	choose_homeland(this, interactive);
	choose_homeland_skills(this, interactive);
	choose_homeland_traits(this, interactive);
	choose_skills_talent(this, interactive, rang);
	choose_parents(this, interactive, rang);
	choose_convice(this, interactive, rang);
	choose_artisan(this, interactive, rang);
	choose_mentor(this, interactive, rang);
	choose_specialization(this, interactive, rang);
	tallyskills();
	choose_question(this, interactive, nature_questions);
	// ������
	choose_wises(this, interactive, rang);
	tallywises();
	// �����
	choose_traits(this, interactive, rang);
	// ����������
	this->persona = 1;
	this->fate = 1;
	choosename(interactive);
	// ���� ����� ������� ��� ����
	if(playable) {
		for(auto& e : players) {
			if(!e) {
				e = this;
				break;
			}
		}
	}
	this->weapon = weapon;
	if(interactive) {
		add_info(this);
		logs::add("��� �������� �����.");
		logs::next();
	}
}