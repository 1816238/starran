#include "DxLib.h"
#include "BaseScene.h"
#include "MAP_ID.h"
#include "MapControl.h"
#include "GameController.h"
#include "EditCursor.h"

#define EDIT_KEY_EGT_DEF_RNG ( 30 )
#define MIN_KEY_RNG ( 2 )


EditCursor::EditCursor()
{
	id = MAP_ID::WALL1;
}

EditCursor::EditCursor(VECTOR2 drawOffset) :Obj(drawOffset)
{
	id = MAP_ID::WALL1;
}

EditCursor::~EditCursor()
{

}

void EditCursor::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	Obj::Draw( static_cast<int>(id) );
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(static_cast<int>(animCnt% 512) - 256));
	Obj::Draw(0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	animCnt+=5;
}

VECTOR2 EditCursor::GetChipPos()
{
	return ChipPos;
}

void EditCursor::SetMove_Mouse()
{
		//’[‚Ü‚Ås‚Á‚½‚çŽ~‚ß‚é
	if (ChipPos.x > 0)
	{
		ChipPos.x = 0;
	}
	else if (ChipPos.x < -(SCREEN_SIZE_X * 3))
	{
		ChipPos.x = -(SCREEN_SIZE_X * 3);
	}
	else
	{
		ChipPos.x += GetMouseWheelRotVol() * 15;
	}
}

bool EditCursor::CheackObjType(OBJ_TYPE Obj_type)
{
	return (Obj_type == OBJ_TYPE::EDIT_CUR);
}

void EditCursor::SetMove(const GameController &controller, weekListObj objList)
{
	auto cnt = controller.GetCtl(KEY_TYPE::NOW);
	auto cntOld = controller.GetCtl(KEY_TYPE::OLD);
		VECTOR2 tmpPos = pos ;

	auto Mover = [](int keyState, int &Pos /*x, y‚Ç‚¿‚ç‚à“ü‚é*/, int addNum /*‰ÁŽZ’l*/)
	{
		if (keyState)
		{
			Pos += addNum;
		}
	};

	if (pos.x > 0)
	{	
		Mover( cnt[KEY_INPUT_NUMPAD4],	 tmpPos.x,-divSize.x);
		Mover( cnt[KEY_INPUT_LEFT],		 tmpPos.x,-divSize.x);
	}
	if (pos.x + divSize.x < SCREEN_SIZE_X)
	{
		Mover( cnt[KEY_INPUT_NUMPAD6],	  tmpPos.x,divSize.x);
		Mover( cnt[KEY_INPUT_RIGHT],	  tmpPos.x,divSize.x);
	}
	if (pos.y > 0)
	{
		Mover( cnt[KEY_INPUT_NUMPAD8],	 tmpPos.y,-divSize.y);
		Mover( cnt[KEY_INPUT_UP],		 tmpPos.y,-divSize.y);
	}
	if (pos.y + divSize.y < SCREEN_SIZE_Y)
	{
		Mover( cnt[KEY_INPUT_NUMPAD2],  tmpPos.y, divSize.y );
		Mover( cnt[KEY_INPUT_DOWN],		tmpPos.y, divSize.y );
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

	SetID( cnt[KEY_INPUT_1], MAP_ID::BOMB );
	SetID( cnt[KEY_INPUT_2], MAP_ID::NON  );
	SetID( cnt[KEY_INPUT_3], MAP_ID::WALL1);
	SetID( cnt[KEY_INPUT_4], MAP_ID::WALL2);
	SetID( cnt[KEY_INPUT_5], MAP_ID::BLOCK);
	SetID( cnt[KEY_INPUT_6], MAP_ID::ITEM_FIRE );
	SetID( cnt[KEY_INPUT_7], MAP_ID::ITEM_BOMB );
	SetID( cnt[KEY_INPUT_8], MAP_ID::ITEM_CTL  );
	SetID( cnt[KEY_INPUT_9], MAP_ID::ITEM_SPEED);

	if (cnt[KEY_INPUT_LCONTROL] & (~cntOld[KEY_INPUT_LCONTROL]))
	{
		id = (MAP_ID)(static_cast<int>(id) + 1);
		if (id >= MAP_ID::MAX)
		{
			id = MAP_ID::BOMB;
		}
	}

	if(cnt[KEY_INPUT_SPACE] & (cntOld[KEY_INPUT_SPACE]))
	{
		lpMapControl.SetMapData(pos + ChipPos,id);
	}


}
