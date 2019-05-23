#include <DxLib.h>
#include "ImageMng.h"
#include "Shot.h"
#include "GameScene.h"


Shot::Shot(VECTOR2 pos, VECTOR2 offset, bool objType) 
{
	this->pos = pos;
	this->offset = offset;
	Shot::init();
}


Shot::~Shot()
{
}

bool Shot::initAnim(void)
{

	return true;
}

bool Shot::init(void)
{
	Obj::init("image/Pshot.png", VECTOR2{ 64,32 }, VECTOR2{29,1 },pos);
	AddAnim("’e", 0, 0, 1, 2, true);

	SetAnim("’e");
	time = 0;
	RotAngle = 0.0;
	return true;
}

void Shot::SetMove(const GameCtl & controller, weekListObj objList)
{
	
	time++;
	if (time > 29)
	{
		time = 0;
	}
	pos.x+=5;
	SetPos(pos);
	//Draw(time);
}

//void Shot::Draw(void)
//{
//	VECTOR2 tmp = { pos.x + + offset.x, pos.y  + offset.y };
//	if (tmp > VECTOR2{ 0 , 0 }&&tmp < VECTOR2{ SCREEN_SIZE_X,SCREEN_SIZE_Y })
//	{
//		Obj::Draw(time);
//	}
//
//}
