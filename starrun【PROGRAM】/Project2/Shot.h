#pragma once
#include "Obj.h"
class Shot :
	public Obj
{
public:
	Shot(VECTOR2 pos,VECTOR2 offset,bool objType);
	~Shot();
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//
	//void Draw(void);
};

