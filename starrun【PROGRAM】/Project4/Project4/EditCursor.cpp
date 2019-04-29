#include "DxLib.h"
#include "BaseScene.h"
#include "MapControl.h"
#include "GameCtl.h"
#include "EditCursor.h"

#define EDIT_KEY_EGT_DEF_RNG ( 30 )
#define MIN_KEY_RNG ( 2 )

EditCursor::EditCursor()
{
	id = MAP_ID_BLUE;
}

EditCursor::EditCursor(VECTOR2 drawOffset) :Obj(drawOffset)
{
	id = MAP_ID_BLUE;
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

VECTOR2 EditCursor::SetMove_Mouse()
{

	if (ChipPos.x < 0)
	{
		ChipPos.x = 0;
	}
	if (ChipPos.x > (SCREEN_SIZE_X * 3))
	{
		ChipPos.x = (SCREEN_SIZE_X * 3);
	}
	
	ChipPos.x -= (GetMouseWheelRotVol()%2) * 30;
	
	return VECTOR2(ChipPos);
}

void EditCursor::SetMove(const GameCtl &controller, weekListObj objList)
{
	auto cnt = controller.GetCtl(NOW);
	auto cntOld = controller.GetCtl(OLD);
	VECTOR2 tmpPos = pos;

	auto Mover = [](int keyState, int &pos /*x, yどちらも入る*/, int addNum /*加算値*/)
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



	if (cnt[KEY_INPUT_LCONTROL] & (~cntOld[KEY_INPUT_LCONTROL]))
	{
		id = (MAP_ID)(id + 1);
		if (id >= MAP_ID_MAX)
		{
			id = MAP_ID_BLUE;
		}
	}

	if (cnt[KEY_INPUT_SPACE] & (cntOld[KEY_INPUT_SPACE]))
	{
		lpMapControl.SetMapData(pos, id);
	}

	if (cnt[KEY_INPUT_RIGHT] & (~cntOld[KEY_INPUT_RIGHT]))
	{
		ChipPos.x += 600;
	}
}
