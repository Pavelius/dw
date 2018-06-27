#include "main.h"

hero players[max_players];

static int rolln(int bonus, int f, int ps, int s) {
	auto result = thing::roll(bonus);
	switch(result) {
	case PartialSuccess: return ps;
	case Fail: return f;
	default: return s;
	}
}

int	hero::getharm() const {
	auto r = weapon.getharm();
	if(is(Bloodcrazed) || is(Merciless))
		r++;
	return r;
}

int hero::getindex() const {
	return this - players;
}

bool hero::is(move_s value) const {
	return (moves & (1 << value)) != 0;
}

void hero::set(move_s value) {
	moves |= 1 << value;
	switch(value) {
	case InsanoLikeDrano: stats[Hard] = imin(stats[Hard] + 1, 3); break;
	case PreparedForTheInevitable: angelkit = 2; break;
	default: break;
	}
}

bool hero::add(item value) {
	if(value.isweapon() && !weapon) {
		weapon = value;
		return true;
	}
	return false;
}

result_s hero::actunderfire() {
	int bonus = get(Cool);
	if(is(BattleHardened))
		bonus = imax(bonus, get(Hard));
	return roll(bonus);
}

result_s hero::goaggro(actor& enemy) {
	int bonus = get(Hard);
	if(is(IceCold))
		bonus = imax(bonus, get(Cool));
	auto result = roll(bonus);
	if(result >= Success) {
		if(!weapon)
			act(enemy, "%герой резко ударил%а %оппонента головой в нос. От боли %ОНА вcкрикнул%А и отош%ЛА назад. Затем последовал резкий удар в живот, коленом в пах и сверху кулаком по спине. От такой подачи %оппонент упала%А на землю. %герой же начал%а нещадно бить %ЕЕ ногами.");
		else
			act(enemy, "%герой выстрелил%а в %оппонента.");
		inflictharm(enemy, getharm());
		act("\n- И не смейте меня больше злить суки! - заорал%а %герой. - Имейте ввиду, это будет с каждым!");
	} else if(result == PartialSuccess) {
		enemy.act("- Валим! - крикнула%а %герой. В момент %она и те кто с %ней скрылись из виду.");
	} else {
		enemy.act("- Ну ты и мудила! - крикнула%а %герой.\n");
		combat(enemy);
	}
	return result;
}

result_s hero::readasitch() {
	int bonus = get(Sharp);
	return roll(bonus);
}

result_s hero::readaperson() {
	int bonus = get(Sharp);
	return roll(bonus);
}

result_s hero::openyourbrain() {
	int bonus = get(Weird);
	return roll(bonus);
}

int hero::whatdo() const {
	return logs::input(true, true, "Что будет делать [%1]?", getname());
}

item* hero::getweapon(distance_s distance) {
	for(auto& e : weapons) {
		if(!e)
			continue;
		if(e.is(distance))
			return &e;
	}
	return 0;
}

void hero::prepareweapon(distance_s distance) {
	if(weapon.is(distance))
		return;
	auto p = getweapon(distance);
	if(p) {
		char temp[260]; iswap(weapon, *p);
		act("%герой достал%а %1.", weapon.getname(temp, false));
	}
}

void hero::choose(aref<const char*> strings, const char* title, char* result, int answer_count) {
	result[0] = 0;
	for(auto i = 0; i < answer_count; i++) {
		for(unsigned j = 1; j <= strings.count; j++) {
			if(zchr(result, (char)j))
				continue;
			logs::add(j, strings.data[j - 1]);
		}
		zcat(result, (char)logs::input(true, false, ((answer_count - i) > 1) ? "%1 (выберите [%2i])" : title, title, answer_count - i));
	}
}

bool hero::seizbyforce(actor& enemy, const char* goal) {
	auto bonus = get(Hard);
	act(enemy, "%герой начал%а стрельбу, %оппонент палил%А в ответ. И на несколько мгновений воцарился ад.");
	auto ca = rolln(bonus, 1, 2, 3);
	auto ph = getharm();
	auto eh = enemy.getharm();
	auto control = false;
	char answers[4];
	static const char* answers_text[] = {
		"Нанести ужасный урон (+1 урон врагу).",
		"Вы получили не много урона (-1 урон вам).",
		goal,
		"Вы удивляете, пугаете или обращаете в бегство врага."
	};
	choose(answers_text, "Что вы предпочтете?", answers, ca + addchoice());
	for(auto e : answers) {
		switch(e) {
		case 1: ph++; break;
		case 2: eh--; break;
		case 3: enemy.set(Frighten); break;
		case 4: control = true; break;
		}
	}
	inflictharm(enemy, ph);
	sufferharm(eh);
	return control;
}

