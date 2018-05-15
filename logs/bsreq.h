#pragma once

// Macros for defining metadata information, where
// 'c' is class,
// 'f' is field of this class
#define	BSREQ(c, f) {#f, (const int)&((c*)0)->f,\
bsgetsize<decltype(c::f)>::value,\
sizeof(c::f),\
bsgetcount<decltype(c::f)>::value,\
bsgetmeta<decltype(c::f)>::value,\
bsgetref<decltype(c::f)>::value,\
bsgetsubtype<decltype(c::f)>::value}
// Macros for metatype enum declaration
#define	BSDECLENUM(c) bsreq c##_type[];\
template<> struct bsgetmeta<c##_s> { static constexpr const bsreq* value = c##_type; };
#define	BSDECLTYPE(c) bsreq c##_type[];\
template<> struct bsgetmeta<c##> { static constexpr const bsreq* value = c##_type; };

const int			bsreq_max_text = 8192;
extern "C" int		strcmp(const char* s1, const char* s2);

// Get count of reference
template<class T> struct bsgetref {
	static constexpr int value = 0;
};
template<class T> struct bsgetref<T*> {
	static constexpr int value = 1 + bsgetref<T>::value;
};
template<class T, int N> struct bsgetref<T[N]> {
	static constexpr int value = bsgetref<T>::value;
};
template<class T> struct bsgetref<T[]> {
	static constexpr int value = bsgetref<T>::value;
};
// Get type size
template<class T> struct bsgetsize{
	static constexpr int value = sizeof(T);
};
template<class T, unsigned N> struct bsgetsize<T[N]> {
	static constexpr int value = sizeof(T);
};
template<class T> struct bsgetsize<T[]> {
	static constexpr int value = sizeof(T);
};
template<class T> struct bsgetcount {
	static constexpr int value = 1;
};
// Get type count
template<class T, unsigned N> struct bsgetcount<T[N]> {
	static constexpr int value = N;
};
template<class T> struct bsgetcount<T[]> {
	static constexpr int value = 0;
};
template<class T> struct bsgetsubtype {
	static constexpr const char* value = __is_enum(T) ? "enum" : "";
};
template<class T> struct bsgetsubtype<T*> {
	static constexpr const char* value = bsgetsubtype<T>::value;
};
template<class T, unsigned N> struct bsgetsubtype<T[N]> {
	static constexpr const char* value = bsgetsubtype<T>::value;
};
// Metadata field descriptor
struct bsreq {
	const char*		id; // field identifier
	unsigned		offset; // offset from begin of class or object
	unsigned		size; // size of single element
	unsigned		lenght; // total size in bytes of all field (array has size*count)
	unsigned		count; // count of elements
	const bsreq*	type; // metadata of element
	unsigned char	reference; // 1+ is reference
	const char*		subtype; // name of subtype (like 'enum') or emphty string for scalar
	//
	operator bool() const { return id != 0; }
	//
	const bsreq*	find(const char* name) const;
	const bsreq*	find(const char* name, const bsreq* type) const;
	int				get(const void* p) const;
	const char*		getdata(char* result, const char* id, const void* object, bool tobuffer) const;
	const bsreq*	getkey() const;
	bool			isenum() const { return issubtype("enum"); }
	bool			issimple() const { return type == 0; }
	bool			issubtype(const char* id) const { return strcmp(subtype, id) == 0; }
	bool			match(const void* p, const char* name) const;
	const char*		ptr(const void* data) const { return (const char*)data + offset; }
	const char*		ptr(const void* data, int index) const { return (const char*)data + offset + index*size; }
	void			set(const void* p, int value) const;
	void			setdata(const char* result, const char* id, void* object) const;
};
struct bsval {
	const bsreq*	type;
	void*			data;
	operator bool() const { return data != 0; }
	int				get() const { return type->get(type->ptr(data)); }
	void			set(int value) { type->set(type->ptr(data), value); }
};
extern bsreq		any_type[]; // any existing object type, exept number (and other integer) or text
extern bsreq		number_type[]; // standart integer value
extern bsreq		text_type[]; // stantart zero ending string
extern bsreq		bsreq_type[]; // requisit metadata
// Default type autodetection
template<class T> struct bsgetmeta {
	static constexpr const bsreq* value = number_type;
};
template<> struct bsgetmeta<const char*> {
	static constexpr const bsreq* value = text_type;
};
template<> struct bsgetmeta<bsreq> {
	static constexpr const bsreq* value = bsreq_type;
};
template<class T> struct bsgetmeta<const T> {
	static constexpr const bsreq* value = bsgetmeta<T>::value;
};
template<class T> struct bsgetmeta<T*> {
	static constexpr const bsreq* value = bsgetmeta<T>::value;
};
template<class T, unsigned N> struct bsgetmeta<T[N]> {
	static constexpr const bsreq* value = bsgetmeta<T>::value;
};