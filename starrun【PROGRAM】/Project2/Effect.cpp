#include "DxLib.h"
#include "BaseScene.h"
#include "Enemy.h"
#include "EnemyBit.h"
#include "Effect.h"

Effect::Effect()
{
}


Effect::~Effect()
{
}

void Effect::Shake(void)
{
	effect_flag[SHAKE] = true;
	effect_image[SHAKE] = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	GetDrawScreenGraph(0,0,SCREEN_SIZE_X, SCREEN_SIZE_Y,effect_image[SHAKE]);
}

void Effect::Rotation(void)
{
	effect_flag[ROTATION] = true;
	//SetDrawArea(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	effect_image[ROTATION] = MakeScreen((CIRCLE_RANGE + 43 / 2)*2, (CIRCLE_RANGE + 45 / 2)*2);
	GetDrawScreenGraph(CENTER_POS_X - (CIRCLE_RANGE + 43 / 2), CENTER_POS_Y - (CIRCLE_RANGE + 45 / 2),
						CENTER_POS_X + (CIRCLE_RANGE + 43 / 2), CENTER_POS_Y + (CIRCLE_RANGE + 43 / 2), effect_image[ROTATION]);
}

bool Effect::init()
{
	effect_flag[SHAKE] = false;
	effect_flag[ROTATION] = false;
	return false;
}

void Effect::Draw(EFFECT_TYPE type)
{
	SetDrawScreen(DX_SCREEN_BACK);
			auto tmp_num = 0.0f;
	switch (type)
	{
	case SHAKE:
	if (effect_flag[SHAKE])
	{
		if (shake_cnt < 5)
		{
			DrawGraph((shake_cnt % 3-1) * (-32), (shake_cnt % 3 - 1) * (-64), effect_image[SHAKE], false);
		}
		else
		{
			shake_cnt = 0;
			effect_flag[SHAKE] = false;
		}
		shake_cnt++;
	}
		break;
	case ROTATION:
		if (effect_flag[ROTATION])
		{
			if (rotation_cnt <= 1.0f)
			{
				rotation_cnt += 0.1f;
			
			DrawRotaGraph(CENTER_POS_X, CENTER_POS_Y, 1.0f - rotation_cnt, PI / rotation_cnt, effect_image[ROTATION], false, false);
			}
			effect_flag[ROTATION] = false;
		}
		break;
	default:
		break;
	}
}

const void Effect::SetEffectFlag(EFFECT_TYPE type,bool flag)
{
	effect_flag[type] = flag;
}

const bool Effect::GetEffectFlag(EFFECT_TYPE type)
{
	return effect_flag[type];
}
