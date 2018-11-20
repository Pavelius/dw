#include "collection.h"

#pragma once

// Macros for defining metadata information, where
// 'c' is class,
// 'f' is field of this class
// 't' is type
#define	BSREQ(c, f, t) {#f, (const int)&((c*)0)->f,\
bsreq::bsgetsize<decltype(c::f)>::value,\
sizeof(c::f),\
bsreq::bsgetcount<decltype(c::f)>::value,\
t,\
bsreq::bsgetref<decltype(c::f)>::value,\
bsreq::bsgetsubtype<decltype(c::f)>::value}

const int			bsreq_max_text = 8192;
extern "C" int		strcmp(const char* s1, const char* s2);

// Metadata field descriptor
struct bsreq {
	enum subtype_s : unsigned char { Scalar, Enum, ADat, ARef, CFlags };
	template<int V> struct ival { static constexpr int value = V; };
	// Get count of reference
	template<class T> struct bsgetref : ival<0> {};
	template<class T> struct bsgetref<T*> : ival<1 + bsgetref<T>::value> {};
	template<class T, int N> struct bsgetref<T[N]> : ival<bsgetref<T>::value> {};
	template<class T> struct bsgetref<T[]> : ival<bsgetref<T>::value> {};
	// Get type size
	template<class T> struct bsgetsize : ival<sizeof(T)> {};
	template<class T, unsigned N> struct bsgetsize<T[N]> : ival<sizeof(T)> {};
	template<class T> struct bsgetsize<T[]> : ival<sizeof(T)> {};
	// Get type count
	template<class T> struct bsgetcount : ival<1> {};
	template<class T, unsigned N> struct bsgetcount<T[N]> : ival<N> {};
	template<class T> struct bsgetcount<T[]> : ival<0> {};
	template<class T, unsigned N> struct bsgetcount<adat<T, N>> : ival<N> {};
	// Get subtype
	template<class T> struct bsgetsubtype { static constexpr subtype_s value = __is_enum(T) ? Enum : Scalar; };
	template<class T> struct bsgetsubtype<T*> { static constexpr subtype_s value = bsgetsubtype<T>::value; };
	template<class T, unsigned N> struct bsgetsubtype<T[N]> { static constexpr subtype_s value = bsgetsubtype<T>::value; };
	template<class T, unsigned N> struct bsgetsubtype<adat<T, N>> { static constexpr subtype_s value = ADat; };
	template<class T> struct bsgetsubtype<aref<T>> { static constexpr subtype_s value = ARef; };
	template<class T, class DT> struct bsgetsubtype<cflags<T, DT>> { static constexpr subtype_s value = CFlags; };
	const char*		id; // field identifier
	unsigned		offset; // offset from begin of class or object
	unsigned		size; // size of single element
	unsigned		lenght; // total size in bytes of all field (array has size*count)
	unsigned		count; // count of elements
	const bsreq*	type; // metadata of element
	unsigned char	reference; // 1+ is reference
	subtype_s		subtype; // name of subtype (like 'enum') or emphty string for scalar
	//
	operator bool() const { return id != 0; }
	//
	const bsreq*	find(const char* name) const;
	const bsreq*	find(const char* name, const bsreq* type) const;
	int				get(const void* p) const;
	const bsreq*	getkey() const;
	bool			is(subtype_s value) const { return subtype == value; }
	bool			issimple() const { return type == 0; }
	bool			match(const void* p, const char* name) const;
	const char*		ptr(const void* data) const { return (const char*)data + offset; }
	const char*		ptr(const void* data, int index) const { return (const char*)data + offset + index * size; }
	void			set(const void* p, int value) const;
};
struct bsval {
	const bsreq*	type;
	void*			data;
	operator bool() const { return data != 0; }
	int				get() const { return type->get(type->ptr(data)); }
	void			set(int value) { type->set(type->ptr(data), value); }
};
extern bsreq		any_type[]; // any existing object type, exept number (and other integer) or text
extern bsreq		bsreq_type[]; // requisit metadata
extern bsreq		number_type[]; // standart integer value
extern bsreq		text_type[]; // stantart zero ending string