#include "main.h"

static bool match(const char* a, const char* mv) {
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(mv[i] && a[i] < mv[i])
			return false;
	}
	return true;
}

static bool match(const char* a, const char* mv, const char* mm) {
	if(!match(a, mv))
		return false;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(mv[i] && a[i] > mm[i])
			return false;
	}
	return true;
}

void character::chooseability(bool interactive, char* abilities) {
	if(!interactive) {
		for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
			auto v1 = dice::roll(3, 6);
			auto v2 = dice::roll(3, 6);
			abilities[i] = imax(v1, v2);
		}
	} else {
		do {
			for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
				auto v1 = dice::roll(3, 6);
				auto v2 = dice::roll(3, 6);
				abilities[i] = imax(v1, v2);
			}
			logs::add("Прежде чем устремиться в мир AD&D, вы должны создать своего персонажа. Созданный вами персонаж - это ваше alter ego в фантастических мирах этой игры, воображаемая личность, подчиненная вам, с помощью которой вы опосредованно исследуете мир, созданный Мастером.\n");
			logs::add("Каждый персонаж в AD&D обладает шестью способностями : Сила, Ловкость, Телосложение, Интеллект, Мудрость и Обаяние.Три первые способности характеризуют физические возможности персонажа, а три другие - его умственные способности и личные качества.\n");
			logs::add("Ваши способности: ");
			for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
				if(i != Strenght)
					logs::add(", ");
				logs::add("%1 [%2i]", getstr(i), abilities[i]);
			}
			logs::add(".");
			logs::add(1, "Продолжить");
			logs::add(2, "Перебросить");
		} while(logs::input(interactive) == 2);
	}
}

static bool israce(class_s c, race_s r) {
	for(auto e : character::getraces(c)) {
		if(!e)
			break;
		if(e == r)
			return true;
	}
	return false;
}

class_s	character::chooseclass(bool interactive, race_s race, char* abilities) {
	if(!abilities)
		return NoClass;
	for(auto i = Bard; i <= FighterMageTheif; i = (class_s)(i + 1)) {
		if(!israce(i, race))
			continue;
		if(!match(abilities, getminimum(i)))
			continue;
		logs::add(i, getstr(i));
	}
	if(logs::getcount() == 0)
		return NoClass;
	logs::sort();
	return (class_s)logs::input(interactive, false, "После определения расы персонажа вы выбираете его класс. Класс персонажа - это нечто вроде его профессии или рода занятий. Это тот вид деятельности, которым персонаж занимался или которому обучался в юности. Если вы захотите стать врачом, вы не сможете выйти из дома и немедленно начать работать. Сначала вам нужно приобрести соответствующее образование. То же самое можно сказать о классах игровых персонажей в AD&D. Предполагается, что перед тем, как начать свою приключенческую деятельность, персонаж прошел определенное предварительное обучение и подготовку. Теперь, вооруженный некоторыми знаниями и умениями, ваш персонаж готов завоевывать себе доброе имя и удачу.");
}

static char* szrating(char* result, const char* text, int level) {
	zcpy(result, text);
	auto p = zend(result);
	for(int i = 1; i < level; i++)
		*p++ = '+';
	*p = 0;
	return result;
}

race_s character::chooserace(bool interactive, char* abilities) {
	for(auto i = Human; i <= Halfling; i = (race_s)(i + 1)) {
		if(!match(abilities, getminimum(i), getmaximum(i)))
			continue;
		logs::add(i, "[%1]: %2", getstr(i), getinfo(i));
	}
	if(logs::getcount() == 0)
		return Human;
	logs::sort();
	return (race_s)logs::input(interactive, false, "После накидывания показателей способностей своего персонажа вы должны выбрать его расу. Это не то же самое, что раса в общепринятом смысле этого слова: европеидная, монголоидная или негроидная. В данном случае имеется в виду воображаемый биологический тип вашего персонажа - человек, эльф, полуэльф, карлик, гном или хоббит. Каждая раса заметно отличается от других. Каждая раса обладает особыми преимуществами и имеет свой список классов, доступных для выбора.");
}

void character::equip() {
	switch(getclass(type)) {
	case Fighter:
		addweapons(3);
		add(LeatherArmor);
		add(Shield);
		break;
	case Paladin:
	case Ranger:
		addweapons(2);
		add(LeatherArmor);
		add(Shield);
		break;
	case Mage:
		add(Staff);
		break;
	case Cleric:
		add(Mace);
		add(LeatherArmor);
		break;
	default:
		add(Dagger);
		add(LeatherArmor);
		break;
	}
}

character::character(bool interactive) {
	char abilities[Charisma + 1]; chooseability(interactive, abilities);
	auto race = chooserace(interactive, abilities);
	auto type = chooseclass(interactive, race, abilities);
	create(interactive, race, Male, type, abilities, true);
}