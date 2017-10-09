#include "adat.h"
#include "command.h"
#include "crt.h"
#include "draw.h"
#include "logs.h"

namespace logs
{
	struct answer
	{
		int						id;
		const char*				text;
	};
	static char					content[256 * 8];
}

static adat<logs::answer, 35>	answers;
static draw::surface			picture;
static char						text_buffer[256 * 32];
static char*					text_ptr = text_buffer;
extern rect						sys_static_area;
extern bool						sys_optimize_mouse_move;
const char*						logs::information;

enum answer_tokens {
	FirstAnswer = InputUser,
	LastAnswer = FirstAnswer + sizeof(answers.data) / sizeof(answers.data[0])
};

static void answer_clear()
{
	text_ptr = text_buffer;
	answers.clear();
}

static char* ending(char* p, const char* string)
{
	char* p1 = (char*)zright(p, 1);
	if(p1[0] != '.' && p1[0] != '?' && p1[0] != '!' && p1[0] != ':' && p1[0] != 0)
		zcat(p1, string);
	return p;
}

void logs::add(int id, const char* format ...)
{
	logs::answer* e = answers.add();
	if(!e)
		return;
	memset(e, 0, sizeof(logs::answer));
	e->id = id;
	szprintv(text_ptr, format, xva_start(format));
	szupper(text_ptr, 1);
	e->text = ending(text_ptr, ".");
	text_ptr = zend(text_ptr) + 1;
}

void logs::addv(const char* format, const char* param)
{
	if(!format)
	{
		memset(content, 0, sizeof(content));
		return;
	}
	char* p = zend(content);
	// First string may not be emphty or white spaced
	if(zskipspcr(format)[0] == 0 && p == content)
		return;
	if(p != content)
	{
		if(p[-1] != ' ' && p[-1] != '\n' && *format != '\n' && *format != '.' && *format != ',')
		{
			*p++ = ' ';
			*p = 0;
		}
		if(p[-1] == '\n' && format[0] == '\n')
			format++;
	}
	szprintv(p, format, param);
}

void logs::add(const char* format, ...)
{
	addv(format, xva_start(format));
}

void logs::open(const char* title, bool resize)
{
	command_app_initialize->execute();
	sys_optimize_mouse_move = true;
	static draw::window window(-1, -1, 800, 620, resize ? WFResize | WFMinmax : 0);
	set_light_theme();
	draw::font = metrics::font;
	draw::fore = colors::text;
	draw::setcaption(title);
	answer_clear();
}

static char* letter(char* result, int n)
{
	if(n < 9)
		return szprint(result, "%1i)", n + 1);
	result[0] = 'A' + (n - 9);
	result[1] = ')';
	result[2] = 0;
	return result;
}

int wdt_tool(int x, int y, int width, const char* name, int id, const char* label, const char* tips)
{
	char result[32];
	int y0 = y;
	int x2 = x + width;
	x += metrics::padding;
	int i = id - FirstAnswer;
	letter(result, i);
	draw::text(x, y, result);
	int w1 = draw::textw(result) + metrics::padding;
	int x1 = x + w1;
	rect rc = {x1, y, x2, y};
	int dy = draw::textf(rc, answers.data[i].text);
	areas a = draw::area(rc);
	if(a == AreaHilited || a == AreaHilitedPressed)
	{
		if(a == AreaHilitedPressed)
		{
			hot::pressed = false;
			draw::execute(i + FirstAnswer);
		}
		draw::rectf({rc.x1 - 2, rc.y1 - 2, rc.x2 + 2, rc.y2 + 2}, colors::edit, 16);
		draw::rectb({rc.x1 - 2, rc.y1 - 2, rc.x2 + 2, rc.y2 + 2}, colors::border.mix(colors::window, 128));
	}
	draw::textf(x1, y, x2 - x1, answers.data[i].text);
	y += dy + metrics::padding;
	return y - y0;
}

int wdt_answers(int x, int y, int width, const char* name, int id, const char* label, const char* tips)
{
	for(unsigned i = 0; i < answers.count; i++)
		y += wdt_tool(x, y, width, "answer", i + FirstAnswer, answers.data[i].text, 0);
	return 0;
}

