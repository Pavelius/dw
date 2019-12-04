#include "crt.h"
#include "draw.h"
#include "logs.h"

using namespace draw;

extern rect		sys_static_area;
extern bool		sys_optimize_mouse_move;
static bool		break_modal;
static int		break_result;
eventproc		draw::domodal;

static void clear_resources(bool clear_text) {
	logs::an.clear();
	if(clear_text)
		logs::sb.clear();
}

void draw::execute(eventproc proc, int param) {
	domodal = proc;
	hot.key = 0;
	hot.param = param;
}

void draw::breakmodal(int result) {
	break_modal = true;
	break_result = result;
}

void draw::buttoncancel() {
	breakmodal(0);
}

void draw::buttonok() {
	breakmodal(1);
}

int draw::getresult() {
	return break_result;
}

static void standart_domodal() {
	hot.key = draw::rawinput();
	switch(hot.key) {
	case 0:
		exit(0);
		break;
	}
}

bool draw::ismodal() {
	hot.cursor = CursorArrow;
	if(hot.mouse.x < 0 || hot.mouse.y < 0)
		sys_static_area.clear();
	else
		sys_static_area = {0, 0, draw::getwidth(), draw::getheight()};
	domodal = standart_domodal;
	if(!break_modal)
		return true;
	break_modal = false;
	return false;
}

void draw::initialize() {
	draw::font = metrics::font;
	draw::fore = colors::text;
	draw::fore_stroke = colors::blue;
}

void logs::open(const char* title, bool resize) {
	sys_optimize_mouse_move = true;
	draw::create(-1, -1, 800, 600, WFResize | WFMinmax, 32);
	draw::font = metrics::font;
	draw::fore = colors::text;
	draw::setcaption(title);
}

static char* letter(stringbuilder& sb, int n) {
	if(n < 9)
		sb.add("%1i)", n + 1);
	else {
		char result[3];
		result[0] = 'A' + (n - 9);
		result[1] = ')';
		result[2] = 0;
		sb.add(result);
	}
	return sb;
}

static void breakparam() {
	breakmodal(hot.param);
}

int answeri::paint(int x, int y, int width, int i, int& maximum_width) const {
	auto padding = metrics::padding * 3;
	width -= padding;
	char result[32]; stringbuilder sb(result);
	int y0 = y;
	int x2 = x + width;
	y += metrics::padding / 2;
	x += metrics::padding;
	letter(sb, i);
	draw::text(x, y, result);
	auto mw0 = draw::textw("AZ)");
	auto x1 = x + mw0;
	rect rc = {x1, y, x2, y};
	auto dy = draw::textf(rc, elements[i].text);
	auto a = draw::area(rc);
	auto run = false;
	if(a == AreaHilited || a == AreaHilitedPressed) {
		draw::rectf({rc.x1 - 2, rc.y1 - 2, rc.x2 + 2, rc.y2 + 2}, colors::edit, 16);
		draw::rectb({rc.x1 - 2, rc.y1 - 2, rc.x2 + 2, rc.y2 + 2}, colors::border.mix(colors::window, 128));
		if(hot.key == MouseLeft && hot.pressed)
			run = true;
	}
	if((i<10 && hot.key == (Alpha + '1' + i))
		|| (i >= 9 && hot.key == (Alpha + 'A' + (i - 9))))
		run = true;
	auto mw1 = 0;
	draw::textf(x1, y, x2 - x1, elements[i].text, &mw1);
	mw1 += mw0 + padding;
	if(maximum_width < mw1)
		maximum_width = mw1;
	y += dy;
	if(run) {
		hot.pressed = false;
		execute(breakparam, elements[i].param);
	}
	return y - y0;
}

int answeri::paint(int x, int y, int width) const {
	unsigned column_count = 1 + elements.getcount() / 13;
	unsigned medium_width = width / column_count;
	unsigned rows_count = elements.count / column_count;
	auto index = 0;
	auto y0 = y;
	auto mw = 0;
	for(unsigned column = 0; column < column_count; column++) {
		y = y0;
		mw = 0;
		for(unsigned row = 0; row < rows_count; row++) {
			y += paint(x, y, medium_width, index, mw);
			index++;
		}
		if(column != column_count - 1)
			x += mw;
	}
	while(index < (int)elements.getcount()) {
		y += paint(x, y, medium_width, index, mw);
		index++;
	}
	return 0;
}

int answeri::choosev(bool interactive, bool clear_text, bool return_single, const char* format) const {
	if(!elements)
		return 0;
	if(!interactive || (return_single && elements.count == 1)) {
		// Fast return single element
		auto r = elements.data[0].param;
		clear_resources(clear_text);
		return r;
	}
	logs::sb.normalize();
	while(ismodal()) {
		rect rc = {0, 0, draw::getwidth(), draw::getheight()};
		draw::rectf(rc, colors::window);
		rc.offset(metrics::padding);
		auto rp = logs::panel::getcurrent();
		if(rp) {
			char temp[512]; temp[0] = 0;
			stringbuilder sb(temp);
			rp->print(sb);
			const auto right_width = 300;
			rc.x2 -= right_width + metrics::padding;
			auto y1 = rc.y1;
			y1 += draw::textf(rc.x2, y1, right_width, sb);
			rc.x2 -= metrics::padding * 2;
		}
		rc.y1 += draw::textf(rc.x1, rc.y1, rc.width(), logs::sb);
		if(format)
			rc.y1 += draw::textf(rc.x1, rc.y1, rc.width(), format);
		rc.y1 += paint(rc.x1, rc.y1, rc.width());
		domodal();
	}
	clear_resources(clear_text);
	return getresult();
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