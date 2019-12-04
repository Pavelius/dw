#include "draw.h"
#include "logs.h"

using namespace draw;

static logs::dialog*	dialog_object;
static int				dialog_param;

int logs::dialog::headof(int& x, int y, int& width, const char* format) const {
	auto dy = header(x, y, width, format);
	x += metrics::padding;
	width -= metrics::padding * 2;
	return dy;
}

int logs::dialog::header(int x, int y, int width, const char* format) const {
	auto pf = font; font = metrics::h3;
	auto pc = fore; fore = colors::white;
	rect rc = {x, y, x + width, y + texth() + metrics::padding * 2};
	gradv(rc, colors::black, colors::black.mix(colors::window, 192));
	text(x + metrics::padding + (width - textw(format)) / 2, y + metrics::padding, format);
	font = pf;
	fore = pc;
	return rc.height();
}

int	logs::dialog::detail(int x, int y, int width, const char* format) const {
	return textf(x, y, width, format);
}

int	logs::dialog::detail(int x, int y, int width, const char* format, int width_right, int value) const {
	char temp[16]; stringbuilder sb(temp); sb.add("%1i", value);
	return detail(x, y, width, format, width_right, temp);
}

int	logs::dialog::detail(int x, int y, int width, const char* format, int width_right, const char* text_value) const {
	auto d1 = textf(x, y, width - width_right - metrics::padding, format);
	auto pc = fore; fore = fore.mix(colors::window, 192);
	text(x + width - width_right + (width_right - textw(text_value)) / 2, y, text_value);
	fore = pc;
	return d1;
}

int logs::dialog::choose() {
	while(ismodal()) {
		rect rc = {0, 0, draw::getwidth(), draw::getheight()};
		draw::rectf(rc, colors::window);
		rc.offset(metrics::padding, metrics::padding);
		render(rc.x1, rc.y1, rc.width());
		domodal();
	}
	return getresult();
}

void logs::dialog::close(int param) {
	breakmodal(param);
}

static void dialog_click() {
	dialog_object->clicking(hot.param, dialog_param);
}

int	logs::dialog::button(int x, int y, int width, const char* title, int id, int param) const {
	rect rc = {x, y, x + width, y + texth() + metrics::padding * 2};
	if(draw::buttonh(rc, false, false, false, true, title)) {
		dialog_param = param;
		dialog_object = const_cast<dialog*>(this);
		draw::execute(dialog_click, id);
	}
	return rc.height();
}