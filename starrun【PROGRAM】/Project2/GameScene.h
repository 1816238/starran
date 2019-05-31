#pragma once
#include <list>
#include <vector>
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
	int HP;
};

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller);
private:
	bool circleHit(VECTOR2 CePos, int CeRad, VECTOR2 SquPos, VECTOR2 SquRange);//â~ÇÃíÜêS,â~ÇÃîºåa,éläpÇÃç∂è„ç¿ïW,éläpÇÃîÕàÕ
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
	int attack;
	vector<VECTOR2> MeteoOffset;
	vector<int> MeteoRad;
	int timeFont;
};

