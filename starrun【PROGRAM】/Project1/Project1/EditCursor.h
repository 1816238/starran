#pragma once
#include <array>
#include "Obj.h"
#include "MapControl.h"

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

#define lpEditCursor EditCursor::GetInstance();

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
	void SetMove_Mouse();

private:
	bool CheackObjType(OBJ_TYPE Obj_type);

	void SetMove(const GameController &controller, weekListObj objList);
	MAP_ID id;							//map画像のID

	int KeyGetRng;						//ｷｰを取得するフレーム数
	int inputFram;						//ｷｰを押していたフレーム数
	MAP_EDIT_KEY_ARRAY edit_Key;
	 VECTOR2 ChipPos;

};

