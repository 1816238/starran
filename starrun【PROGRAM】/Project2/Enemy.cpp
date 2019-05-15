#include "DxLib.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "MapControl.h"
#include "classObj.h"
#include "SpeedMng.h"
#include "EnemyAct.h"
#include "Enemy.h"

Enemy::Enemy(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	init("image/constellation.png", VECTOR2(250, 250), VECTOR2(4, 4));
	enemyType = ARIES;
	shotFlag = false;
	enemyBossFlag = true;
}

Enemy::Enemy()
{
	maxHp = ENEMY_DEF_HP;
	enemyHp = ENEMY_DEF_HP;
	meteoPos = VECTOR2(0, 0);
	speed = VECTOR2(0, 0);
}

Enemy::~Enemy()
{
}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
	lpEnemyAct.SelectAct(pos , meteoPos);
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
		speed = VECTOR2(1, 1);
		break;
	case 4:
		speed = VECTOR2(2, 1);
		break;
	case 5:
		speed = VECTOR2(SPEED, 1);
		break;
	case 6:
		speed = VECTOR2(SPEED, 1);
		break;
	case 7:
		speed = VECTOR2(SPEED, 1);
		break;
	case 8:
		speed = VECTOR2(SPEED, 1);
		break;
	default:
		break;
	}
	HitCheck();
}

VECTOR2 Enemy::EnemyType(void)
{
	switch (enemyType)
	{
	case ARIES:
		return VECTOR2( 0, 0);
		break;
	case TAURUS:
		return VECTOR2( 1, 0);
		break;
	case GEMINI:
		return VECTOR2( 2, 0);
		break;
	case CANCER:
		return VECTOR2( 3, 0);
		break;
	case LEO:
		return VECTOR2( 0, 1);
		break;
	case VIRGO:
		return VECTOR2( 1, 1);
		break;
	case LIBRA:
		return VECTOR2( 2, 1);
		break;
	case SCORPIO:
		return VECTOR2( 3, 1);
		break;
	case SAGITTARIUS:
		return VECTOR2( 0, 2);
		break;
	case CAPRICORN:
		return VECTOR2( 1, 2);
		break;
	case AQUARIUS:
		return VECTOR2( 2, 2);
		break;
	case PISCES:
		return VECTOR2(3, 2);

		break;
	default:
		break;
	}
}

void Enemy::Draw(void)
{
	auto Draw = [&](VECTOR2 divID)
	{
		DrawRectGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, divID.x * 250, divID.y * 250, 250, 250, IMAGE_ID("image/constellation.png")[0], true, false);
	};
	int Pos = (SCREEN_SIZE_X - 80)*(enemyHp / maxHp);
		DrawBox(100, SCREEN_SIZE_Y - 64, Pos, SCREEN_SIZE_Y - 32, 0x00ffff, true);
		DrawBox(100, SCREEN_SIZE_Y - 64, SCREEN_SIZE_X - 80, SCREEN_SIZE_Y - 32, 0xff0000, false);
		DrawBox( 99, SCREEN_SIZE_Y - 63, SCREEN_SIZE_X - 81, SCREEN_SIZE_Y - 33, 0xff0000, false);


	if (lpEnemyAct.GetshotFlag())
	{
		pos.x += 2;
		DrawRotaGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x, SCREEN_SIZE_Y - SCREEN_SIZE_Y / 5 - SCREEN_SIZE_Y /10, 0.25f, 0, IMAGE_ID("image/tama.png")[0], true, true);
	}

	if (lpEnemyAct.GetmeteoriteFlag())
	{
		meteoPos.x += speed.x;
		pos.y += speed.y;
		DrawRotaGraph(GIMMICK_POP_X + CHIP_SIZE * lpEnemyAct.SetPos() - meteoPos.x, pos.y, 1, -(PI/ lpEnemyAct.SetAngle()), IMAGE_ID("image/tama.png")[0], true, true);
	}

	DrawFormatString(1100, 0, 0xffff00, "ìGÇÃç≈ëÂHP...%d", enemyBossFlag);
	DrawFormatString(1100, 25, 0xffff00, "ìGÇÃç≈ëÂHP", maxHp);
	DrawFormatString(1100, 50, 0xffff00, "ìGÇÃécÇËHP", enemyHp);
	DrawFormatString(1100, 75, 0xffff00, "íeÇÃFlag...%d", lpEnemyAct.GetshotFlag());
	DrawFormatString(1100, 100, 0xffff00, "Ë¶êŒÇÃFlag...%d", lpEnemyAct.GetmeteoriteFlag());
	DrawFormatString(1100,125, 0xffff00, "íeÇÃç¿ïW...%d", SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x);
	DrawFormatString(1100,150, 0xffff00, "Ë¶êŒÇÃç¿ïW...%d", pos.y);
	DrawFormatString(1100,175, 0xffff00, "Ë¶êŒÇÃäpìx...%d", lpEnemyAct.SetAngle());
	
	Draw(EnemyType());
}

void Enemy::HitCheck(void)
{
	if (CheckHitKey(KEY_INPUT_P)==1)
	{
		enemyType = static_cast<BOSS_ID>(enemyType + 1);
		bool enemyBossFlag = false;
	}
}
