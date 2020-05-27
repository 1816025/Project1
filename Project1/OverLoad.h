#pragma once
#include "Unit.h"
#include "Achievement.h"
#include "Game.h"
#include "VECTOR2.h"

bool operator == (const GroupParameter& a, const GroupParameter& b);
bool operator == (const GroupParameter& a, const VECTOR2& b);
bool operator >= (const AchievementStatus& a, const AchievementStatus& b);
bool operator >= (const Date& a, const Date& b);



