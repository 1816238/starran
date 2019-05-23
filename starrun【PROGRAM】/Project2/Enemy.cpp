#include "DxLib.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "SoundMng.h"
#include "MapControl.h"
#include "classObj.h"
#include "SpeedMng.h"
#include "EnemyAct.h"
#include "Enemy.h"

Enemy::Enemy(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	Obj::init("image/constellation.png", VECTOR2(250, 250), VECTOR2(4, 4));
}

Enemy::Enemy()
{
	init();
}

Enemy::~Enemy()
{
}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
	lpEnemyAct.SelectAct(pos , meteoPos, frequency[enemyType], At_Type[enemyType][SHOT], At_Type[enemyType][METEORITE],at_wait,waitCnt[0],waitCnt[1],waitCnt[2]);
	if (!lpEnemyAct.GetshotFlag())
	{
		pos.x = 0;
	}
	
	if (!lpEnemyAct.GetmeteoriteFlag())
	{
		meteoPos.x = 0;
		pos.y = 0;
	}

	switch (lpEnemyAct.SetAngle())
	{
	case 3:
		speed = VECTOR2(SHOT_SPEED , 7);
		break;
	case 4:
		speed = VECTOR2(SHOT_SPEED , 5);
		break;
	case 5:
		speed = VECTOR2(SHOT_SPEED , 4);
		break;
	case 6:
		speed = VECTOR2(SHOT_SPEED , 3);
		break;
	case 7:
		speed = VECTOR2(SHOT_SPEED + 2, 3);
		break;
	case 8:
		speed = VECTOR2(SHOT_SPEED , 2);
		break;
	default:
		break;
	}
	HitCheck();
}


