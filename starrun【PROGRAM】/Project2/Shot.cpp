#include <DxLib.h>
#include "ImageMng.h"
#include "EnemyAct.h"
#include "Shot.h"
#include "GameScene.h"


Shot::Shot(VECTOR2 pos, VECTOR2 offset, bool objType,int speed) 
{
	this->pos = pos;
	this->offset = offset;
	this->speed = speed/10 + 5;
	if (objType)
	{
		Shot::init();

	}
}


Shot::~Shot()
{
	OutputDebugString("Á‚¦‚½‚æ\n");
}

bool Shot::initAnim(void)
{

	return true;
}

bool Shot::init(void)
{
	Obj::init("image/Pshot.png", VECTOR2{ 64,32 }, VECTOR2{29,1 },pos);
	AddAnim("’e", 0, 0, 28,1, true);

	SetAnim("’e");
	return true;
}

void Shot::SetMove(const GameCtl & controller, weekListObj objList)
{
	
	if (time > 29)
	{
		time = 0;
	}
	pos.x += speed;


	if (!lpEnemyAct.GetshotFlag())
	{
		pos.x = 0;		//shot‚Ìpos.x
	}
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
