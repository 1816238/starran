#pragma once
#include <list>
#include"Obj.h"
#include "BaseScene.h"
#include "classObj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller);
private:
	sharedListObj objList;
	virtual int Init(void);
	bool GameDraw(void);

};

