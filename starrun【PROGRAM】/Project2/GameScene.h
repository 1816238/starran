#pragma once
#include <list>
#include"Obj.h"
#include "BaseScene.h"
#include "classObj.h"

#define lpGameScene GameScene::GetInstance()

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller);
	 bool SetDeathFlag(void);
private:
	sharedListObj objList;
	virtual int Init(void);
	bool GameDraw(void);
	 bool DeathPlayerFlag;
	 ListObj_itr obj;

};

