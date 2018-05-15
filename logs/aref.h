#pragma once

template<class T>
struct aref {
	T*						data;
	unsigned				count;
	constexpr aref() = default;
	template<unsigned N> constexpr aref(T(&data)[N]) : data(data), count(N) {}
	constexpr T& operator[](int index) { return data[index]; }
	constexpr const T& operator[](int index) const { return data[index]; }
	explicit operator bool() const { return count != 0; }
	T*						add() { return &data[count++]; }
	void					add(const T& e) { data[count++] = e; }
	constexpr T*			begin() { return data; }
	constexpr const T*		begin() const { return data; }
	void					clear() { count = 0; }
	constexpr T*			end() { return data + count; }
	constexpr const T*		end() const { return data + count; }
	int						indexof(const T* t) const { if(t<data || t>data + count) return -1; return t - data; }
	int						indexof(const T t) const { for(unsigned i = 0; i < count; i++) if(data[i] == t) return i; return -1; }
	bool					is(const T value) const { return indexof(value) != -1; }
	void					remove(int index, int elements_count = 1) { if(index < 0 || index >= count) return; count -= elements_count; if(index >= count) return; memmove(data + index, data + index + elements_count, sizeof(data[0])*(count - index)); }
};