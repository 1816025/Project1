#pragma once

enum class Map_ID
{
	BOOK_SHELF,
	COUNTER,
	CORRIDOR,
	NON,
	CHAIR,
	DESK,
	DESK2,
	DESK3,
	DESK4,
	DESK5,
	DESK6,
	MAX
};

Map_ID operator+(const Map_ID& r, const int& l);
Map_ID operator-(const Map_ID& r, const int& l);
Map_ID operator+(const Map_ID& r, const Map_ID& l);
Map_ID operator-(const Map_ID& r, const Map_ID& l);

