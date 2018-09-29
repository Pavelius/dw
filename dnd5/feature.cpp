#include "main.h"

struct feature_info {
	class_s			type;
	char			level;
	const char*		name;
	featureproc		proc;
	feat_s			feat;
};
static feat_s fighting_style_feats[] = {StyleArchery, StyleDefense, StyleDueling, StyleGreatWeaponFighting, StyleProtection, StyleTwoWeaponFighting};

static void fighting_style(const feature_info& info, creature& player, bool interactive) {
	player.apply(fighting_style_feats, "Выбирайте ваш стиль боя", interactive);
}

static feature_info feature_data[] = {{Fighter, 1, "Боевой стиль", fighting_style},
{Fighter, 1, 0, 0, SecondWind},
};

void creature::apply(class_s type, int level, bool interactive) {
	for(auto& e : feature_data) {
		if(e.type != type || e.level != level)
			continue;
		if(e.feat)
			set(e.feat);
		if(e.proc)
			e.proc(e, *this, interactive);
	}
}