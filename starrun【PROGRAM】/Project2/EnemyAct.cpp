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

void EnemyAct::SelectAct(VECTOR2 pos,VECTOR2 pos2)
{
	auto ATCnt = SEASONE_LIM - Time(Main);
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
	ShotCtl(pos , pos2);
	MeteoCtl(pos , pos2);
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
		
		switch ((rand() % 8) +1)
		{
		case 3:
			randAngle = 3;
			break;
		case 4:
			randAngle = 4;
			break;
		case 5: 
			randAngle = 5;
			break;
		case 6:
			randAngle = 6;
			break;
		case 7:
			randAngle = 7;
			break;
		case 8:
			randAngle = 8;
			break;
		default:
			break;
		}
	}
	return randAngle;
}

void EnemyAct::ShotCtl(VECTOR2 pos,VECTOR2 pos2)
{
	if (shotFlag == true && SCREEN_SIZE_X - SCREEN_SIZE_X / 4 -pos.x <  - 118  )
	{
		shotFlag = false;
	}
}

void EnemyAct::MeteoCtl(VECTOR2 pos, VECTOR2 pos2)
{
	if (meteoriteFlag == true && pos.y > SCREEN_SIZE_Y + 235 
		|| SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos2.x < -460)
	{
		meteoriteFlag = false;
	}
}
