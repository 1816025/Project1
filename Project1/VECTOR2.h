#pragma once
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x,int y);
	~VECTOR2();
	int x;
	int y;

	int& operator[](int i);

};

	VECTOR2 operator+(const VECTOR2& r, const VECTOR2& l);
	VECTOR2 operator-(const VECTOR2& r, const VECTOR2& l);
	VECTOR2 operator/(const VECTOR2& r, const VECTOR2& l);
