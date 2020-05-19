#pragma once

enum class Map_ID
{
	BOOK_SHELF,
	COUNTER,
	DESK,
	CHAIR,
	NON,
	MAX
};

Map_ID operator+(const Map_ID& r, const int& l);
Map_ID operator-(const Map_ID& r, const int& l);
Map_ID operator+(const Map_ID& r, const Map_ID& l);
Map_ID operator-(const Map_ID& r, const Map_ID& l);

