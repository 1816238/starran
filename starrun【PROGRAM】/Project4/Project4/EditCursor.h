#pragma once
#include <array>
#include "Obj.h"
#include "MapControl.h"

#define lpEditCursor EditCursor::GetInstance();

enum EDIT_KEY
{
	KEY_CTL,
	KEY_NUM_0,
	KEY_NUM_1,
	KEY_NUM_2,
	KEY_NUM_3,
	KEY_NUM_4,
	KEY_NUM_5,
	KEY_NUM_6,
	KEY_NUM_7,
	KEY_NUM_8,
	KEY_NUM_9,
	EDIT_KEY_MAX
};

using namespace std;
using MAP_EDIT_KEY_ARRAY = array<int, EDIT_KEY_MAX>;

class EditCursor :
	public Obj
{
public:
	static EditCursor &GetInstance(void)
	{
		static EditCursor s_Instance;
		return s_Instance;
	}
	EditCursor();
	EditCursor(VECTOR2 drawOffset);
	~EditCursor();
	void Draw(void);
	VECTOR2 GetChipPos();
	VECTOR2 SetCur(void);
	bool ifCurShift(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);
	MAP_ID id;
	int KeyGetRng;
	int inputFram;
	VECTOR2 ChipPos;
	MAP_EDIT_KEY_ARRAY edit_Key;
	int MouseCheck(int CheckInfo, bool OldCheck);
	VECTOR2 CurPos;
	int oldin;
	int input;
};

