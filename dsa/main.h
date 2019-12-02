#include "crt.h"

#pragma once

enum ability_s : unsigned char {
	Courage, Wisdom, Charisma, Dexterity, Strenght,
};

template<unsigned N>
class storage {
	char			data[N];
public:
	constexpr int	get(int i) const { return data[i]; }
	constexpr void	set(int i, int v) { data[i] = v; }
};

class creature {
	storage<Strenght + 1>	abilities;
public:
	constexpr int		get(ability_s i) const { return abilities.get(i); }
	constexpr void		set(ability_s i, int v) { abilities.set(i, v); }
};