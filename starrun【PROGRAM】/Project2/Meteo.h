#pragma once
#include "Obj.h"
class Meteo :
	public Obj
{
public:
	Meteo();
	~Meteo();
	bool initAnim(void);
	bool init(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//
	void Draw(void);
	double RotAngle;
	VECTOR2 offset;

	unsigned int waitCnt[AT_DRAW_MAX];
	VECTOR2 enemy_speed;
	int time;
};

