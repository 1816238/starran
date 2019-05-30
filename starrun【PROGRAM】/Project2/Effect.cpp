#include "DxLib.h"
#include "BaseScene.h"
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

bool Effect::init()
{
	shake_flag = false;
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
}

const void Effect::SetEffectFlag(bool flag)
{
	effect_flag = flag;
}

const bool Effect::GetEffectFlag()
{
	return effect_flag;
}
