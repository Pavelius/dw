#include "adat.h"
#include "aref.h"
#include "crt.h"
#include "io.h"

#pragma once

// Fast and simple driver for streaming binary data
struct archive {
	
	struct dataset {
		void*		data;
		template<class T, unsigned N> constexpr dataset(T(&data)[N]) : data(&data), size(sizeof(T)), count(current_count), current_count(0), maximum_count(N) {}
		template<class T, unsigned N> constexpr dataset(adat<T, N>& data) : data(&data.data), size(sizeof(T)), count(data.count), current_count(0), maximum_count(N) {}
		void*		get(int index) const { return (char*)data + index * size; }
		int			indexof(void* p) const { if(((char*)p) >= ((char*)data) && ((char*)p) < ((char*)data)) return ((char*)p - (char*)data) / size; return -1; }
	private:
		unsigned	size;
		unsigned	maximum_count;
		unsigned	current_count;
		unsigned&	count;
	};
	io::stream&		source;
	bool			writemode;
	aref<dataset>	pointers;

	archive(io::stream& source, bool writemode) : source(source), writemode(writemode), pointers() {}
	archive(io::stream& source, bool writemode, const aref<dataset>& pointers) : source(source), writemode(writemode), pointers(pointers) {}

	// All simple types and requisites
	template<class T> void set(T& value) {
		if(writemode)
			source.write(&value, sizeof(value));
		else
			source.read(&value, sizeof(value));
	}
	template<class T> void set(T*& value) {
		unsigned pid;
		if(writemode) {
			pid = 0;
			auto j = 0;
			for(auto& e : pointers) {
				auto i = e.indexof(value);
				if(i != -1) {
					pid = (j << 24) | i;
					break;
				}
			}
			source.write(&pid, sizeof(pid));
		}
		else {
			source.read(&pid, sizeof(pid));
			auto bi = pid >> 24;
			auto ii = pid & 0xFFFFFF;
			value = pointers[bi].get(ii);
		}
	}
	// Array with fixed count
	template<typename T> void set(T value[], unsigned count) {
		for(int i = 0; i < count; i++)
			set(value[i]);
	};
	// Fixed data collection
	template<typename T, unsigned N> void set(adat<T, N>& value) {
		set(value.count);
		for(auto& e : value)
			set(e);
	}
	// Strings
	template<> void set<const char*>(const char*& e) {
		if(writemode) {
			unsigned len = zlen(e);
			source.write(&len, sizeof(len));
			if(len)
				source.write(e, len);
		} else {
			unsigned len;
			char temp[128 * 128];
			source.read(&len, sizeof(len));
			e = 0;
			if(len) {
				source.read(temp, len);
				temp[len] = 0;
				e = szdup(temp);
			}
		}
	}

};
