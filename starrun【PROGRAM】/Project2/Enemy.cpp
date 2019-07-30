#include <math.h>
#include "DxLib.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "SoundMng.h"
#include "MapControl.h"
#include "classObj.h"
#include "SpeedMng.h"
#include "Shot.h"
#include "Meteo.h"
#include "EnemyAct.h"
#include "EnemyBit.h"
#include "Enemy.h"

#define PI  3.1415926535897932384626433832795f
#define CIRCLE_PI ( PI*2 )
#define CENTER_POS_X ( SCREEN_SIZE_X - SCREEN_SIZE_X / 4 + 125) 
#define CENTER_POS_Y ( SCREEN_SIZE_Y / 4 + 125 )
#define CIRCLE_RANGE ( 250 -(60+43))

Enemy::Enemy(OBJ_TYPE objType)
{
	Obj::init("image/constellation.png", VECTOR2(250, 250), VECTOR2(4, 4));
	Obj::init("image/boss_body.png", VECTOR2(215, 45), VECTOR2(5, 1));
	this->objType = objType;
	init();
}

Enemy::Enemy()
{
	Obj::init("image/boss_body.png", VECTOR2(215, 45), VECTOR2(5, 1));

	init();
}

Enemy::~Enemy()
{

}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
	HitCheck();
	lpEnemyAct.SelectAct(pos, meteoPos, frequency[enemyType], enemyType, at_wait, waitCnt[0], waitCnt[1], waitCnt[2]);
	//ìGÇÃÀﬁØƒÇÃ≤›Ω¿›Ω
	if (enemyBossFlag)
	{
		if (lpSpeedMng.GetFlag(Main)&~lpSpeedMng.GetFlag(Sub))
		{
			BitObj.resize(enemy_bit_cnt[enemyType]);
			for (int bit_cnt = 0; bit_cnt < enemy_bit_cnt[enemyType]; bit_cnt++)
			{
				BitObj[bit_cnt] = AddObjList()(objList, std::make_unique<EnemyBit>(VECTOR2{ CIRCLE_RANGE + 43 / 2 , 45 / 2 }, VECTOR2{ 0,0 }, bit_cnt, max_hp[enemyType] / 4));
			}
			enemyBossFlag = false;
			Obj::switchFlag = false;
		}
	}
	
	//Ë¶êŒÇÃ≤›Ω¿›Ω
	if (lpEnemyAct.GetmeteoriteFlag())
	{
		if (meteo_waitCnt > 120)
		{
			AddObjList()(objList, std::make_unique<Meteo>(VECTOR2{ GIMMICK_POP_X + CHIP_SIZE * lpEnemyAct.SetPos(), -500 }, VECTOR2{ 0,0 }));
			lpEnemyAct.SetMeteoFlag(false);
			meteo_waitCnt = 0;
		}
		meteo_waitCnt++;
	}

	//ìGÇÃíeÇÃ≤›Ω¿›ΩãyÇ—î≠éÀÇ‹Ç≈ÇÃä«óù
	if (At_Type[enemyType][SHOT])
	{


		if (!shotFlag[0] || !shotFlag[1] || !shotFlag[2])
		{
			VECTOR2 tmpPos = VECTOR2(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y);
		/*
			if ( || (shot_waitCnt / at_wait) % at_wait == 8
			 || (shot_waitCnt / at_wait) % at_wait == 1 || (shot_waitCnt / at_wait) % at_wait == 9
			 || (shot_waitCnt / at_wait) % at_wait == 2 || (shot_waitCnt / at_wait) % at_wait == 10
			 || (shot_waitCnt / at_wait) % at_wait == 3 || (shot_waitCnt / at_wait) % at_wait == 11
			 || (shot_waitCnt / at_wait) % at_wait == 4 || (shot_waitCnt / at_wait) % at_wait == 12
			 || (shot_waitCnt / at_wait) % at_wait == 5 || (shot_waitCnt / at_wait) % at_wait == 13
			 || (shot_waitCnt / at_wait) % at_wait == 6 || (shot_waitCnt / at_wait) % at_wait == 14
			 || (shot_waitCnt / at_wait) % at_wait == 7 || (shot_waitCnt / at_wait) % at_wait == 15)
			{*/
				for (int num = 0; num < 16; num++)
				{
					(shot_waitCnt / at_wait) % at_wait == num;
				
				auto DrawShot = [&](int h) {
					AddObjList()(objList, std::make_unique<Shot>(VECTOR2{ tmpPos.x,tmpPos.y - h * CHIP_SIZE }, VECTOR2{ 0,0 }, TYPE_ENEMY_SHOT, 12));
				};

				auto Enemy_Shot = [&](int shot_num, int draw_num)
				{
					if (!shotFlag[shot_num])
					{
						DrawShot(draw_num);
						shotFlag[shot_num] = true;
					}
				};
				Enemy_Shot((enemy_shot_tbl[(shot_waitCnt / at_wait) % at_wait] >> 0x08) & 0xff,
							enemy_shot_tbl[(shot_waitCnt / at_wait) % at_wait] & 0xff);
			}
			shot_waitCnt++;
		}
		else
		{
			OutputDebugString("shot_waitCnt = 0 \n");

			for (int num = 0; num < AT_DRAW_MAX; num++)
			{
				shotFlag[num] = false;
			}
			shot_waitCnt = 0;
		}
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		HP = 0;
	}
	enemy_hp[enemyType] = static_cast<float>(HP);
	deathFlag = (enemy_hp[enemyType] <= 0 ? true : deathFlag);
}

