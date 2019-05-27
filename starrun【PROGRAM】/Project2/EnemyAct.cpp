#include "DxLib.h"
#include "BaseScene.h"
#include "SpeedMng.h"
#include "SoundMng.h"
#include "ImageMng.h"
#include "Enemy.h"
#include "EnemyAct.h"

EnemyAct::EnemyAct()
{
}

EnemyAct::~EnemyAct()
{
}

void EnemyAct::SelectAct(VECTOR2 pos,VECTOR2 pos2,int frequency , BOSS_ID enemy_name,int at_wait,int waitcnt,int waitcnt2,int waitcnt3)
{
	auto ATCnt = SEASONE_LIM - Speed(Main);

		switch (ATCnt %frequency)
		{
		case 1:
			if (At_Type[enemy_name][SHOT])
			{
				shotFlag = true;
				if (!shotFlag)
				{
					SetPos();
				}
			}
			break;
		case 2:
			if (At_Type[enemy_name][METEORITE])
			{
				meteoriteFlag = true;
				if (!meteoriteFlag)
				{

					SetPos();
					SetAngle();
				}
			}
			break;
		default:
			break;
		}

	//SetMeteoFlag(false);
	ShotCtl(pos , pos2,waitcnt,waitcnt2,waitcnt3);
}

const bool EnemyAct::GetshotFlag()
{
	return shotFlag;
}

const bool EnemyAct::GetmeteoriteFlag()
{
	return meteoriteFlag;
}

const bool EnemyAct::GetAtDrawFlag(int num)
{
	return At_DrawFlag[num];
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
	if (meteoriteFlag)
	{
		
		switch ((rand() % 6) +1)
		{
		case 3:
			randAngle = 1;
			break;
		case 4:
			randAngle = 2;
			break;
		case 5: 
			randAngle = 3;
			break;
		case 6:
			randAngle = 4;
			break;
		default:
			break;
		}
	}
	return randAngle;
}

void EnemyAct::SetShotFlag(bool flag)
{
	shotFlag = flag;
}

void EnemyAct::SetMeteoFlag(bool flag)
{
	meteoriteFlag = flag;
}

void EnemyAct::ShotCtl(VECTOR2 pos,VECTOR2 pos2, int waitcnt, int waitcnt2, int waitcnt3)
{
	auto ATCnt = SEASONE_LIM - Speed(Main);


	if (shotFlag == true)
	{
		switch ((ATCnt / at_wait)% at_Cnt)
		{
		case 1:
			At_DrawFlag[0] = true;
			break;
		case 5:
			At_DrawFlag[1] = true;
			break;
		case 19:
			At_DrawFlag[2] = true;
			break;
		default:
			break;
		}
		if (waitcnt < waitcnt2 < waitcnt3)
		{
			max_waitCnt = waitcnt3;
		}
		else if (waitcnt < waitcnt3 < waitcnt2)
		{
			max_waitCnt = waitcnt2;

		}
		else if (waitcnt2 < waitcnt < waitcnt3)
		{
			max_waitCnt = waitcnt3;

		}
		else if (waitcnt2 < waitcnt3 < waitcnt)
		{
			max_waitCnt = waitcnt;

		}
		else if (waitcnt3 < waitcnt2 < waitcnt)
		{
			max_waitCnt = waitcnt;

		}
		else if (waitcnt3 < waitcnt < waitcnt2)
		{
			max_waitCnt = waitcnt2;

		}
		else {}
		if (SCREEN_SIZE_X - SCREEN_SIZE_X / 4 + 2* max_waitCnt - pos.x < -118)
		{
			lpSoundMng.StopSound(SOUND_METEO);
			shotFlag = false;
		}
	}
	else
	{
		for (int num = 0; num < AT_DRAW_MAX; num++)
		{
			At_DrawFlag[num] = false;
		}
	}
}
