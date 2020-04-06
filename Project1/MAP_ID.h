#pragma once

enum class Map_ID
{
	mine,
	hut,
	field,
	water,
	water2,
	plain,
	sand,
	forest,
	rock,
	NON,
	MAX
};


Map_ID operator+(const Map_ID& r, const int& l);

