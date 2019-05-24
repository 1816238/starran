#pragma once
#include <list>
#include"Obj.h"
#include "BaseScene.h"
#include "classObj.h"

#define lpGameScene GameScene::GetInstance()
class Enemy;
class Player;

typedef struct HIT {
	VECTOR2 pos;
	uniqueObjList::iterator itr;
};

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
	 std::unique_ptr<Enemy> enemy;
	 std::unique_ptr<Player> PLAYER;
	// std::unique_ptr<Player> player;
	 ListObj_itr player;
	int SeasonSwitchFlag;
	void SeasonSwitch(void);
	list<HIT>pShotObj;
	list<HIT>::iterator pShot_itr;
	HIT playerPos;
};

