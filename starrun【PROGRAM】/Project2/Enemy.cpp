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
	lpEnemyAct.SelectAct(pos , meteoPos, frequency, AttackType[SHOT], AttackType[METEORITE],at_wait,waitCnt[0],waitCnt[1],waitCnt[2]);
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
		speed = VECTOR2(4, 4);
		break;
	case 4:
		speed = VECTOR2(5, 4);
		break;
	case 5:
		speed = VECTOR2(SPEED, 4);
		break;
	case 6:
		speed = VECTOR2(SPEED, 4);
		break;
	case 7:
		speed = VECTOR2(SPEED, 3);
		break;
	case 8:
		speed = VECTOR2(SPEED, 3);
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
	int Pos = (SCREEN_SIZE_X - 80)*(enemyHp / maxHp);
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

	//ÉfÉoÉbÉNóp====================================================================================================================
	DrawLine((SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, 0, (SCREEN_SIZE_X - SCREEN_SIZE_X / 4) - pos.x, SCREEN_SIZE_Y, 0xff0000);
	DrawFormatString(1100, 0, 0xffff00, "ìGÇÃéÌóﬁ......%d", static_cast<int>(enemyBossFlag));
	DrawFormatString(1100, 25, 0xffff00, "ìGÇÃç≈ëÂHP....%d", maxHp);
	DrawFormatString(1100, 50, 0xffff00, "ìGÇÃécÇËHP....%d", enemyHp);
	DrawFormatString(1100, 75, 0xffff00, "çUåÇSHOT......%d", AttackType[SHOT]);
	DrawFormatString(1100, 100, 0xffff00, "çUåÇMETEO.....%d", AttackType[METEORITE]);
	DrawFormatString(1100, 125, 0xffff00, "ìGÇÃçUåÇïpìx..%d", frequency);
	if (AttackType[SHOT])
	{
		DrawFormatString(1100, 150, 0xffff00, "íeÇÃFlag......%d", lpEnemyAct.GetshotFlag());
		DrawFormatString(1100, 175, 0xffff00, "íeÇÃç¿ïW......%d", SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x);

		for (int num = 0; num < AT_DRAW_MAX; num++)
		{
			DrawFormatString(1100, 200 + 25 * num, 0xffff00, "At_DrawFlag[%d]...%d", num, lpEnemyAct.GetAtDrawFlag(num));
		}
	}
	if (AttackType[METEORITE])
	{
		DrawFormatString(1100, 300, 0xffff00, "Ë¶êŒÇÃFlag....%d", lpEnemyAct.GetmeteoriteFlag());
		DrawFormatString(1100, 325, 0xffff00, "Ë¶êŒÇÃç¿ïW....%d", pos.y);
		DrawFormatString(1100, 350, 0xffff00, "Ë¶êŒÇÃäpìx....%d", lpEnemyAct.SetAngle());
		for (int num = 0; num <= AT_DRAW_MAX; num++)
		{
		}
	}
	//==============================================================================================================================
	if (enemyType < ENEMY_ID_MAX)
	{
		Draw(EnemyType());
	}
}

VECTOR2 Enemy::EnemyType(void)
{
	switch (enemyType)
	{
		//ètÇÃêØç¿
	case CANCER:
		maxHp = 100;
		enemyHp = 100;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = false;
		frequency = 20;
		return VECTOR2(3, 0);
		break;
	case LEO:
		maxHp = 200;
		enemyHp = 200;
		AttackType[SHOT] = false;
		AttackType[METEORITE] = true;
		frequency = 20;
		return VECTOR2(0, 1);
		break;
	case VIRGO:
		maxHp = 250;
		enemyHp = 250;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = true;
		frequency = 20;
		return VECTOR2(1, 1);
		break;
		//âƒÇÃêØç¿
	case LIBRA:
		maxHp = 350;
		enemyHp = 350;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = false;
		frequency = 15;
		return VECTOR2(2, 1);
		break;
	case SCORPIO:
		maxHp = 500;
		enemyHp = 500;
		AttackType[SHOT] = false;
		AttackType[METEORITE] = true;
		frequency = 15;
		return VECTOR2(3, 1);
		break;
	case SAGITTARIUS:
		maxHp = 650;
		enemyHp = 650;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = true;
		frequency = 15;
		return VECTOR2(0, 2);
		break;
		//èHÇÃêØç¿
	case ARIES:
		maxHp = 800;
		enemyHp = 800;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = false;
		frequency = 10;
		return VECTOR2( 0, 0);
		break;
	case TAURUS:
		maxHp = 950;
		enemyHp = 950;
		AttackType[SHOT] = false;
		AttackType[METEORITE] = true;
		frequency = 10;
		return VECTOR2( 1, 0);
		break;
	case GEMINI:
		maxHp = 1050;
		enemyHp = 1050;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = true;
		frequency = 10;
		return VECTOR2( 2, 0);
		break;
		//ì~ÇÃêØç¿
	case CAPRICORN:
		maxHp = 1250;
		enemyHp = 1250;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = false;
		frequency = 5;
		return VECTOR2(1, 2);
		break;
	case AQUARIUS:
		maxHp = 1450;
		enemyHp = 1450;
		AttackType[SHOT] = false;
		AttackType[METEORITE] = true;
		frequency = 5;
		return VECTOR2(2, 2);
		break;
	case PISCES:
		maxHp = 1650;
		enemyHp = 1650;
		AttackType[SHOT] = true;
		AttackType[METEORITE] = true;
		frequency = 5;
		return VECTOR2(3, 2);
		break;
	default:
		break;
	}
}
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
	enemyType = PISCES;
	maxHp = ENEMY_DEF_HP;
	frequency = ENEMY_DEF_FREQUENCY;
	enemyHp = maxHp;
	at_Cnt = 36;
	at_wait = 60;

	meteoPos = VECTOR2(0, 0);
	speed = VECTOR2(0, 0);
	AttackType[SHOT] = false;
	AttackType[METEORITE] = false;
	for (int num = 0; num < AT_DRAW_MAX; num++)
	{
		At_DrawFlag[num] = false;
	}
	shotFlag = false;
	enemyBossFlag = true;
	return false;
}
