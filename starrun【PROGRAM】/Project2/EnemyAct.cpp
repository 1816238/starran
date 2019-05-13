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
	switch (ATCnt % 50)
	{
	case 0:
		shotFlag = true;
		ShotCtl(pos);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
		break;
	default:
		break;
	}
}

const bool EnemyAct::GetshotFlag()
{
	return shotFlag;
}

void EnemyAct::ShotCtl(VECTOR2 pos)
{
	if (shotFlag == true && (SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x) < -118  )
	{
		shotFlag = false;
	}
}
