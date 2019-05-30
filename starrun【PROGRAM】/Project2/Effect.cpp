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
	effect_image = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	SetDrawScreen(effect_image);
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(100, 10, effect_image, false);
}

bool Effect::init()
{
	return false;
}
//
//void Effect::Draw()
//{
//}