bool hero::keephold(actor& enemy) {
	return seizbyforce(enemy, "Вы сумели отстоять свою позицию и вам не пришлось отступать.");
}

bool hero::laydownfire(actor& enemy) {
	auto bonus = get(Hard);
	act("%герой начал%а стрельбу в сторону врагов, пытаясь отвлечь их внимание и помешать их планам.");
	auto ca = rolln(bonus, 1, 2, 3);
	//auto ph = getharm();
	//auto eh = enemy.getharm();
	char answers[4];
	static const char* answers_text[] = {
		"Вы обеспечили огонь прикрытия, чтобы другой персонаж смог выполнить действие свободно и без ограничений.",
		"Вы обеспечили подеррживающий огонь, чтобы другой персонаж получил +1 выбор в своем боевом ходе.",
		"Вы обеспечили подавляющий огонь, запрещая врагу передвигаться или что-то делать.",
		"Враг в вашем поле зрения получает случайный урон от вас (-1 к урону)."
	};
	choose(answers_text, "Каков результат ваших действий?", answers, ca + addchoice());
	bool cover = false;
	for(auto e : answers) {
		switch(e) {
		case 1: cover = true; break;
		case 2: break;
		case 3: enemy.set(ActingUnderFire); break;
		case 4: inflictharm(enemy, getharm() - 1); break;
		}
	}
	return cover;
}

bool hero::combat(actor& enemy) {
	if(!isalive())
		return false;
	if(!enemy.isalive())
		return true;
	while(true) {
		auto bonus = get(Hard);
		auto result = roll(bonus);
		act(enemy, "%герой начал%а стрельбу, %оппонент палил%А в ответ. И на несколько мгновений воцарился ад.");
		auto ph = getharm();
		auto eh = enemy.getharm();
		switch(result) {
		case Success:
			ph++; eh--;
			break;
		case PartialSuccess:
			logs::add(1, "Нанести ужасный урон (+1 урон врагу).");
			logs::add(2, "Вы получили не много урона (-1 урон вам).");
			if(logs::input(true, false, "Что предпочтете?") == 1)
				ph++;
			else
				eh--;
			break;
		case Fail:
			if(d100() < 50)
				ph--;
			else
				eh++;
			break;
		}
		inflictharm(enemy, ph);
		sufferharm(eh);
		if(isalive() && enemy.isalive())
			logs::add(1, "Продолжить поединок");
		if(!enemy.isalive())
			logs::add(2, "Закончить поединок победой");
		else if(!isalive() || enemy.iswounded())
			logs::add(3, "Закончить поединок");
		switch(logs::input(true, true, "Что делать дальше?")) {
		case 2: return true;
		case 3: return false;
		}
	}
}

void hero::sufferharm(int bonus) {
	bonus -= getarmor();
	if(bonus > 0) {
		health -= bonus;
		if(!isalive())
			act("%герой получил%а [%1i] урона и упал%а.", bonus);
		else if(iswounded())
			act("%герой получил%а [%1i] урона и закричал%а от боли.", bonus);
		else
			act("%герой получил%а [%1i] урона.", bonus);
	} else {
		if(getarmor())
			act("Броня спасла %героя от вреда.", bonus);
	}
	switch(roll(bonus, 0, false)) {
	case Success:
		if(health > 0) {
			health -= 1;
			act("Все было не так плохо, пока %герой не обнаружил%а кровь текущую из рукава что стоило еще 1 урона.");
		}
		break;
	case PartialSuccess:
		break;
    default:
        break;
	}
}

void hero::inflictharm(actor& enemy, int count) {
	enemy.sufferharm(count + (getsize() - enemy.getsize()));
}

int	hero::gethistory(const hero& player) const {
	return history[player.getindex()];
}