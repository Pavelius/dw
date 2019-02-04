#include "collection.h"
#include "crt.h"
#include "draw.h"
#include "logs.h"

using namespace draw;

namespace logs {
struct answer {
	int				id;
	int				priority;
	const char*		text;
	static int		compare(const void* v1, const void* v2);
};
};

static char	text_buffer[256 * 4 * 8];
static stringbuilder textbuilder(text_buffer);
static char	answer_buffer[256 * 4 * 2];
static stringbuilder answerbuilder(answer_buffer);
static adat<logs::answer, 128> answers;
extern rect	sys_static_area;
extern bool	sys_optimize_mouse_move;

enum answer_tokens {
	FirstAnswer = 0xD000,
	LastAnswer = FirstAnswer + sizeof(answers.data) / sizeof(answers.data[0])
};

int logs::answer::compare(const void* v1, const void* v2) {
	return strcmp(((answer*)v1)->text, ((answer*)v2)->text);
}

void logs::clear(bool clear_text) {
	if(clear_text)
		textbuilder.clear();
	answerbuilder.clear();
	answers.clear();
}

void logs::sort() {
	qsort(answers.data, answers.count, sizeof(answers.data[0]), answer::compare);
}

void logs::addv(int id, int priority, const char* format, const char* param) {
	logs::answer* e = answers.add();
	if(!e)
		return;
	memset(e, 0, sizeof(logs::answer));
	e->id = id;
	e->priority = priority;
	e->text = answerbuilder.get();
	answerbuilder.addv(format, param);
	answerbuilder.addsep('.');
	answerbuilder.addsz();
	*((char*)e->text) = stringbuilder::upper(e->text[0]);
}

void logs::open(const char* title, bool resize) {
	sys_optimize_mouse_move = true;
	draw::create(-1, -1, 800, 600, WFResize | WFMinmax, 32);
	draw::font = metrics::font;
	draw::fore = colors::text;
	draw::setcaption(title);
	clear();
}

static char* letter(char* result, const char* result_maximum, int n) {
	if(n < 9)
		return szprints(result, result_maximum, "%1i)", n + 1);
	result[0] = 'A' + (n - 9);
	result[1] = ')';
	result[2] = 0;
	return result;
}

static int render_input() {
	char temp[4096];
	while(ismodal()) {
		rect rc = {0, 0, draw::getwidth(), draw::getheight()};
		draw::rectf(rc, colors::window);
		rc.offset(metrics::padding);
		int left_width = logs::getwidth(0);
		auto panel_information = logs::getpanel(0);
		if(panel_information) {
			if(!left_width)
				left_width = 300;
		}
		if(left_width) {
			int y1 = metrics::padding;
			int x1 = rc.x2 - left_width;
			// Left panel
			if(panel_information) {
				szprints(temp, temp + sizeof(temp) - 1, panel_information);
				y1 += draw::textf(x1, y1, rc.x2 - x1, temp);
			}
			rc.x2 = x1 - metrics::padding;
		}
		rc.y1 += draw::textf(rc.x1, rc.y1, rc.width(), text_buffer);
		domodal();
		if(hot.key >= FirstAnswer && hot.key <= LastAnswer) {
			auto index = unsigned(hot.key - FirstAnswer);
			if(index < answers.count)
				return answers.data[index].id;
		}
	}
	return 0;
}

int	logs::getcount() {
	return answers.count;
}

stringbuilder& logs::getbuilder() {
	return textbuilder;
}

int logs::inputv(bool interactive, bool clear_text, bool return_single, const char* format, const char* param, const char* element) {
	int r = 0;
	if(return_single && answers.count == 1) {
		// Fast return single element
		r = answers.data[rand() % (answers.count)].id;
		clear(clear_text);
		return r;
	}
	auto p = textbuilder.get();
	if(format && format[0] && interactive)
		textbuilder.addx('\n', format, param);
	if(element)
		textbuilder.addx('\n', element, 0);
	if(interactive)
		r = render_input();
	else if(answers.count)
		r = answers.data[rand() % (answers.count)].id;
	textbuilder.set(p);
	clear(clear_text);
	return r;
}

int logs::input(bool inveractive, bool clear_text, const char* format, ...) {
	return inputv(inveractive, clear_text, false, format, xva_start(format), "$(answers)");
}

int logs::inputsg(bool inveractive, bool clear_text, const char* format, ...) {
	return inputv(inveractive, clear_text, true, format, xva_start(format), "$(answers)");
}

void logs::next(bool interactive) {
	logs::add(1, "Далее");
	logs::input(interactive);
}

