#include "DxLib.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "MapControl.h"
#include "Enemy.h"

Enemy::Enemy()
{
	init("image/constellation.png", VECTOR2(250, 250), VECTOR2(4, 4));
	enemyType = ARIES;
	initAnim();
}


Enemy::~Enemy()
{
}

bool Enemy::initAnim(void)
{
	AddAnim("‰²—rÀ", 0, 0, 1, 1, true);
	AddAnim("‰²‹À", 1, 0, 1, 1, true);
	AddAnim("‘oqÀ", 2, 0, 1, 1, true);
	AddAnim(" ŠIÀ ", 3, 0, 1, 1, true);
	AddAnim("‚qÀ", 0, 1, 1, 1, true);
	AddAnim("‰³—À", 1, 1, 1, 1, true);
	AddAnim("“V”‰À", 2, 1, 1, 1, true);
	AddAnim(" å¶À ", 3, 1, 1, 1, true);
	AddAnim("ËèÀ", 0, 2, 1, 1, true);
	AddAnim("R—rÀ", 1, 2, 1, 1, true);
	AddAnim("…•rÀ", 2, 2, 1, 1, true);
	AddAnim(" ‹›À ", 3, 2, 1, 1, true);
	AddAnim(" ‹ó”’ ", 0, 3, 1, 1, true);	//BOSS‚ª‚¢‚È‚¢
	return true;
}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
}

void Enemy::Draw(void)
{

	switch (enemyType)
	{
	case ARIES:
		SetAnim("‰²—rÀ");
		break;
	case TAURUS:
		SetAnim("‰²‹À");
		break;
	case GEMINI:		
		SetAnim("‘oqÀ");
		break;
	case CANCER:
		SetAnim(" ŠIÀ ");
		break;
	case LEO:
		SetAnim("‚qÀ");
		break;
	case VIRGO:
		SetAnim("‰³—À");
		break;
	case LIBRA:
		SetAnim("“V”‰À");
		break;
	case SCORPIO:
		SetAnim(" å¶À ");
		break;
	case SAGITTARIUS:
		SetAnim("ËèÀ");
		break;
	case CAPRICORN:
		SetAnim("R—rÀ");
		break;
	case AQUARIUS:
		SetAnim("…•rÀ");
		break;
	case PISCES:
		SetAnim(" ‹›À ");
	case NON:
		SetAnim(" ‹ó”’ ");
		break;
	default:
		break;
	}
}
