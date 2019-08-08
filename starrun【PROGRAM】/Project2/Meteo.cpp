#include <math.h>
#include <DxLib.h>
#include "ImageMng.h"
#include "SoundMng.h"
#include "EnemyAct.h"
#include "Enemy.h"
#include "GameScene.h"
#include "Meteo.h"

Meteo::Meteo(VECTOR2 pos, VECTOR2 offset)
{
	this->pos = pos;
	this->offset = offset;
	this->objType = TYPE_METEO;
	Meteo::init();
	OutputDebugString("pop\n");

}

Meteo::~Meteo()
{
}

bool Meteo::initAnim(void)
{
	
	return true;
}

bool Meteo::init(void)
{
		switch (15 * lpEnemyAct.SetAngle())
		{
		case 15:
			Obj::init("image/metorite15.png", VECTOR2{ 590,300 }, VECTOR2{ 4,5 });
			AddAnim("隕石：15度", 0, 0, 20, 1, true);
			SetAnim("隕石：15度");
			obj_no = static_cast<int>(ANGLE_15);
			return false;
			break;
		case 30:
			Obj::init("image/metorite30.png", VECTOR2{ 560,390 }, VECTOR2{ 4,5 });
			AddAnim("隕石：30度", 0, 0, 20, 1, true);
			SetAnim("隕石：30度");
			obj_no = static_cast<int>(ANGLE_30);

			return false;
			break;
		case 45:
			Obj::init("image/metorite45.png", VECTOR2{ 470,480 }, VECTOR2{ 4,5 });
			AddAnim("隕石：45度", 0, 0, 20, 1, true);
			SetAnim("隕石：45度");
			obj_no = static_cast<int>(ANGLE_45);

			return false;
			break;
		case 60:
			Obj::init("image/metorite60.png", VECTOR2{ 390,540 }, VECTOR2{ 4,5 });
			AddAnim("隕石：60度", 0, 0, 20, 1, true);
			SetAnim("隕石：60度");
			obj_no = static_cast<int>(ANGLE_60);

			return false;
			break;
		default:
			break;
		}
	return false;
}

void Meteo::SetMove(const GameCtl & controller, weekListObj objList)
{
	if (EndFlag && !lpSoundMng.CheckSound(SOUND_METEO))
	{
		lpSoundMng.PlaySound(SOUND_METEO, DX_PLAYTYPE_LOOP);
	}
	if (pos.y > SCREEN_SIZE_Y + 235
		|| SCREEN_SIZE_X - SCREEN_SIZE_X / 4 - pos2.x < -460)
	{
		lpSoundMng.StopSound(SOUND_METEO);
		lpEnemyAct.SetMeteoFlag(false);

		EndFlag = true;
	}

	switch (lpEnemyAct.SetAngle())
	{
	case 1:
		enemy_speed = VECTOR2(SHOT_SPEED, 2);
		break;
	case 2:
		enemy_speed = VECTOR2(SHOT_SPEED, 4);
		break;
	case 3:
		enemy_speed = VECTOR2(SHOT_SPEED, SHOT_SPEED);
		break;
	case 4:
		enemy_speed = VECTOR2(3,SHOT_SPEED);
		break;
	default:
		break;
	}
	pos += enemy_speed;
	SetPos(pos);
}

//void Meteo::Draw(void)
//{
//
//	if (lpEnemyAct.GetmeteoriteFlag())
//	{
//		if (!lpSoundMng.CheckSound(SOUND_METEO))
//		{
//			lpSoundMng.PlaySound(SOUND_METEO, DX_PLAYTYPE_LOOP);
//		}
//		pos.x += enemy_speed.x;
//		pos.y += enemy_speed.y;
//		DrawRotaGraph(pos.x, pos.y, 1, -(PI / lpEnemyAct.SetAngle()), IMAGE_ID("image/metorite.png")[0], true, true);
//	}
//
//}
