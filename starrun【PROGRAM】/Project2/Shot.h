#pragma once
#include "Obj.h"
class Shot :
	public Obj
{
public:
	Shot(VECTOR2 pos,VECTOR2 offset,bool objType);
	~Shot();
	bool initAnim(void);
	bool init(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//
	//void Draw(void);
	double RotAngle;
	VECTOR2 offset;
	
	int time;
};

