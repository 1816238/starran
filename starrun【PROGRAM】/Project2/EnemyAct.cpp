#include "DxLib.h"
#include "BaseScene.h"
#include "SpeedMng.h"
#include "ImageMng.h"
#include "Enemy.h"
#include "EnemyAct.h"

EnemyAct::EnemyAct()
{
}

EnemyAct::~EnemyAct()
{
}

void EnemyAct::SelectAct(VECTOR2 pos)
{
	auto ATCnt = SEASONE_LIM - Time;
	switch (ATCnt %10)
	{
	case 1:
		shotFlag = true;
		if (!shotFlag)
		{
			SetPos();
		}
		break;
	case 2:
		meteoriteFlag = true;
		if (!meteoriteFlag)
		{
			
			SetPos();
			SetAngle();
		}
		break;
	case 3:
	case 4:
	case 5:
		break;
	default:
		break;
	}
	ShotCtl(pos);
	MeteoCtl(pos);
}

const bool EnemyAct::GetshotFlag()
{
	return shotFlag;
}

const bool EnemyAct::GetmeteoriteFlag()
{
	return meteoriteFlag;
}

const int EnemyAct::SetPos()
{
	if (!meteoriteFlag)
	{
		randPos = (rand() % 10);
	}
	return randPos;
}

const int EnemyAct::SetAngle()
{
	if (!meteoriteFlag)
	{
		randAngle = ((rand() % 8)+1);
	}
	return randAngle;
}

void EnemyAct::ShotCtl(VECTOR2 pos)
{
	if (shotFlag == true && SCREEN_SIZE_X - SCREEN_SIZE_X / 4 -pos.x <  - 118  )
	{
		shotFlag = false;
	}
}

void EnemyAct::MeteoCtl(VECTOR2 pos)
{
	if (meteoriteFlag == true && pos.y > SCREEN_SIZE_Y + 235)
	{
		meteoriteFlag = false;
	}
}
