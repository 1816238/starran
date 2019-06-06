#include <DxLib.h>
#include "ImageMng.h"
#include "EnemyAct.h"
#include "Shot.h"
#include "GameScene.h"
#include "SoundMng.h"

Shot::Shot(VECTOR2 pos, VECTOR2 offset, OBJ_TYPE objType,int speed,int attack) 
{
	this->pos = pos;
	this->offset = offset;
	this->speed = speed/30 + 5;
	this->objType = objType;
	this->attack = 1+attack/30;
	Shot::init();

	
}

Shot::Shot(VECTOR2 pos, VECTOR2 offset, OBJ_TYPE objType, int speed)
{
	this->pos = pos;
	this->offset = offset;
	this->speed = speed / 30 + 5;
	this->objType = objType;
	Shot::init();
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
	if (objType == TYPE_PLAYER_SHOT)
	{
		Obj::init("image/Pshot.png", VECTOR2{ 48,32 }, VECTOR2{ 5,6 }, pos);
		AddAnim("Ž©•ª‚Ì’e", 0, 0, 29, 1, true);

		SetAnim("Ž©•ª‚Ì’e");
		return true;

	}
	if (objType == TYPE_ENEMY_SHOT)
	{
		Obj::init("image/Eshot.png", VECTOR2{ 200,30 }, VECTOR2{ 7,2 });
		AddAnim("“G‚Ì’e", 0, 0, 14, 1, true);
		SetAnim("“G‚Ì’e");
		//lpSoundMng.PlaySound(SOUND_METEO, DX_PLAYTYPE_BACK);
		
		return true;
	}
	return false;
}

OBJ_TYPE Shot::CheckObjType(void)
{
	return objType;
}

bool Shot::CheckDeath(void)
{
	return deathFlag;
}

void Shot::SetMove(const GameCtl & controller, weekListObj objList)
{
	if (objType == TYPE_PLAYER_SHOT)
	{
		
		pos.x += speed;

		if (pos.x > SCREEN_SIZE_X)
		{
			deathFlag = true;
		
		}

	}
	else if (objType == TYPE_ENEMY_SHOT)
	{
		pos.x -= speed;
		if (pos.x+256 <0)
		{
			deathFlag = true;
			lpSoundMng.StopSound(SOUND_METEO);
		}

		
	}else{}
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
