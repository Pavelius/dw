#include "main.h"

namei bsmeta<namei>::elements[] = {{TheAngel, NoGender, "Dou", "Ду"},
{TheAngel, Male, "Bon", "Бон"},
{TheAngel, Female, "Abe", "Эйб"},
{TheAngel, Male, "Boo", ""},
{TheAngel, Male, "T", "Ти"},
{TheAngel, Male, "Kal", "Кейл"},
{TheAngel, Male, "Bai", "Бэй"},
{TheAngel, Male, "Char", "Уголь"},
{TheAngel, Male, "Jav", "Джав"},
{TheAngel, Female, "Ruth", "Руфь"},
{TheAngel, Female, "Wei", "Вэй"},
{TheAngel, Male, "Jay", "Джей"},
{TheAngel, Female, "Nee", "Ни"},
{TheAngel, Male, "Kim", "Ким"},
{TheAngel, Female, "Lan", "Лен"},
{TheAngel, Male, "Di", "Ди"},
{TheAngel, Female, "Dez", "Дез"},
{TheAngel, Male, "Doc", "Док"},
{TheAngel, Male, "Core", "Штифт"},
{TheAngel, Female, "Wheels", "Каталка"},
{TheAngel, Male, "Buzz", "Приход"},
{TheAngel, Male, "Key", "Ключ"},
{TheAngel, Female, "Gabe", "Гейб"},
{TheAngel, Female, "Biz", "Биз"},
{TheAngel, Male, "Bish", "Облом"},
{TheAngel, Female, "Line", "Линейка"},
{TheAngel, Male, "Inch", "Дюйм"},
{TheAngel, Male, "Grip", "Зажим"},
{TheAngel, Male, "Setter", "Наладчик"},
//
{TheBattleBaby, Female, "Snow", "Снежинка"},
{TheBattleBaby, Female, "Crimson", "Алая"},
{TheBattleBaby, Female, "Shadow", "Тень"},
{TheBattleBaby, Female, "Azure", "Лазурь"},
{TheBattleBaby, Female, "Midnight", "Полночь"},
{TheBattleBaby, Female, "Scarlet", "Пурпур"},
{TheBattleBaby, Female, "Violetta", "Виолетта"},
{TheBattleBaby, Female, "Amber", "Янтарь"},
{TheBattleBaby, Female, "Rouge", "Руж"},
{TheBattleBaby, Female, "Damson", "Изюминка"},
{TheBattleBaby, Female, "Sunset", "Закат"},
{TheBattleBaby, Female, "Emerald", "Рубин"},
{TheBattleBaby, Female, "Ruby", "Изумруд"},
{TheBattleBaby, Female, "Raksha", "Ракша"},
{TheBattleBaby, Female, "Kickskirt", "Оторва"},
{TheBattleBaby, Female, "Kite", "Коршун"},
{TheBattleBaby, Female, "Monsoon", "Муссон"},
{TheBattleBaby, Female, "Smith", "Смит"},
{TheBattleBaby, Female, "Beastie", "Зверек"},
{TheBattleBaby, Female, "Baaba", "Малышка"},
{TheBattleBaby, Female, "Melody", "Мелодия"},
{TheBattleBaby, Female, "Mar", "Порча"},
{TheBattleBaby, Female, "Tavi", "Тави"},
{TheBattleBaby, Female, "Absinthe", "Абсент"},
{TheBattleBaby, Female, "Honeytree", "Милашка"},
//
{TheGunlugger, Male, "Vonk the Sculptor", "Вонк 'Скульптор'"},
{TheGunlugger, Female, "Batty", "Бетти"},
{TheGunlugger, Male, "Jonker", "Йонкер"},
{TheGunlugger, Male, "A.T.", "Эй-Ти"},
{TheGunlugger, Male, "Rue Wakeman", "Рю Вокман"},
{TheGunlugger, Female, "Navarre", "Наварра"},
{TheGunlugger, Male, "Man", "Мужик"},
{TheGunlugger, Male, "Kartak", "Картак"},
{TheGunlugger, Male, "Barbarossa", "Барбаросса"},
{TheGunlugger, Female, "Keeler", "Келлер"},
{TheGunlugger, Male, "Grekkor", "Греккор"},
{TheGunlugger, Male, "Crille", "Грилль"},
{TheGunlugger, Male, "Doom", "Дум"},
{TheGunlugger, Male, "Chaplain", "Капеллан"},
{TheGunlugger, Male, "Rex", "Рекс"},
{TheGunlugger, Male, "Fido", "Фидо"},
{TheGunlugger, Male, "Spot", "Спот"},
{TheGunlugger, Male, "Boxer", "Боксер"},
{TheGunlugger, Male, "Doberman", "Доберман"},
{TheGunlugger, Male, "Trey", "Трей"},
{TheGunlugger, Male, "Killer", "Душегуб"},
{TheGunlugger, Male, "Butch", "Мясник"},
{TheGunlugger, Female, "Fifi", "Фифи"},
{TheGunlugger, Female, "Fluffy", "Пушок"},
{TheGunlugger, Male, "Duke", "Дюк"},
{TheGunlugger, Male, "Wolf", "Волк"},
{TheGunlugger, Female, "Rover", "Бита"},
{TheGunlugger, Male, "Max", "Макс"},
{TheGunlugger, Male, "Buddy", "Дружок"},
};
DECLFULL(namei);

static int select(short unsigned* result, gender_s gender, booklet_s type) {
	auto p = result;
	for(auto& e : bsmeta<namei>()) {
		if(e.gender != NoGender && e.gender != gender)
			continue;
		if(e.type != type)
			continue;
		*p++ = &e - bsmeta<namei>::elements;
	}
	return p - result;
}

static short unsigned random_name(booklet_s type, gender_s gender) {
	short unsigned result[128];
	auto count = select(result, gender, type);
	if(!count)
		return 0;
	return result[rand() % count];
}

void hero::choosename(bool interactive, booklet_s booklet, gender_s gender) {
	short unsigned result[128];
	int count = select(result, gender, type);
	for(int i = 0; i < count; i++)
		an.add(result[i], bsmeta<namei>::elements[result[i]].name);
	auto v = an.choose(interactive, true, "Все вокруг называют вас:");
	setname(v);
}

const char* nameablei::getname() const {
	return bsmeta<namei>::elements[data].name;
}

gender_s nameablei::getgender() const {
	return bsmeta<namei>::elements[data].gender;
}