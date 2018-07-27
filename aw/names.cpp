#include "main.h"

static struct nameinfo {
	booklet_s		type;
	gender_s		gender;
	const char*		id;
	const char*		name;
} objects[] = {
	{TheAngel, NoGender, "Dou", "Ду"},
	{TheAngel, Male, "Bon", "Бон"},
	{TheAngel, Female, "Abe", "Эйб"},
	{TheAngel, Male, "Boo", ""},
	{TheAngel, NoGender, "T", "Ти"},
	{TheAngel, Male, "Kal", "Кейл"},
	{TheAngel, Male, "Bai", "Бэй"},
	{TheAngel, NoGender, "Char", "Уголь"},
	{TheAngel, Male, "Jav", "Джав"},
	{TheAngel, Female, "Ruth", "Руфь"},
	{TheAngel, Female, "Wei", "Вэй"},
	{TheAngel, Male, "Jay", "Джей"},
	{TheAngel, NoGender, "Nee", "Ни"},
	{TheAngel, Male, "Kim", "Ким"},
	{TheAngel, Female, "Lan", "Лен"},
	{TheAngel, Male, "Di", "Ди"},
	{TheAngel, Female, "Dez", "Дез"},
	{TheAngel, NoGender, "Doc", "Док"},
	{TheAngel, Male, "Core", "Штифт"},
	{TheAngel, Female, "Wheels", "Каталка"},
	{TheAngel, Male, "Buzz", "Приход"},
	{TheAngel, Male, "Key", "Ключ"},
	{TheAngel, Female, "Gabe", "Гейб"},
	{TheAngel, Female, "Biz", "Биз"},
	{TheAngel, NoGender, "Bish", "Облом"},
	{TheAngel, Female, "Line", "Линейка"},
	{TheAngel, Male, "Inch", "Дюйм"},
	{TheAngel, Male, "Grip", "Зажим"},
	{TheAngel, Male, "Setter", "Наладчик"},
	//
	{TheBattleBaby, Female, "Snow", "Снежинка"},
	{TheBattleBaby, Female, "Crimson", "Алая"},
	{TheBattleBaby, Female, "Shadow", "Тень"},
	{TheBattleBaby, Female, "Azure", "Лазурь"},
	{TheBattleBaby, NoGender, "Midnight", "Полночь"},
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
	{TheBattleBaby, NoGender, "Kite", "Коршун"},
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
	{TheGunlugger, NoGender, "Navarre", "Наварра"},
	{TheGunlugger, Male, "Man", "Мужик"},
	{TheGunlugger, Male, "Kartak", "Картак"},
	{TheGunlugger, Male, "Barbarossa", "Барбаросса"},
	{TheGunlugger, NoGender, "Keeler", "Келлер"},
	{TheGunlugger, Male, "Grekkor", "Греккор"},
	{TheGunlugger, Male, "Crille", "Грилль"},
	{TheGunlugger, Male, "Doom", "Дум"},
	{TheGunlugger, Male, "Chaplain", "Капеллан"},
	{TheGunlugger, Male, "Rex", "Рекс"},
	{TheGunlugger, NoGender, "Fido", "Фидо"},
	{TheGunlugger, NoGender, "Spot", "Спот"},
	{TheGunlugger, Male, "Boxer", "Боксер"},
	{TheGunlugger, NoGender, "Doberman", "Доберман"},
	{TheGunlugger, Male, "Trey", "Трей"},
	{TheGunlugger, Male, "Killer", "Душегуб"},
	{TheGunlugger, Male, "Butch", "Мясник"},
	{TheGunlugger, Female, "Fifi", "Фифи"},
	{TheGunlugger, Female, "Fluffy", "Пушок"},
	{TheGunlugger, Male, "Duke", "Дюк"},
	{TheGunlugger, Male, "Wolf", "Волк"},
	{TheGunlugger, NoGender, "Rover", "Бита"},
	{TheGunlugger, Male, "Max", "Макс"},
	{TheGunlugger, Male, "Buddy", "Дружок"},
};

static int select(short unsigned* result, gender_s gender, booklet_s type) {
	auto p = result;
	for(auto& e : objects) {
		if(e.gender != NoGender && e.gender != gender)
			continue;
		if(e.type != type)
			continue;
		*p++ = &e - objects;
	}
	return p - result;
}

const char*	thing::getname(gender_s gender, booklet_s type) {
	short unsigned result[128];
	auto count = select(result, gender, type);
	if(!count)
		return 0;
	return objects[rand() % count].name;
}

void hero::choosename(bool interactive) {
	short unsigned result[128];
	int count = select(result, getgender(), type);
	for(int i = 0; i < count; i++)
		logs::add(result[i], objects[result[i]].name);
	setname(objects[logs::input(interactive, true, "Все вокруг называют вас:")].name);
}