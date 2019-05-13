#include "DxLib.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "MapControl.h"
#include "classObj.h"
#include "EnemyAct.h"
#include "Enemy.h"

Enemy::Enemy(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	init("image/constellation.png", VECTOR2(250, 250), VECTOR2(4, 4));
	enemyType = ARIES;
	shotFlag = false;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
	lpEnemyAct.SelectAct(pos);
	if (!lpEnemyAct.GetshotFlag())
	{
		pos.x = 0;
	}
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
	if (lpEnemyAct.GetshotFlag())
	{
		DrawRotaGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x++, SCREEN_SIZE_Y / 4 - SCREEN_SIZE_Y / 6, 0.25f, 0, IMAGE_ID("image/tama.png")[0], true, true);
	}

	DrawFormatString(0, 175, 0xffff00, "�e��Flag...%d", lpEnemyAct.GetshotFlag());
	DrawFormatString(0, 200, 0xffff00, "�e�̍��W...%d", SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos.x);
	Draw(EnemyType());
}
