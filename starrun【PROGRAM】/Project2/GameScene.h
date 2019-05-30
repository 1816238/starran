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
	int ObjNo;
	bool deathFlag;
	bool damageFlag;
};

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller);
private:
	bool circleHit(VECTOR2 CePos, int CeRad, VECTOR2 SquPos, VECTOR2 SquRange);//�~�̒��S,�~�̔��a,�l�p�̍�����W,�l�p�͈̔�
	bool circleHit(VECTOR2 CePos, int CeRad, VECTOR2 CePos2, int CeRad2);
	sharedListObj objList;
	virtual int Init(void);
	bool GameDraw(void);
	 bool DeathPlayerFlag;

	// std::unique_ptr<Player> player;
	 ListObj_itr player;
	int SeasonSwitchFlag;
	void SeasonSwitch(void);
	list<HIT>BitObj;
	list<HIT>::iterator Bit_itr;
	HIT playerPos;
	int effect_image;
};

