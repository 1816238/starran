#pragma once
#include "BaseScene.h"
#include "classObj.h"
class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller);
private:
	sharedListObj objList;
	virtual int Init(void);
	bool ResultDraw(void);
	int score;
	int time;
};

