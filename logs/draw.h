#include "color.h"
#include "point.h"

#pragma once

typedef void(*eventproc)();
typedef const char* (*fntext)(const void* object, char* result, const char* result_maximum, const void* type);
extern "C" int strcmp(const char* s1, const char* s2); // Compare two strings

enum draw_event_s {
	// input events
	InputSymbol = 0xED00, InputTimer, InputIdle, InputUpdate, InputNoUpdate, InputExecute,
	// Keyboard and mouse input (can be overrided by flags)
	MouseLeft = 0xEE00, MouseLeftDBL, MouseRight,
	MouseMove, MouseWheelUp, MouseWheelDown,
	KeyLeft, KeyRight, KeyUp, KeyDown, KeyPageUp, KeyPageDown, KeyHome, KeyEnd,
	KeyBackspace, KeyEnter, KeyDelete, KeyEscape, KeySpace, KeyTab,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	// named keys range
	Alpha,
	FirstKey = MouseLeft,
	FirstMouse = MouseLeft, LastMouse = MouseWheelDown,
	// support
	CommandMask = 0x0000FFFF,
	// misc events can be combination with previous
	Ctrl = 0x00010000,
	Alt = 0x00020000,
	Shift = 0x00040000,
	// columns flags
	SmallHilite = 0x00010000,
	HideZero = 0x00020000,
	// state flags
	Focused = 0x10000000, // Control has keyboard input and can change visual form.
	Checked = 0x20000000, // Use in background virtual method.
	Disabled = 0x40000000, // Control not grant any input.
	FirstInput = InputSymbol,
};
enum window_flags {
	WFResize = 0x0010,
	WFMinmax = 0x0020,
	WFMaximized = 0x0040,
	WFAbsolutePos = 0x0080,
};
enum cursors {
	CursorArrow, CursorHand, CursorLeftRight, CursorUpDown, CursorAll, CursorNo, CursorEdit, CursorWait,
};
enum areas {
	AreaNormal, // Area not have mouse
	AreaHilited, // Area have mouse
	AreaHilitedPressed, // Area have mouse and mouse button is pressed
};
enum image_flag_s {
	ImageMirrorV = 0x0001,
	ImageMirrorH = 0x0002,
	ImageGrayscale = 0x0004,
	ImageNoOffset = 0x0008,
	ImageTransparent = 0x0010,
	ImageColor = 0x0020,
	ImagePallette = 0x0040,
	TextStroke = 0x0080,
	TextItalic = 0x0100,
	TextBold = 0x0200,
	TextUscope = 0x0400,
	TextSingleLine = 0x0800, // Text would be showed as single line
	AlignLeft = 0x0000,
	AlignCenter = 0x1000,
	AlignRight = 0x2000,
	AlignLeftCenter = 0x3000,
	AlignCenterCenter = 0x4000,
	AlignRightCenter = 0x5000,
	AlignLeftBottom = 0x6000,
	AlignCenterBottom = 0x7000,
	AlignRightBottom = 0x8000,
	AlignWidth = 0xE000,
	AlignMask = 0xF000,
};
struct pma {
	char				name[4]; // Identifier of current block
	int					size; // Size of all block
	int					count; // Count of records in this block
	int					find(const char* name) const;
	const pma*			getheader(const char* name) const;
	const char*			getstring(int id) const;
};
struct sprite : pma {
	enum flagse { NoIndex = 1 };
	enum encodes { Auto, RAW, RLE, ALC, RAW8, RLE8 };
	struct frame {
		short 			sx, sy;
		short			ox, oy;
		encodes			encode;
		unsigned		pallette;
		unsigned		offset;
		rect			getrect(int x, int y, unsigned flags) const;
	};
	struct cicle {
		short unsigned	start;
		short unsigned	count;
	};
	short int			width, height; // common size of all frames (if applicable)
	short int			ascend, descend; // top or down ascend
	short unsigned		flags; // must be zero
	unsigned			cicles; // count of anim structure
	unsigned			cicles_offset;
	frame				frames[1];
	int					esize() const { return frames[0].offset - (sizeof(sprite) + sizeof(frame)*(count - 1)); }
	const unsigned char* edata() const { return (const unsigned char*)this + sizeof(sprite) + sizeof(frame)*(count - 1); }
	int					ganim(int index, int tick);
	const frame&		get(int id) const { return frames[(id >= count) ? 0 : id]; }
	cicle*				gcicle(int index) { return (cicle*)ptr(cicles_offset) + index; }
	inline int			gindex(int index) const { return *((short unsigned*)((cicle*)ptr(cicles_offset) + cicles) + index); }
	int					glyph(unsigned sym) const;
	const unsigned char* ptr(unsigned o) const { return (unsigned char*)this + o; }
};
namespace colors {
extern color			active;
extern color			button;
extern color			form;
extern color			focus;
extern color			window;
extern color			border;
extern color			text, edit, h1, h2, h3, special;
namespace tips {
extern color			back;
extern color			text;
}
namespace tabs {
extern color			back;
extern color			text;
}
}
namespace metrics {
extern rect				edit;
extern sprite*			font;
extern sprite*			h1;
extern sprite*			h2;
extern sprite*			h3;
extern int				padding;
extern int				scroll;
}
namespace draw {
namespace dialog {
bool					color(struct color& result, struct color* custom = 0);
bool					folder(const char* title, char* path);
bool					open(const char* title, char* path, const char* filter, int filter_index = 0, const char* ext = 0);
bool					save(const char* title, char* path, const char* filter, int filter_index = 0);
}
struct hoti {
	cursors				cursor; // set this mouse cursor
	unsigned			key; // if pressed key or mouse this field has key
	point				mouse; // current mouse coordinates
	bool				pressed; // flag if any of mouse keys is pressed
	int					param; // command context or parameters
	//anyval			value;
	explicit operator bool() const { return key != 0; }
	void				zero() { key = InputUpdate; }
};
extern hoti				hot;
struct surface {
	struct plugin {
		const char*		name;
		const char*		filter;
		plugin*			next;
		static plugin*	first;
		//
		plugin(const char* name, const char* filter);
		//
		virtual bool	decode(unsigned char* output, int output_bpp, const unsigned char* input, unsigned input_size) = 0;
		virtual bool	inspect(int& w, int& h, int& bpp, const unsigned char* input, unsigned size) = 0;
	};
	int					width;
	int					height;
	int					scanline;
	int					bpp;
	unsigned char*		bits;
	surface();
	surface(int width, int height, int bpp);
	surface(const char* url, color* pallette = 0);
	~surface();
	operator bool() const { return bits != 0; }
	static unsigned char* allocator(unsigned char* bits, unsigned size);
	void				clear() { resize(0, 0, 0, true); }
	void				convert(int bpp, color* pallette);
	void				flipv();
	unsigned char*		ptr(int x, int y);
	bool				read(const char* url, color* pallette = 0, int need_bpp = 0);
	void				resize(int width, int height, int bpp, bool alloc_memory);
	void				write(const char* url, color* pallette);
};
// Push state in stack
struct state {
	state();
	~state();
private:
	color				fore, fore_stroke;
	float				linw;
	const sprite*		font; // glyph font
	surface*			canvas;
	rect				clip;
};
struct textplugin {
	typedef int(*proc)(int x, int y, int width, const char* id, int value, const char* label, const char* tips);
	const char*			name;
	proc				render;
	textplugin*			next;
	static textplugin*	first;
	textplugin(const char* name, proc e);
	static textplugin*	find(const char* name);
};
extern rect				clipping; // Clipping area
extern color			fore; // Foreground color (curently selected color)
extern color			fore_stroke; // foreground stroke color
extern const sprite*	font; // Currently selected font
//
int						aligned(int x, int width, unsigned state, int string_width);
int						alignedh(const rect& rc, const char* string, unsigned state);
areas					area(rect rc);
bool					areb(rect rc);
void					bezier(int x0, int y0, int x1, int y1, int x2, int y2);
void					bezierseg(int x0, int y0, int x1, int y1, int x2, int y2);
void					blit(surface& dest, int x, int y, int width, int height, unsigned flags, surface& dc, int xs, int ys);
void					blit(surface& dest, int x, int y, int width, int height, unsigned flags, surface& source, int x_source, int y_source, int width_source, int height_source);
void					breakmodal(int result);
void					buttoncancel();
void					buttonok();
extern surface*			canvas;
void					circle(int x, int y, int radius);
void					circle(int x, int y, int radius, const color c1);
void					circlef(int x, int y, int radius, const color c1, unsigned char alpha = 0xFF);
void					create(int x, int y, int width, int height, unsigned flags, int bpp);
void					decortext(unsigned flags);
extern eventproc		domodal;
bool					dragactive(const void* p);
bool					dragactive();
void					dragbegin(const void* p);
extern point			dragmouse;
void					execute(eventproc proc, int value = 0);
rect					getarea();
int						getbpp();
color					getcolor(color normal, unsigned flags);
color					getcolor(rect rc, color normal, color hilite, unsigned flags);
int						getheight();
int						getresult();
int						getwidth();
void					getwindowpos(point& pos, point& size, unsigned* flags);
void					glyph(int x, int y, int sym, unsigned flags);
void					gradv(rect rc, const color c1, const color c2, int skip = 0);
void					gradh(rect rc, const color c1, const color c2, int skip = 0);
const sprite*			gres(const char* name, const char* folder = 0);
int						hittest(int x, int test_x, const char* string, int lenght);
int						hittest(rect rc, const char* string, unsigned state, point mouse);
inline bool				ischecked(unsigned flags) { return (flags&Checked) != 0; }
inline bool				isdisabled(unsigned flags) { return (flags&Disabled) != 0; }
bool					isfocused();
inline bool				isfocused(unsigned flags) { return (flags&Focused) != 0; }
bool					ismodal();
void					image(int x, int y, const sprite* e, int id, int flags, unsigned char alpha = 0xFF);
void					image(int x, int y, const sprite* e, int id, int flags, unsigned char alpha, color* pal);
void					initialize();
char*					key2str(char* result, int key);
void					line(int x1, int y1, int x2, int y2); // Draw line
void					line(int x1, int y1, int x2, int y2, color c1); // Draw line
inline void				line(point p1, point p2, color c1) { line(p1.x, p1.y, p2.x, p2.y, c1); }
void					linet(int x1, int y1, int x2, int y2);
inline void				linet(point p1, point p2) { linet(p1.x, p1.y, p2.x, p2.y); }
extern float			linw;
extern char				link[4096];
extern bool				mouseinput;
extern color*			palt;
void					pixel(int x, int y);
void					pixel(int x, int y, unsigned char alpha);
unsigned char*			ptr(int x, int y);
int						rawinput();
void					rectb(rect rc); // Draw rectangle border
void					rectb(rect rc, color c1);
void					rectf(rect rc); // Draw rectangle area. Right and bottom side is one pixel less.
void					rectf(rect rc, color c1);
void					rectf(rect rc, color c1, unsigned char alpha);
void					rectx(rect rc, color c1);
void					savefocus();
void					set(void(*proc)(int& x, int& y, int x0, int x2, int* max_width, int& w, const char* id));
void					setcaption(const char* string);
void					setclip(rect rc);
inline void				setclip() { clipping.set(0, 0, getwidth(), getheight()); }
void					settimer(unsigned milleseconds);
const char*				skiptr(const char* string);
void					spline(point* points, int n);
void					stroke(int x, int y, const sprite* e, int id, int flags, unsigned char thin = 1, unsigned char* koeff = 0);
void					syscursor(bool enable);
void					sysredraw();
void					text(int x, int y, const char* string, int count = -1, unsigned flags = 0);
int						text(rect rc, const char* string, unsigned state = 0, int* max_width = 0);
int						textc(int x, int y, int width, const char* string, int count = -1, unsigned flags = 0, bool* clipped = 0);
int						textbc(const char* string, int width);
int						textlb(const char* string, int index, int width, int* line_index = 0, int* line_count = 0);
int						texte(rect rc, const char* string, unsigned flags, int i1, int i2);
int						textf(int x, int y, int width, const char* text, int* max_width = 0, int min_height = 0, int* cashe_height = 0, const char** cashe_string = 0, int tab_width = 0);
int						textf(rect& rc, const char* string, int tab_width = 0);
int						texth();
int						texth(const char* string, int width);
int						textw(int sym);
int						textw(const char* string, int count = -1);
int						textw(rect& rc, const char* string);
int						textw(sprite* font);
void					triangle(point v1, point v2, point v3, color c1);
void					updatewindow();
void					write(const char* url, unsigned char* bits, int width, int height, int bpp, int scanline, color* pallette);
}
namespace draw {
int						addbutton(rect& rc, bool focused, const char* t1, int k1, const char* tt1, const char* t2, int k2, const char* tt2);
bool					addbutton(rect& rc, bool focused, const char* t1, int k1, const char* tt1);
bool					buttonh(rect rc, bool checked, bool focused, bool disabled, bool border, color value, const char* string, int key, bool press, const char* tips = 0);
bool					buttonh(rect rc, bool checked, bool focused, bool disabled, bool border, const char* string, int key = 0, bool press = false, const char* tips = 0);
bool					buttonv(rect rc, bool checked, bool focused, bool disabled, bool border, const char* string, int key = 0, bool press = false);
int						clipart(int x, int y, int width, unsigned flags, const char* string);
void					scrollh(const struct rect& scroll, int& origin, int count, int maximum, bool focused);
void					scrollv(const rect& scroll, int& origin, int count, int maximum, bool focused);
int						sheetline(rect rc, bool background);
void					splitv(int x, int y, int& value, int height, int size, int minimum, int maximum, bool right_align);
void					splith(int x, int y, int width, int& value, int size, int minimum, int maximum, bool down_align);
void					statusbar(const char* format, ...);
void					statusbarv(const char* format, const char* format_param);
int						statusbardw();
int						tabs(int x, int y, int width, bool show_close, bool right_side, void** data, int start, int count, int current, int* hilite, fntext gtext = 0, rect position = {0, 0, 0, 0});
int						tabs(rect rc, bool show_close, bool right_side, void** data, int start, int count, int current, int* hilite, fntext gtext, rect position = {0, 0, 0, 0});
bool					tool(const rect& rc, bool disabled, bool checked, bool press, bool focused = false, int key = 0);
void					tooltips(const char* format, ...);
void					tooltips(int x, int y, int width, const char* format, ...);
void					tooltipsv(int x, int y, int width, const char* format, const char* format_param);
}