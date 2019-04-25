#pragma once
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x ,int y);
	~VECTOR2();
	int x;
	int y;

	//������Z�q------------------------------------------
	VECTOR2& operator = (const VECTOR2& vec);

	//�Y�������Z�q----------------------------------------
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

	//�P�����Z�q------------------------------------------
	VECTOR2& operator +=(const VECTOR2& vec);
	VECTOR2& operator -=(const VECTOR2& vec);
	VECTOR2& operator *=(int k);
	VECTOR2& operator /=(int k);

	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
	
};

//�޸�ق̉��Z//////////////////////////////////
//VECTOR2 + int-------------------------------- 
VECTOR2 operator+(const VECTOR2 &u, int v);

//VECTOR2 - int--------------------------------
VECTOR2 operator-(const VECTOR2 &u, int v);

//VECTOR2 * int--------------------------------
VECTOR2 operator*(const VECTOR2 &u, int v);

//VECTOR2 / int--------------------------------
VECTOR2 operator/(const VECTOR2 &u, int v);

//VECTOR2 % int--------------------------------
VECTOR2 operator%(const VECTOR2 &u, int v);

//int * VECTOR2--------------------------------
VECTOR2 operator+(int u, const VECTOR2 &v);

//VECTOR2 + VECTOR2----------------------------
VECTOR2 operator+(const VECTOR2 &u, const VECTOR2 &v);

//VECTOR2 - VECTOR2----------------------------
VECTOR2 operator-(const VECTOR2 &u, const VECTOR2 &v);

//VECTOR2 / VECTOR2----------------------------
VECTOR2 operator/(const VECTOR2 &u, const VECTOR2 &v);

//VECTOR2 / VECTOR2----------------------------
VECTOR2 operator%(const VECTOR2 &u, const VECTOR2 &v);