bool logs::yesno(bool interactive, const char* format, ...) {
	add(1, "Да");
	add(2, "Нет");
	return inputv(interactive, true, false, format, xva_start(format), "\n$(answers)") == 1;
}

void logs::setdark() {
	colors::active = color::create(172, 128, 0);
	colors::border = color::create(73, 73, 80);
	colors::button = color::create(0, 122, 204);
	colors::form = color::create(32, 32, 32);
	colors::window = color::create(64, 64, 64);
	colors::text = color::create(255, 255, 255);
	colors::edit = color::create(38, 79, 120);
	colors::h1 = colors::text.mix(colors::edit, 64);
	colors::h2 = colors::text.mix(colors::edit, 96);
	colors::h3 = colors::text.mix(colors::edit, 128);
	colors::special = color::create(255, 244, 32);
	colors::border = colors::window.mix(colors::text, 128);
	colors::tips::text = color::create(255, 255, 255);
	colors::tips::back = color::create(100, 100, 120);
	colors::tabs::back = color::create(255, 204, 0);
	colors::tabs::text = colors::black;
}

void logs::setlight() {
	colors::active = color::create(0, 128, 172);
	colors::button = color::create(223, 223, 223);
	colors::form = color::create(240, 240, 240);
	colors::window = color::create(255, 255, 255);
	colors::text = color::create(0, 0, 0);
	colors::edit = color::create(173, 214, 255);
	colors::h1 = colors::text.mix(colors::edit, 64);
	colors::h2 = colors::text.mix(colors::edit, 96);
	colors::h3 = colors::text.mix(colors::edit, 128);
	colors::special = color::create(0, 0, 255);
	colors::border = color::create(172, 172, 172);
	colors::tips::text = color::create(255, 255, 255);
	colors::tips::back = color::create(80, 80, 120);
	colors::tabs::back = color::create(0, 122, 204);
	colors::tabs::text = color::create(255, 255, 255);
}

static void set_hot_key() {
	hot.key = hot.param;
}

int wdt_answer(int x, int y, int width, const char* name, int id, const char* label, const char* tips) {
	char result[32];
	int y0 = y;
	int x2 = x + width;
	y += metrics::padding / 2;
	x += metrics::padding;
	int i = id - FirstAnswer;
	letter(result, result + sizeof(result) / sizeof(result[0]) - 1, i);
	draw::text(x, y, result);
	int x1 = x + draw::textw("AZ)");
	rect rc = {x1, y, x2, y};
	int dy = draw::textf(rc, answers.data[i].text);
	areas a = draw::area(rc);
	auto run = false;
	if(a == AreaHilited || a == AreaHilitedPressed) {
		draw::rectf({rc.x1 - 2, rc.y1 - 2, rc.x2 + 2, rc.y2 + 2}, colors::edit, 16);
		draw::rectb({rc.x1 - 2, rc.y1 - 2, rc.x2 + 2, rc.y2 + 2}, colors::border.mix(colors::window, 128));
	}
	if((hot.key==MouseLeft && a == AreaHilitedPressed)
		|| (i<10 && hot.key==(Alpha + '1' + i))
		|| (i>=9 && hot.key == (Alpha + 'A' + (i - 9)))) {
		hot.pressed = false;
		draw::execute(set_hot_key, i + FirstAnswer);
	}
	draw::textf(x1, y, x2 - x1, answers.data[i].text);
	y += dy;
	y += metrics::padding / 2;
	return y - y0;
}

int wdt_answers(int x, int y, int width, const char* name, int id, const char* label, const char* tips) {
	auto column_count = 1 + answers.count / 13;
	auto medium_width = width / column_count;
	if(column_count > 1 && medium_width > 200) {
		unsigned text_width = 0;
		auto glyph_width = draw::textw("a") + draw::textw("AZ)");
		for(auto& e : answers) {
			unsigned w = zlen(e.text)*glyph_width;
			if(w > text_width)
				text_width = w;
		}
		text_width += text_width / 10;
		if(text_width < medium_width)
			medium_width = text_width;
	}
	auto column_width = medium_width - metrics::padding;
	auto rows_count = answers.count / column_count;
	auto index = 0;
	auto y0 = y;
	for(unsigned column = 0; column < column_count; column++) {
		y = y0;
		for(unsigned row = 0; row < rows_count; row++) {
			y += wdt_answer(x, y, column_width, "answer", index + FirstAnswer, answers.data[index].text, 0);
			index++;
		}
		if(column != column_count - 1)
			x += medium_width;
	}
	while(index < (int)answers.count) {
		y += wdt_answer(x, y, column_width, "answer", index + FirstAnswer, answers.data[index].text, 0);
		index++;
	}
	return 0;
}
static draw::textplugin answers_plugin("answers", wdt_answers);