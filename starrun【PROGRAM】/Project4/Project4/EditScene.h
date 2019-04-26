#pragma once
#include <array>
#include <list>
#include "Obj.h"
#include "BaseScene.h"
#include "classObj.h"

enum TXT_DRAW
{
	TXT_PANEL_CHANGE,
	TXT_PANEL_SELECT,
	TXT_CURSOR_MOVE,
	TXT_MAP_LOAD,
	TXT_MAP_SAVE,
	TXT_MAX
};

using namespace std;
using EDIT_DRAW_TXT = array<string, TXT_MAX>;

class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	unique_Base UpDate(unique_Base own, const GameCtl &controller);
	virtual bool CheckEditMode(void)
	{
		return true;
	};
private:
	sharedListObj objList;
	virtual int Init(void);
	bool EditDraw(void);		//EditŠÖŒW‚Ì•`‰æ
	int Color;					//•¶š‚ÌFî•ñ‚ğ“ü‚ê‚é
	EDIT_DRAW_TXT string_Tbl;	//DrawString‚Åg—p‚·‚é•¶š—ñ‚ğŠi”[
};

