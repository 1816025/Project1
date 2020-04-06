#include "MAP_ID.h"

Map_ID operator+(const Map_ID & r, const int & l)
{
	return static_cast<Map_ID>(static_cast<int>(r) + l);
}
