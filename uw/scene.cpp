#include "main.h"

scene*	current_scene;

static const char* scene_enter_text[] = {
	"�� ����� � ������� �����.",
	"�� ����������� ��� ������ � ������ � ���.",
	"������ ��� �� ������ ���������� �������� ����.",
};
static const char* position_text[4] = {
	"����� ����� ����",
	"����� �� ���",
	"� ����",
};

scene::scene(scene_s type, hero& player) : type(type), player(player) {
	current_scene = this;
	enemy.clear();
	memset(features, 0, sizeof(features));
}

scene::~scene() {
	current_scene = previous_scene;
}

void scene::enter() {
	logs::add(scene_enter_text[type]);
}