VECTOR2 Enemy::GetCircleMove_pos(void)
{
	return VECTOR2(pos.x, pos.y);
}

void Enemy::Draw(void)
{
	auto ATCnt = SEASONE_LIM - Speed(Main);
	SetAnim("í èÌ");

	auto Draw = [&](VECTOR2 divID)
	{
		//DrawCircle(CENTER_POS_X, CENTER_POS_Y, CIRCLE_RANGE, 0xff0000, false);
		//DrawCircle(SCREEN_SIZE_X - SCREEN_SIZE_X / 4 + 125, SCREEN_SIZE_Y / 4 + 125, 4, 0xff0000, true);
		DrawRectGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, divID.x * 250, divID.y * 250, 250, 250, IMAGE_ID("image/constellation.png")[0], true, false);
	};
	int Pos = (SCREEN_SIZE_X - 80)*(enemy_hp[enemyType] / max_hp[enemyType]);
	if (lpSpeedMng.GetFlag(Main) && !lpSpeedMng.GetFlag(Sub))
	{
		//HPï\é¶
		if (enemy_hp[enemyType] > 0)
		{
			DrawBox(100, SCREEN_SIZE_Y - 64, Pos, SCREEN_SIZE_Y - 32, 0x00ffff, true);

		}
		
	
		DrawBox(100, SCREEN_SIZE_Y - 64, SCREEN_SIZE_X - 80, SCREEN_SIZE_Y - 32, 0xff0000, false);
		DrawBox(99, SCREEN_SIZE_Y - 63, SCREEN_SIZE_X - 81, SCREEN_SIZE_Y - 33, 0xff0000, false);
	}
	DrawRectGraph(CENTER_POS_X - 43 / 2 - CIRCLE_RANGE, CENTER_POS_Y - 45 / 2, 43, 0, 43, 45,
		IMAGE_ID("image/boss_body.png")[0], true, false);
	
	//ÉfÉoÉbÉNóp====================================================================================================================
	//DrawLine((SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, 0, (SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, SCREEN_SIZE_Y, 0xff0000);
	//DrawFormatString(1100, 0, 0xffff00, "ìGÇÃéÌóﬁ......%d", enemy_name[enemyType]);
	//DrawFormatString(1100, 25, 0xffff00, "ìGÇÃç≈ëÂHP....%d", max_hp[enemyType]);
	//DrawFormatString(1100, 50, 0xffff00, "ìGÇÃécÇËHP....%d", enemy_hp[enemyType]);
	//DrawFormatString(1100, 75, 0xffff00, "çUåÇSHOT......%d", At_Type[enemyType][SHOT]);
	//DrawFormatString(1100, 100, 0xffff00, "çUåÇMETEO.....%d", At_Type[enemyType][METEORITE]);
	//DrawFormatString(1100, 125, 0xffff00, "ìGÇÃçUåÇïpìx..%d", frequency[enemyType]);
	//DrawFormatString(0, 20 * 13, 0x000ff0, "enemy_shift_flag...%d", enemy_shift_flag);
	///*if (At_Type[enemyType][SHOT])
	//{*/
	//	DrawFormatString(1100, 175, 0xffff00, "íeÇÃç¿ïW......%d", SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x);

	//	for (int num = 0; num < AT_DRAW_MAX; num++)
	//	{
	//		DrawFormatString(1100, 150, 0xffff00, "íeÇÃFlag[%d]......%d",num ,shotFlag[num]);
	//	}
	////}
	//if (At_Type[enemyType][METEORITE])
	//{
	//	DrawFormatString(1100, 300, 0xffff00, "Ë¶êŒÇÃFlag....%d", lpEnemyAct.GetmeteoriteFlag());
	//	DrawFormatString(1100, 325, 0xffff00, "Ë¶êŒÇÃç¿ïW....%d", pos.y);
	//	DrawFormatString(1100, 350, 0xffff00, "Ë¶êŒÇÃäpìx....%d", lpEnemyAct.SetAngle());
	//	for (int num = 0; num <= AT_DRAW_MAX; num++)
	//	{
	//	}
	//}	//DrawLine((SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, 0, (SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, SCREEN_SIZE_Y, 0xff0000);
	//DrawFormatString(1100, 0, 0xffff00, "ìGÇÃéÌóﬁ......%d", enemy_name[enemyType]);
	//DrawFormatString(1100, 25, 0xffff00, "ìGÇÃç≈ëÂHP....%d", max_hp[enemyType]);
	//DrawFormatString(1100, 50, 0xffff00, "ìGÇÃécÇËHP....%d", enemy_hp[enemyType]);
	//DrawFormatString(1100, 75, 0xffff00, "çUåÇSHOT......%d", At_Type[enemyType][SHOT]);
	//DrawFormatString(1100, 100, 0xffff00, "çUåÇMETEO.....%d", At_Type[enemyType][METEORITE]);
	//DrawFormatString(1100, 125, 0xffff00, "ìGÇÃçUåÇïpìx..%d", frequency[enemyType]);
	//DrawFormatString(0, 20 * 13, 0x000ff0, "enemy_shift_flag...%d", enemy_shift_flag);
	///*if (At_Type[enemyType][SHOT])
	//{*/
	//	DrawFormatString(1100, 175, 0xffff00, "íeÇÃç¿ïW......%d", SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x);

	//	for (int num = 0; num < AT_DRAW_MAX; num++)
	//	{
	//		DrawFormatString(1100, 150, 0xffff00, "íeÇÃFlag[%d]......%d",num ,shotFlag[num]);
	//	}
	////}
	//if (At_Type[enemyType][METEORITE])
	//{
	//	DrawFormatString(1100, 300, 0xffff00, "Ë¶êŒÇÃFlag....%d", lpEnemyAct.GetmeteoriteFlag());
	//	DrawFormatString(1100, 325, 0xffff00, "Ë¶êŒÇÃç¿ïW....%d", pos.y);
	//	DrawFormatString(1100, 350, 0xffff00, "Ë¶êŒÇÃäpìx....%d", lpEnemyAct.SetAngle());
	//	for (int num = 0; num <= AT_DRAW_MAX; num++)
	//	{
	//	}
	//}
	//==============================================================================================================================
	if (enemyType < ENEMY_ID_MAX)
	{
		Draw(boss_ID[enemyType]);
	}
}

