#include "DxLib.h"
#include "MapControl.h"
#include "GameCtl.h"
#include "EditCursor.h"

#define EDIT_KEY_EGT_DEF_RNG ( 30 )
#define MIN_KEY_RNG ( 2 )

EditCursor::EditCursor()
{
	id = MAP_ID_WALL1;
}

EditCursor::EditCursor(VECTOR2 drawOffset) :Obj(drawOffset)
{
	id = MAP_ID_WALL1;
}

EditCursor::~EditCursor()
{

}

void EditCursor::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	Obj::Draw(id);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((int)(animCnt % 512) - 256));
	Obj::Draw(0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	animCnt += 5;
}

void EditCursor::SetMove(const GameCtl &controller, weekListObj objList)
{
	auto cnt = controller.GetCtl(NOW);
	auto cntOld = controller.GetCtl(OLD);
	VECTOR2 tmpPos = pos;

	auto Mover = [](int keyState, int &pos /*x, y‚Ç‚¿‚ç‚à“ü‚é*/, int addNum /*‰ÁŽZ’l*/)
	{
		if (keyState)
		{
			pos += addNum;
		}
	};

	if (pos.x > 0)
	{
		Mover(cnt[KEY_INPUT_NUMPAD4], tmpPos.x, -divSize.x);
		Mover(cnt[KEY_INPUT_LEFT], tmpPos.x, -divSize.x);
	}
	if (pos.x + divSize.x < 640)
	{
		Mover(cnt[KEY_INPUT_NUMPAD6], tmpPos.x, divSize.x);
		Mover(cnt[KEY_INPUT_RIGHT], tmpPos.x, divSize.x);
	}
	if (pos.y > 0)
	{
		Mover(cnt[KEY_INPUT_NUMPAD8], tmpPos.y, -divSize.y);
		Mover(cnt[KEY_INPUT_UP], tmpPos.y, -divSize.y);
	}
	if (pos.y + divSize.y < 480)
	{
		Mover(cnt[KEY_INPUT_NUMPAD2], tmpPos.y, divSize.y);
		Mover(cnt[KEY_INPUT_DOWN], tmpPos.y, divSize.y);
	}


	if (tmpPos != pos)
	{
		inputFram++;
		if (inputFram >= KeyGetRng)
		{
			pos = tmpPos;
			inputFram = 0;
			if (KeyGetRng > MIN_KEY_RNG)
			{
				KeyGetRng = KeyGetRng / 2;
			}
			else
			{
				KeyGetRng = MIN_KEY_RNG;
			}
		}
	}
	else
	{
		KeyGetRng = EDIT_KEY_EGT_DEF_RNG;
		inputFram = EDIT_KEY_EGT_DEF_RNG;
	}

	auto SetID = [&](int keyState, /*MAP_ID id,*/ MAP_ID SetID)
	{
		if (keyState)
		{
			id = SetID;
		}
	};

	SetID(cnt[KEY_INPUT_1], MAP_ID_BOMB);
	SetID(cnt[KEY_INPUT_2], MAP_ID_NON);
	SetID(cnt[KEY_INPUT_3], MAP_ID_WALL1);
	SetID(cnt[KEY_INPUT_4], MAP_ID_WALL2);
	SetID(cnt[KEY_INPUT_5], MAP_ID_BLOCK);
	SetID(cnt[KEY_INPUT_6], MAP_ID_ITEM_FIRE);
	SetID(cnt[KEY_INPUT_7], MAP_ID_ITEM_BOMB);
	SetID(cnt[KEY_INPUT_8], MAP_ID_ITEM_CTL);
	SetID(cnt[KEY_INPUT_9], MAP_ID_ITEM_SPEED);

	if (cnt[KEY_INPUT_LCONTROL] & (~cntOld[KEY_INPUT_LCONTROL]))
	{
		id = (MAP_ID)(id + 1);
		if (id >= MAP_ID_MAX)
		{
			id = MAP_ID_BOMB;
		}
	}

	if (cnt[KEY_INPUT_SPACE] & (cntOld[KEY_INPUT_SPACE]))
	{
		lpMapControl.SetMapData(pos, id);
	}

}
