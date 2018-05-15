#pragma once

// Macros for defining metadata information, where
// 'cls' is original class,
// 'field' is field of this class,
// 'type' is reference to type metadata.
#define	BSREQ(cls, field) {#field, (const int)&((cls*)0)->field,\
bssize_info<decltype(cls::field)>::value,\
sizeof(cls::field),\
bscount_info<decltype(cls::field)>::value,\
bsgetmeta<decltype(cls::field)>::value,\
bsref_info<decltype(cls::field)>::value,\
bsgetsubtype<decltype(cls::field)>::value}

const int			bsreq_max_text = 8192;
extern "C" int		strcmp(const char* s1, const char* s2);

template<class T> struct bsref_info {
	static constexpr int value = 0;
};
template<class T> struct bsref_info<T*> {
	static constexpr int value = 1 + bsref_info<T>::value;
};
template<class T, int N> struct bsref_info<T[N]> {
	static constexpr int value = bsref_info<T>::value;
};
template<class T> struct bsref_info<T[]> {
	static constexpr int value = bsref_info<T>::value;
};
template<class T> struct bssize_info {
	static constexpr int value = sizeof(T);
};
template<class T, unsigned N> struct bssize_info<T[N]> {
	static constexpr int value = sizeof(T);
};
template<class T> struct bssize_info<T[]> {
	static constexpr int value = 0;
};
template<class T> struct bscount_info {
	static constexpr int value = 1;
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
template<class T> struct bsgetmeta {
	static constexpr const bsreq* value = number_type;
};
template<> struct bsgetmeta<const char*> {
	static constexpr const bsreq* value = text_type;
};
template<> struct bsgetmeta<bsreq> {
	static constexpr const bsreq* value = bsreq_type;
};
template<class T> struct bsgetmeta<T*> {
	static constexpr const bsreq* value = bsgetmeta<T>::value;
};
template<class T> struct bsgetmeta<const T> {
	static constexpr const bsreq* value = bsgetmeta<T>::value;
};
template<class T, unsigned N> struct bsgetmeta<T[N]> {
	static constexpr const bsreq* value = bsgetmeta<T>::value;
};