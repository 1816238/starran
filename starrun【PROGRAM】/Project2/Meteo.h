#pragma once
#include "Obj.h"
#include "Enemy.h"
class Meteo :
	public Obj
{
public:
	Meteo(VECTOR2 pos, VECTOR2 offset);
	~Meteo();
	bool initAnim(void);
	bool init(void);
	OBJ_TYPE CheckObjType(void);
	bool CheckDeath(void) {return deathFlag;};
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//
	double RotAngle;
	VECTOR2 offset;
	unsigned int waitCnt[AT_DRAW_MAX];
	VECTOR2 enemy_speed;
	int speed;
	int time;
	bool deathFlag;
};

