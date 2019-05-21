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

void EnemyAct::SelectAct(VECTOR2 pos,VECTOR2 pos2,int frequency , bool at_shot, bool at_meteorite,int at_wait,int waitcnt,int waitcnt2,int waitcnt3)
{
	auto ATCnt = SEASONE_LIM - Speed(Main);
	
	if ((ATCnt %frequency) == 1)
	{
		if (at_shot)
		{
			
			shotFlag = true;
			if (!shotFlag)
			{
				SetPos();
			}
		}

		if (at_meteorite)
		{
			meteoriteFlag = true;
			if (!meteoriteFlag)
			{
				SetPos();
				SetAngle();
			}
		}
	}

	if (AttackType[SHOT] && AttackType[METEORITE])
	{
		switch (ATCnt %frequency)
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
		default:
			break;
		}
	}
	
	ShotCtl(pos , pos2,waitcnt,waitcnt2,waitcnt3);
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

void EnemyAct::MeteoCtl(VECTOR2 pos, VECTOR2 pos2)
{
	if (meteoriteFlag == true && pos.y > SCREEN_SIZE_Y + 235 
		|| SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos2.x < -460)
	{
		lpSoundMng.StopSound(SOUND_METEO);
		meteoriteFlag = false;
	}
}
