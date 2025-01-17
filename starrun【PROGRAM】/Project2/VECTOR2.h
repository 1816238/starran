#pragma once
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x ,int y);
	VECTOR2(float x ,int y);
	VECTOR2(int x ,float y);
	VECTOR2(float x ,float y);

	~VECTOR2();
	int x;
	int y;

	//代入演算子------------------------------------------
	VECTOR2& operator = (const VECTOR2& vec);

	//添え字演算子----------------------------------------
	int& operator[](int i);

	//比較演算子------------------------------------------
	  /*読み込み専用で使用するときのみconstを使用する*/
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

	//単項演算子------------------------------------------
	VECTOR2& operator +=(const VECTOR2& vec);
	VECTOR2& operator -=(const VECTOR2& vec);
	VECTOR2& operator *=(int k);
	VECTOR2& operator /=(int k);

	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
	
};

//ﾍﾞｸﾄﾙの演算//////////////////////////////////
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







