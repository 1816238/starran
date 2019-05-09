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
	AddAnim("���r��", 0, 0, 1, 1, true);
	AddAnim("������", 1, 0, 1, 1, true);
	AddAnim("�o�q��", 2, 0, 1, 1, true);
	AddAnim(" �I�� ", 3, 0, 1, 1, true);
	AddAnim("���q��", 0, 1, 1, 1, true);
	AddAnim("������", 1, 1, 1, 1, true);
	AddAnim("�V����", 2, 1, 1, 1, true);
	AddAnim(" 嶍� ", 3, 1, 1, 1, true);
	AddAnim("�ˎ��", 0, 2, 1, 1, true);
	AddAnim("�R�r��", 1, 2, 1, 1, true);
	AddAnim("���r��", 2, 2, 1, 1, true);
	AddAnim(" ���� ", 3, 2, 1, 1, true);
	AddAnim(" �� ", 0, 3, 1, 1, true);	//BOSS�����Ȃ���
	return true;
}

void Enemy::SetMove(const GameCtl & controller, weekListObj objList)
{
	switch (enemyType)
	{
	case ARIES:
		SetAnim("���r��");
		break;
	case TAURUS:
		SetAnim("������");
		break;
	case GEMINI:
		SetAnim("�o�q��");
		break;
	case CANCER:
		SetAnim(" �I�� ");
		break;
	case LEO:
		SetAnim("���q��");
		break;
	case VIRGO:
		SetAnim("������");
		break;
	case LIBRA:
		SetAnim("�V����");
		break;
	case SCORPIO:
		SetAnim(" 嶍� ");
		break;
	case SAGITTARIUS:
		SetAnim("�ˎ��");
		break;
	case CAPRICORN:
		SetAnim("�R�r��");
		break;
	case AQUARIUS:
		SetAnim("���r��");
		break;
	case PISCES:
		SetAnim(" ���� ");
	case NON:
		SetAnim(" �� ");
		break;
	default:
		break;
	}
}

void Enemy::Draw(void)
{
	DrawRectGraph(SCREEN_SIZE_X - SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 4, 0, 0, 250, 250, IMAGE_ID("image/constellation.png")[0], true, false);
}
