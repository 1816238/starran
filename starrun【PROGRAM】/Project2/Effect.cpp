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
	shake_flag = true;
	effect_image = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	SetDrawScreen(effect_image);
}

void Effect::Rotation(void)
{
	escape_flag = true;
	effect_image = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	SetDrawScreen(effect_image);
}

bool Effect::init()
{
	shake_flag = false;
	escape_flag = false;
	return false;
}

void Effect::Draw()
{
	SetDrawScreen(DX_SCREEN_BACK);
	if (shake_flag)
	{
		if (shake_cnt < 5)
		{
			DrawGraph((shake_cnt % 3-1) * (-32), (shake_cnt % 3 - 1) * (-64), effect_image, false);
		}
		else
		{
			shake_cnt = 0;
			effect_flag = false;
			shake_flag = false;
		}
		shake_cnt++;
	}
	if (escape_flag)
	{
		for (float num = 0; num <= 1; num += 0.1f)
		{
			DrawRotaGraph2(0, 0, CIRCLE_RANGE + 43 / 2, 45 / 2, 1.0f - num, PI / 2.0f*num, escape_flag,false,false);
		}
	}
}

const void Effect::SetEffectFlag(bool flag)
{
	effect_flag = flag;
}

const bool Effect::GetEffectFlag()
{
	return effect_flag;
}
