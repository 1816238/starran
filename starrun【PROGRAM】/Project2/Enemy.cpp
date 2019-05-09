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
	AddAnim("â≤órç¿", 0, 0, 1, 1, true);
	AddAnim("â≤ãçç¿", 1, 0, 1, 1, true);
	AddAnim("ëoéqç¿", 2, 0, 1, 1, true);
	AddAnim(" äIç¿ ", 3, 0, 1, 1, true);
	AddAnim("éÇéqç¿", 0, 1, 1, 1, true);
	AddAnim("â≥èóç¿", 1, 1, 1, 1, true);
	AddAnim("ìVîâç¿", 2, 1, 1, 1, true);
	AddAnim(" Â∂ç¿ ", 3, 1, 1, 1, true);
	AddAnim("éÀéËç¿", 0, 2, 1, 1, true);
	AddAnim("éRórç¿", 1, 2, 1, 1, true);
	AddAnim("êÖïrç¿", 2, 2, 1, 1, true);
	AddAnim(" ãõç¿ ", 3, 2, 1, 1, true);
	AddAnim(" ãÛîí ", 0, 3, 1, 1, true);	//BOSSÇ™Ç¢Ç»Ç¢éû
	return true;
}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
	switch (enemyType)
	{
	case ARIES:
		SetAnim("â≤órç¿");
		break;
	case TAURUS:
		SetAnim("â≤ãçç¿");
		break;
	case GEMINI:
		SetAnim("ëoéqç¿");
		break;
	case CANCER:
		SetAnim(" äIç¿ ");
		break;
	case LEO:
		SetAnim("éÇéqç¿");
		break;
	case VIRGO:
		SetAnim("â≥èóç¿");
		break;
	case LIBRA:
		SetAnim("ìVîâç¿");
		break;
	case SCORPIO:
		SetAnim(" Â∂ç¿ ");
		break;
	case SAGITTARIUS:
		SetAnim("éÀéËç¿");
		break;
	case CAPRICORN:
		SetAnim("éRórç¿");
		break;
	case AQUARIUS:
		SetAnim("êÖïrç¿");
		break;
	case PISCES:
		SetAnim(" ãõç¿ ");
	case NON:
		SetAnim(" ãÛîí ");
		break;
	default:
		break;
	}
}

void Enemy::Draw(void)
{
	DrawRectGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, 0, 0, 250, 250, IMAGE_ID("image/constellation.png")[0], true, false);
}
