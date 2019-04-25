#pragma once
class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x ,int y);
	~VECTOR2();
	int x;
	int y;

	//ë„ì¸ââéZéq------------------------------------------
	VECTOR2& operator = (const VECTOR2& vec);

	//ìYÇ¶éöââéZéq----------------------------------------
	int& operator[](int i);

	//î‰ärââéZéq------------------------------------------
	  /*ì«Ç›çûÇ›êÍópÇ≈égópÇ∑ÇÈÇ∆Ç´ÇÃÇ›constÇégópÇ∑ÇÈ*/
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

	//íPçÄââéZéq------------------------------------------
	VECTOR2& operator +=(const VECTOR2& vec);
	VECTOR2& operator -=(const VECTOR2& vec);
	VECTOR2& operator *=(int k);
	VECTOR2& operator /=(int k);

	VECTOR2 operator+()const;
	VECTOR2 operator-()const;
	
};

//Õﬁ∏ƒŸÇÃââéZ//////////////////////////////////
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







