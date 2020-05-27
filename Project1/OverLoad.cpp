#include "OverLoad.h"

bool operator==(const GroupParameter & a, const GroupParameter & b)
{
	return (a == b);
}

bool operator==(const GroupParameter & a, const VECTOR2 & b)
{
	return (a.pos == b);
}

bool operator>=(const AchievementStatus & a, const AchievementStatus & b)
{
	return (a.flag >= b.flag && a.date >= b.date && a.BookRank >= b.BookRank && a.BookCnt >= b.BookCnt &&a.CollectCnt >= b.CollectCnt);
}

bool operator>=(const Date & a, const Date & b)
{
	return (a.year >= b.year && a.month >= b.month&&a.day >= b.day && a.hour >= b.hour&&a.minute >= b.minute && a.daycycle >= b.daycycle);
}
