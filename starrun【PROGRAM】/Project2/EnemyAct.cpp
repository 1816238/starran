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

void EnemyAct::SelectAct(VECTOR2 pos,int frequency , BOSS_ID enemy_name,int at_wait,int waitcnt,int waitcnt2,int waitcnt3)
{
	auto ATCnt = SEASONE_LIM - Speed(Main);

		/*switch (ATCnt %frequency)
		{
		case 2:
			if (At_Type[enemy_name][METEORITE])
			{
				meteoriteFlag = true;
				if (!meteoriteFlag)
				{
					SetAngle();
				}
			}
			break;
		default:
			break;
		}*/

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

void EnemyAct::SetMeteoFlag(bool flag)
{
	meteoriteFlag = flag;
}

void EnemyAct::Setswitch(bool flag)
{
	switchflag = flag;
}

bool EnemyAct::Getswitch(void)
{
	return switchflag;
}
