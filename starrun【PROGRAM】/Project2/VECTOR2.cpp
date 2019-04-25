#include "stdafx.h"
#include "VECTOR2.h"


VECTOR2::VECTOR2()
{
}

VECTOR2::VECTOR2(int x, int y)
{
	this->x = x;
	this->y = y;
}


VECTOR2::~VECTOR2()
{
}

VECTOR2 & VECTOR2::operator=(const VECTOR2 & vec)
{
/*(*this).x = vec.x;
  (*this).y = vec.y;*/
	this->x = vec.x;
	this->y = vec.y;
	return (*this);
}

int & VECTOR2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else 
	{
		return x;
	}
	
}

VECTOR2 & VECTOR2::operator+=(const VECTOR2 & vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

VECTOR2 & VECTOR2::operator-=(const VECTOR2 & vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

VECTOR2 & VECTOR2::operator*=(int k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

VECTOR2 & VECTOR2::operator/=(int k)
{
	if (k != 0)
	{
		this->x /= k;
		this->y /= k;
	}
	return (*this);
}

VECTOR2 VECTOR2::operator+()const
{
	return (*this);
}

VECTOR2 VECTOR2::operator-()const
{
	return VECTOR2(-this->x,-this->y);
}

//VECTOR2 + int
VECTOR2 operator+(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x + v;
	vec.y = u.y + v;

	return vec;
}

//VECTOR2 - int
VECTOR2 operator-(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x - v;
	vec.y = u.y - v;

	return vec;
}

//VECTOR2 * int
VECTOR2 operator*(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x * v;
	vec.y = u.y * v;

	return vec;
}

//VECTOR2 / int
VECTOR2 operator/(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x / v;
	vec.y = u.y / v;

	return vec;
}

//VECTOR2 % int
VECTOR2 operator%(const VECTOR2 & u, int v)
{
	VECTOR2 vec;
	vec.x = u.x % v;
	vec.y = u.y % v;

	return vec;
}

//int * VECTOR2
VECTOR2 operator+(int u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u + v.x;
	vec.y = u + v.y;
	return vec;
}

//VECTOR2 + VECTOR2
VECTOR2 operator+(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;
}

//VECTOR2 - VECTOR2
VECTOR2 operator-(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;
}

VECTOR2 operator/(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;
}

VECTOR2 operator%(const VECTOR2 & u, const VECTOR2 & v)
{
	VECTOR2 vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;
	return vec;
}


