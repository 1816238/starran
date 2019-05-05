#include "DxLib.h"
#include "BaseScene.h"
#include "MapControl.h"
#include "GameCtl.h"
#include "EditCursor.h"

#define EDIT_KEY_EGT_DEF_RNG ( 30 )
#define MIN_KEY_RNG ( 2 )

EditCursor::EditCursor()
{
	id = MAP_ID_YELLOW;
	ChipPos = { 0,0 };
}

EditCursor::EditCursor(VECTOR2 drawOffset) :Obj(drawOffset)
{
	id = MAP_ID_YELLOW;
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
	//SetCur();
	//GetMousePoint(&CurPos.x, &CurPos.y);
	DrawFormatString(0, 20, 0xffffff, "id:%d", (MAP_ID)id);
	//DrawBox(CurPos.x-CHIP_SIZE/2, CurPos.y-CHIP_SIZE/2, CurPos.x + CHIP_SIZE/2, CurPos.y + CHIP_SIZE/2, 0xff00ff, true);
	
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
	ChipPos.x -= (GetMouseWheelRotVol() % 2) * 48;



	return ChipPos;
}

void EditCursor::SetMove(const GameCtl &controller, weekListObj objList)
{
	auto cnt = controller.GetCtl(NOW);
	auto cntOld = controller.GetCtl(OLD);
	VECTOR2 tmpPos = pos;
	//SetMove_Mouse();
	//if (ChipPos.x < 0)
	//{
	//	ChipPos.x = 0;
	//}
	//if (ChipPos.x > (SCREEN_SIZE_X * 3))
	//{
	//	ChipPos.x = (SCREEN_SIZE_X * 3);
	//}
	//ChipPos.x -= (GetMouseWheelRotVol() % 2) * 30;

	/*VECTOR2 tmp;
	tmp= SetCur();*/
	//GetMousePoint(&CurPos.x, &CurPos.y);
	SetCur();
	MouseCheck(MOUSE_INPUT_LEFT, false);//ãÛì«Ç›çûÇ›
	


	auto SetID = [&](int keyState, /*MAP_ID id,*/ MAP_ID SetID)
	{
		if (keyState)
		{
			id = SetID;
		}
	};

	if (GetMouseInput()&MOUSE_INPUT_LEFT)
	{
		lpMapControl.SetMapData(CurPos+ChipPos, id);
	}

	if (cnt[KEY_INPUT_LCONTROL] & (~cntOld[KEY_INPUT_LCONTROL]))
	{
		id = (MAP_ID)(id + 1);
		if (id >= MAP_ID_MAX)
		{
			id = MAP_ID_NON;
		}
	}

	if (cnt[KEY_INPUT_SPACE] & (cntOld[KEY_INPUT_SPACE]))
	{
		lpMapControl.SetMapData(CurPos + ChipPos, id);
	}

	
	//SetMove_Mouse();
}

int EditCursor::MouseCheck(int CheckInfo, bool OldCheck)//CheckInfoÇ…ímÇËÇΩÇ¢Œﬁ¿›ÇÃêîílÅAOldCheckÇ™trueÇ≈âﬂãéÇÃèÓïÒ
{
	if (!OldCheck)
	{
		input = GetMouseInput();
		return input&CheckInfo;
	}
	oldin = input;
	return oldin& CheckInfo;
}

VECTOR2 EditCursor::SetCur(void)
{
	GetMousePoint(&CurPos.x, &CurPos.y);
	return CurPos;
}

bool EditCursor::ifCurShift(void)
{
	return (ChipPos.x%32);
}
