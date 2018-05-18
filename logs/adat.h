#include "initializer_list.h"

#pragma once

template<class T, int count_max = 128>
struct adat {
	T						data[count_max];
	unsigned				count;
	//
	constexpr adat() : data(), count(0) {}
	constexpr adat(std::initializer_list<T> list) : count(0) { for(auto& e : list) *add() = e; }
	constexpr const T& operator[](unsigned index) const { return data[index]; }
	constexpr T& operator[](unsigned index) { return data[index]; }
	operator bool() const { return count != 0; }
	//
	T*						add() { if(count < count_max) return data + (count++); return 0; }
	void					add(const T& e) { if(count < count_max) data[count++] = e; }
	T*						begin() { return data; }
	const T*				begin() const { return data; }
	void					clear() { count = 0; }
	T*						end() { return data + count; }
	const T*				end() const { return data + count; }
	template<class Z> T*	find(Z id) { auto e1 = data + count; for(T* e = data; e < e1; e++) { if(e->id == id) return e; } return 0; }
	inline int				getcount() const { return count; }
	int						indexof(const T* e) const { if(e >= data && e <= data + count) return e - data; return -1; }
	int						indexof(const T t) const { for(unsigned i = 0; i < count; i++) if(data[i] == t) return i; return -1; }
	bool					is(const T t) const { for(unsigned i = 0; i < count; i++) if(data[i] == t) return true; return false; }
	void					remove(int index, int remove_count = 1) { if(index < 0) return; if(index<int(count - 1)) memcpy(data + index, data + index + 1, sizeof(data[0])*(count - index - 1)); count--; }
};