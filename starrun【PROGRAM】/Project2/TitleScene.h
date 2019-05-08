#pragma once
#include "BaseScene.h"
#include "Obj.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller);
private:
	sharedListObj objList;
	virtual int Init(void);
	bool TitleDraw(void);
	void TitleMove(void);
	int cnt;
	VECTOR2 pos;
	VECTOR2 drawChip;
	bool ClickCheck;
	bool ClickCheckOld;
	VECTOR2 start;
};

