#include <DxLib.h>
#include "ImageMng.h"
#include "SoundMng.h"
#include "EnemyAct.h"
#include "GameScene.h"
#include "Meteo.h"

Meteo::Meteo()
{
}

Meteo::~Meteo()
{
}

bool Meteo::initAnim(void)
{
	return false;
}

bool Meteo::init(void)
{
	return false;
}

void Meteo::SetMove(const GameCtl & controller, weekListObj objList)
{
	if (!lpEnemyAct.GetmeteoriteFlag())
	{
		pos.x = 0;		//覐΂�pos.x
		pos.y = 0;
	}

	switch (lpEnemyAct.SetAngle())
	{
	case 3:
		enemy_speed = VECTOR2(SHOT_SPEED, 7);
		break;
	case 4:
		enemy_speed = VECTOR2(SHOT_SPEED, 5);
		break;
	case 5:
		enemy_speed = VECTOR2(SHOT_SPEED, 4);
		break;
	case 6:
		enemy_speed = VECTOR2(SHOT_SPEED, 3);
		break;
	case 7:
		enemy_speed = VECTOR2(SHOT_SPEED + 2, 3);
		break;
	case 8:
		enemy_speed = VECTOR2(SHOT_SPEED, 2);
		break;
	default:
		break;
	}
}

void Meteo::Draw(void)
{

	if (lpEnemyAct.GetmeteoriteFlag())
	{
		if (!lpSoundMng.CheckSound(SOUND_METEO))
		{
			lpSoundMng.PlaySound(SOUND_METEO, DX_PLAYTYPE_LOOP);
		}
		pos.x += enemy_speed.x;
		pos.y += enemy_speed.y;
		DrawRotaGraph(GIMMICK_POP_X + CHIP_SIZE * lpEnemyAct.SetPos() - pos.x, pos.y, 1, -(PI / lpEnemyAct.SetAngle()), IMAGE_ID("image/tama.png")[0], true, true);

	}

}