void Enemy::Draw(void)
{
	auto ATCnt = SEASONE_LIM - Speed(Main);


	auto Draw = [&](VECTOR2 divID)
	{
		DrawRectGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, divID.x * 250, divID.y * 250, 250, 250, IMAGE_ID("image/constellation.png")[0], true, false);
	};
	int Pos = (SCREEN_SIZE_X - 80)*(enemy_hp[enemyType] / max_hp[enemyType]);
	DrawBox(100, SCREEN_SIZE_Y - 64, Pos, SCREEN_SIZE_Y - 32, 0x00ffff, true);
	DrawBox(100, SCREEN_SIZE_Y - 64, SCREEN_SIZE_X - 80, SCREEN_SIZE_Y - 32, 0xff0000, false);
	DrawBox(99, SCREEN_SIZE_Y - 63, SCREEN_SIZE_X - 81, SCREEN_SIZE_Y - 33, 0xff0000, false);


	if (lpEnemyAct.GetshotFlag())
	{

		VECTOR2 tmpPos = VECTOR2(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, 0);
		if (!lpSoundMng.CheckSound(SOUND_METEO))
		{
			lpSoundMng.PlaySound(SOUND_METEO, DX_PLAYTYPE_LOOP);
		}

		pos.x += 2;

		auto DrawShot = [&](int num ,int h) {
			if (lpEnemyAct.GetAtDrawFlag(num))
			{
				DrawRotaGraph2((tmpPos.x + 2 * waitCnt[num]) - pos.x, SCREEN_SIZE_Y - CHIP_SIZE * h, 0, 0, 0.25f, 0, IMAGE_ID("image/tama.png")[0], true, true);
			}
			else
			{
				waitCnt[num]++;
			}
		};

		DrawShot(0, 5);
		DrawShot(1, 7);
		DrawShot(2, 9);
		
	}
	else
	{
		for (int num = 0; num < AT_DRAW_MAX; num++)
		{
			waitCnt[num] = 0;
		}
	}

	if (lpEnemyAct.GetmeteoriteFlag())
	{
		if (!lpSoundMng.CheckSound(SOUND_METEO))
		{
			lpSoundMng.PlaySound(SOUND_METEO, DX_PLAYTYPE_LOOP);
		}
		meteoPos.x += speed.x;
		pos.y += speed.y;
		DrawRotaGraph(GIMMICK_POP_X + CHIP_SIZE * lpEnemyAct.SetPos() - meteoPos.x, pos.y, 1, -(PI / lpEnemyAct.SetAngle()), IMAGE_ID("image/tama.png")[0], true, true);

	}

	//ƒfƒoƒbƒN—p====================================================================================================================
	DrawLine((SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, 0, (SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, SCREEN_SIZE_Y, 0xff0000);
	DrawFormatString(1100, 0, 0xffff00, "“G‚ÌŽí—Þ......%d", enemy_name[enemyType]);
	DrawFormatString(1100, 25, 0xffff00, "“G‚ÌÅ‘åHP....%d", max_hp[enemyType]);
	DrawFormatString(1100, 50, 0xffff00, "“G‚ÌŽc‚èHP....%d", enemy_hp[enemyType]);
	DrawFormatString(1100, 75, 0xffff00, "UŒ‚SHOT......%d", At_Type[enemyType][SHOT]);
	DrawFormatString(1100, 100, 0xffff00, "UŒ‚METEO.....%d", At_Type[enemyType][METEORITE]);
	DrawFormatString(1100, 125, 0xffff00, "“G‚ÌUŒ‚•p“x..%d", frequency[enemyType]);
	if (At_Type[enemyType][SHOT])
	{
		DrawFormatString(1100, 150, 0xffff00, "’e‚ÌFlag......%d", lpEnemyAct.GetshotFlag());
		DrawFormatString(1100, 175, 0xffff00, "’e‚ÌÀ•W......%d", SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x);

		for (int num = 0; num < AT_DRAW_MAX; num++)
		{
			DrawFormatString(1100, 200 + 25 * num, 0xffff00, "At_DrawFlag[%d]...%d", num, lpEnemyAct.GetAtDrawFlag(num));
		}
	}
	if (At_Type[enemyType][METEORITE])
	{
		DrawFormatString(1100, 300, 0xffff00, "è¦Î‚ÌFlag....%d", lpEnemyAct.GetmeteoriteFlag());
		DrawFormatString(1100, 325, 0xffff00, "è¦Î‚ÌÀ•W....%d", pos.y);
		DrawFormatString(1100, 350, 0xffff00, "è¦Î‚ÌŠp“x....%d", lpEnemyAct.SetAngle());
		for (int num = 0; num <= AT_DRAW_MAX; num++)
		{
		}
	}
	//==============================================================================================================================
	if (enemyType < ENEMY_ID_MAX)
	{
		Draw(boss_ID[enemyType]);
	}
}

//VECTOR2 Enemy::EnemyType(void)
//{
//	seasone[enemyType];
//}

void Enemy::HitCheck(void)
{
	if (CheckHitKey(KEY_INPUT_P)==1 && enemyType < ENEMY_ID_MAX - 1)
	{
		enemyType = static_cast<BOSS_ID>(enemyType + 1);
		bool enemyBossFlag = false;
	}
}

bool Enemy::init(void)
{
	boss_ID = { VECTOR2(3,0), VECTOR2(0,1), VECTOR2(1,1),
				VECTOR2(2,1), VECTOR2(3,1), VECTOR2(0,2),
				VECTOR2(0,0), VECTOR2(1,0), VECTOR2(2,0),
				VECTOR2(1,2), VECTOR2(2,2), VECTOR2(3,2),VECTOR2(3,0) };

	seasone = { SPRING ,SPRING ,SPRING,
				SUMMER ,SUMMER ,SUMMER,
				AUTUMN ,AUTUMN ,AUTUMN,
				WINTER ,WINTER ,WINTER };

	At_Type = { true,false,
				false,true,
				true,true,
				true,false,
				false,true,
				true,true,
				true,false,
				false,true,
				true,true,
				true,false,
				false,true,
				true,true,
				false,false};

	max_hp = { 100, 200, 250,
			   350, 500, 650,
			   800, 950,1050,
			  1250,1450,1650,0};

	enemy_hp = { 100, 200, 250,
				 350, 500, 650,
				 800, 950,1050,
				1250,1450,1650,0};

	frequency = { 20,20,20,
				  15,15,15,
				  10,10,10,
				   5, 5, 5,0};

	enemyType = CANCER;

	at_Cnt = 36;
	at_wait = 60;

	meteoPos = VECTOR2(0, 0);
	speed = VECTOR2(0, 0);
	for (int num = 0; num < AT_DRAW_MAX; num++)
	{
		At_DrawFlag[num] = false;
	}
	shotFlag = false;
	enemyBossFlag = true;
	return false;
}
