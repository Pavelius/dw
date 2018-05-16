#include "adat.h"
#include "bsreq.h"
#include "collection.h"

#pragma once

// Declare metadata for type 'cls'. Variables 'cls_type' and 'cls_data' must exist.
// Datasource can be fixed array, adat, or single declared element.
#define BSMETA(cls) bsdata cls##_manager(#cls, cls##_data, cls##_type, true)
// Class special adat specification
template<class T, unsigned N> struct bsgetsubtype<adat<T, N>> { static constexpr const char* value = "adat"; };
template<class T, unsigned N> struct bsgetmeta<adat<T, N>> { static constexpr const bsreq* value = bsgetmeta<T>::value; };
template<class T, unsigned N> struct bsgetcount<adat<T, N>> : bsconst<N> {};

enum bserror_s {
	NoParserError,
	ErrorExpectedIdentifier, ErrorExpectedArrayField,
	ErrorNotFoundBase1p, ErrorNotFoundType, ErrorNotFoundIdentifier1p, ErrorNotFoundMember1pInBase2p,
	ErrorFile2pNotFound,
};
struct bsdata : collection {
	struct parser {
		virtual void	error(bserror_s id, const char* url, int line, int column, const char** format_param) {}
		virtual bool	comparer(void* object, const bsreq* type) { return true; }
		virtual bserror_s validate(const char* id, const char* value) { return NoParserError; }
	};
	const char*			id;
	const bsreq*		fields;
	void*				data;
	unsigned			size;
	bsdata*				next;
	static bsdata*		first;
	//
	template<class T, unsigned N> bsdata(const char* id, T(&data)[N], const bsreq* fields, bool make_global) : id(id), fields(fields), data(&data), size(sizeof(T)), count(current_count), current_count(N), next(0), maximum_count(N) { globalize(); }
	template<class T, unsigned N> constexpr bsdata(const char* id, T(&data)[N], const bsreq* fields) : id(id), fields(fields), data(&data), size(sizeof(T)), count(current_count), current_count(N), next(0), maximum_count(N) {}
	template<class T> bsdata(const char* id, T& data, const bsreq* fields, bool make_global) : id(id), fields(fields), data(&data), size(sizeof(T)), count(current_count), current_count(0), next(0), maximum_count(1) { globalize(); }
	template<class T> constexpr bsdata(const char* id, T& data, const bsreq* fields) : id(id), fields(fields), data(&data), size(sizeof(T)), count(current_count), current_count(0), next(0), maximum_count(1) {}
	template<class T, unsigned N> bsdata(const char* id, adat<T, N>& data, const bsreq* fields, bool make_global) : id(id), fields(fields), data(&data.data), size(sizeof(T)), count(data.count), current_count(0), next(0), maximum_count(N) { globalize(); }
	template<class T, unsigned N> constexpr bsdata(const char* id, adat<T, N>& data, const bsreq* fields) : id(id), fields(fields), data(&data.data), size(sizeof(T)), count(data.count), current_count(0), next(0), maximum_count(N) {}
	//
	void*				add() override;
	char*				begin() const { return (char*)data; }
	void				clear() override { count = 0; }
	char*				end() const { return (char*)data + size * count; }
	void*				get(int index) const override { return (char*)data + index * size; }
	unsigned			getcount() const override { return count; }
	unsigned			getmaxcount() const override { return maximum_count; }
	static const char*	gets(const bsreq* type, int index, const char* field = "name");
	unsigned			getsize() const override { return size; }
	void				globalize();
	int					indexof(const void* element) const override;
	static bsdata*		find(const char* id);
	static bsdata*		find(const bsreq* id);
	void*				find(const bsreq* id, const char* value);
	static bsdata*		findbyptr(const void* object);
	static void			read(const char* url, bsdata** custom = 0);
	void				remove(int index, int count = 1) override;
	void				setcount(unsigned value) { count = value; }
	static void			write(const char* url, bsdata** bases, bsdata::parser* parser = 0);
	static void			write(const char* url, const char* baseid);
private:
	unsigned			maximum_count;
	unsigned			current_count;
	unsigned&			count;
};