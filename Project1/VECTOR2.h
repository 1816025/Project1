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

//��r���Z�q------------------------------------------
	  /*�ǂݍ��ݐ�p�Ŏg�p����Ƃ��̂�const���g�p����*/
bool operator==(const VECTOR2 & vec)const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}
bool operator>=(const VECTOR2 & vec)const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}
bool operator<=(const VECTOR2 & vec)const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}
bool operator>(const VECTOR2 & vec)const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}
bool operator<(const VECTOR2 & vec)const
{
	return ((this->x < vec.x) && (this->y < vec.y));
}
bool operator!=(const VECTOR2 & vec)const
{
	return !((this->x == vec.x) && (this->y == vec.y));
	/*return ((this->x != vec.x) || (this->y != vec.y));*/
}

};

	VECTOR2 operator+(const VECTOR2& r, const VECTOR2& l);
	VECTOR2 operator-(const VECTOR2& r, const VECTOR2& l);
	VECTOR2 operator/(const VECTOR2& r, const VECTOR2& l);