void Enemy::HitCheck(void)
{
	if (lpSpeedMng.GetFlag(Main) && !lpSpeedMng.GetFlag(Sub))
	{
		enemy_shift_flag = true;
	}
	if (deathFlag || (enemy_shift_flag &&!lpSpeedMng.GetFlag(Main) && lpSpeedMng.GetFlag(Sub)))
	{
		if (enemyType < PISCES)
		{
			enemyType = static_cast<BOSS_ID>(enemyType + 1);
			HP = max_hp[enemyType];		
			enemyBossFlag = true;
			enemy_shift_flag = false;
			deathFlag = false;
			Obj::switchFlag = true;
		}
		else
		{
			
			enemyType = CANCER;
			HP = max_hp[enemyType];
			enemyBossFlag = true;
			enemy_shift_flag = false;
			deathFlag = false;
			Obj::switchFlag = true;
		}
		lpEnemyAct.Setswitch(true);
	}
}

bool Enemy::init(void)
{


	AddAnim("í èÌ", 0, 0, 30, 1, true);

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
				false,false };

	max_hp = { 100, 200, 250,
			   350, 500, 650,
			   800, 950,1050,
			  1250,1450,1650,0 };

	enemy_hp = { 100, 200, 250,
				 350, 500, 650,
				 800, 950,1050,
				1250,1450,1650,0 };

	enemy_bit_cnt = { 4,4,4,
					  4,4,4,
					  4,4,4,
					  4,4,4 };

	frequency = { 20,20,20,
				  15,15,15,
				  10,10,10,
				   5, 5, 5,0 };
					 //0x00ff
	enemy_shot_tbl = { 0x0305,//0,3,
					   0x0009,//,1,7,
					   0x070f,//2,15,
					   0x0107,//3,9,
					   0x0406,//4,6,
					   0x050d,//5,2,
					   0x0610,//6,16,
					   0x0211 ,//7,4,
					   0x080c,//8,13,
					   0x0915,//9,7,
					   0x0a0a,//10,10,
					   0x0b14,//11,5,
					   0x0c08,//12,8,
					   0x0d0e,//13,14,
					   0x0e13,//14,19,
					   0x0f0b//15,12 */
						};
	enemyType = CANCER;

	at_Cnt = 30;
	at_wait = 30;

	meteoPos = VECTOR2(0, 0);
	speed = VECTOR2(0, 0);
	for (int num = 0; num < AT_DRAW_MAX; num++)
	{
		shotFlag[num] = false;
	}
	enemyBossFlag = true;
	Obj::HP = enemy_hp[CANCER];
	shotcnt = 0;
	enemy_shift_flag = false;
	deathFlag = false;
	return false;
}

OBJ_TYPE Enemy::CheckObjType(void)
{
	return objType;
}
