#pragma once

enum class Map_ID
{
	mine,
	hut,
	field,
	water2,
	water,
	plain,
	sand,
	forest,
	rock,
	NON,
	MAX
};

Map_ID operator+(const Map_ID& r, const int& l);
Map_ID operator-(const Map_ID& r, const int& l);
Map_ID operator+(const Map_ID& r, const Map_ID& l);
Map_ID operator-(const Map_ID& r, const Map_ID& l);

#define Artifact_MAX	(Map_ID::water)
#define Nature_MAX	(static_cast<int>(Map_ID::rock - Map_ID::water) - 1)