static int render_input()
{
	char temp[4096];
	while(true)
	{
		int x = 0;
		int y = 0;
		int y2 = draw::getheight();
		int x2 = draw::getwidth();
		draw::rectf({x, y, x2, y2}, colors::window);
		x += metrics::padding;
		y += metrics::padding;
		x2 -= metrics::padding;
		y2 -= metrics::padding;
		if(picture)
		{
			int y1 = metrics::padding;
			int x1 = x2 - picture.width;
			draw::blit(*draw::canvas, x1, metrics::padding, picture.width, picture.height, 0, picture, 0, 0);
			draw::rectb({x1, y1, x2, y1 + picture.height}, colors::border);
			y1 += picture.height + metrics::padding;
			// Left panel
			if(logs::information)
			{
				szprint(temp, logs::information);
				y1 += draw::textf(x1, y1, x2 - x1, temp);
			}
			x2 = x1 - metrics::padding;
		}
		y += draw::textf(x, y, x2 - x, logs::content);
		int id = draw::input();
		if(!id)
			exit(0);
		else if(id >= FirstAnswer && id <= LastAnswer)
			return answers.data[id - FirstAnswer].id;
		else if(hot::key >= (Alpha + '1')
			&& hot::key <= (Alpha + '1' + (int)answers.count - 1))
			draw::execute(FirstAnswer + hot::key - Alpha - '1');
		else if(hot::key >= ((int)Alpha + 'A') && hot::key <= ((int)Alpha + 'Z'))
		{
			if(hot::key <= ((Alpha + 'A') + ((int)answers.count - 10)))
				draw::execute(FirstAnswer + 9 + hot::key - (Alpha + 'A'));
		}
		else if(id < FirstInput)
			return id; // ������� �� ������ ��������� ���������
	}
}

static void correct(char* p)
{
	bool need_uppercase = true;
	for(; *p; p++)
	{
		if(*p == '.' || *p == '?' || *p == '!')
		{
			p = (char*)zskipsp(p + 1);
			if(*p != '-')
				need_uppercase = true;
		}
		if(*p == ' ' || *p == '-' || *p == '\t')
			continue;
		if(need_uppercase)
		{
			szupper(p, 1);
			need_uppercase = false;
		}
	}
}

int logs::inputv(bool interactive, bool clear_text, const char* format, const char* param, const char* element)
{
	char* p = zend(logs::content);
	while(p > content && p[-1] == '\n')
		*--p = 0;
	if(format && format[0])
	{
		if(p != content)
			zcat(p, "\n");
		zcat(p, "[");
		logs::addv(format, param);
		zcat(p, "]");
	}
	correct(logs::content);
	if(element)
		zcat(logs::content, element);
	int r = 0;
	if(interactive)
		r = render_input();
	else if(answers.count)
		r = answers.data[rand() % (answers.count)].id;
	p[0] = 0;
	if(clear_text)
		memset(logs::content, 0, sizeof(logs::content));
	answer_clear();
	return r;
}

int logs::input(bool inveractive, bool clear_text, const char* format, ...)
{
	return inputv(inveractive, clear_text, format, xva_start(format), "\n$(answers)");
}

bool logs::loadart(const char* url)
{
	char temp[260];
	if(zchr(url, '.'))
		zcpy(temp, url);
	else
		szprint(temp, "art/%1.png", url);
	picture.read(temp);
	if(!picture)
		return false;
	picture.convert(-32, 0);
	return true;
}

void logs::next(bool interactive)
{
	logs::add(1, szt("Next", "�����"));
	logs::input(interactive);
}

bool logs::yesno(bool interactive, const char* format, ...)
{
	add(1, szt("Yes", "��"));
	add(2, szt("No", "���"));
	return inputv(interactive, true, format, xva_start(format), "\n$(answers)") == 1;
}

void draw::window::opening()
{
}

void draw::window::closing()
{
}

void draw::window::resizing(const rect& rc)
{
}

static draw::textplugin answers_plugin("answers", wdt_answers);