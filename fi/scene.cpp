#include "main.h"

static const char* range_text[] = {"на вас",
"прямо перед вами", "в паре метрах от вас", "недалеко от вас", "впереди", "далеко впереди"};

struct scene_info {
	const char*		nameof;
};
static scene_info scene_data[] = {{"большую комнату"},
{"огромый склад"},
{"старую церковь"},
};
struct feature_info {
	gender_s		gender;
	const char*		name;
	const char*		look;
};
static feature_info feature_data[] = {{Male, "деревянный стол"},
{Female, "каменная статуя", "Множество деталей на ней было отколо и судя по виду она была очень старая."},
{Female, "дренажная решетка", "За решеткой находился сток. Оттуда шел ужасный смрад."},
{Male, "алтарь из черного камня", "Алтарь местами был покрыт кровью. Вероятно на нем когда-то приносили в жертву живых существ."},
{Female, "куча мусора", "Куча была наполнена гниющими отходами еды и эксриментами. Внутри что-то шевелилось. Стоял ужасный смрад."},
};

enum feature_flag_s : unsigned {
	Hidden = 1,
};

int	scene::getplayercount() const {
	auto result = 0;
	for(auto p : players) {
		if(p)
			result++;
	}
	return result;
}

void feature::clear() {
	memset(this, 0, sizeof(*this));
}

void feature::create() {
	clear();
	type = feature_data + rand() % (sizeof(feature_data) / sizeof(feature_data[0]));
	position = xrand(0, 2);
}

const char* feature::getlook() const {
	return type->look;
}

const char* feature::getname() const {
	return type->name;
}

void scene::clear() {
	memset(this, 0, sizeof(*this));
}

void scene::create() {
	clear();
	type = scene_data + rand() % (sizeof(scene_data) / sizeof(scene_data[0]));
	auto maximum = xrand(2, sizeof(features) / sizeof(features[0]) - 3);
	for(auto i = 0; i < maximum; i++)
		features[i].create();
}

void scene::look(stringbuilder& sb) {
	auto current = features + 0;
	sb.adds("Вы видите %1.", type->nameof);
	sb.adds("%+1 находится %2.", range_text[ArmsHand], current->getname());
	sb.adds(current->getlook());
	for(auto& e : features) {
		if(!e)
			continue;
		if(&e == current)
			continue;
		auto d = Near + iabs(current->getposition() - e.getposition());
		sb.adds("%+1 находится %2.", range_text[d], e.getname());
	}
}