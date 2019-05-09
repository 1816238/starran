#pragma once
#include <array>
#include "Obj.h"
#include "classObj.h"
#include "MapControl.h"

enum ENEMY_TYPE
{
	ENEMY_MOB,
	ENEMY_BOSS,
	ENEMY_MAX
};

enum BOSS_ID
{
	ARIES,
	TAURUS,
	GEMINI,
	CANCER,
	LEO,
	VIRGO,
	LIBRA,
	SCORPIO,
	SAGITTARIUS,
	CAPRICORN,
	AQUARIUS,
	PISCES,
	NON,
	ENEMY_ID_MAX,

};

class Enemy :
	public Obj
{
public:
	Enemy();
	~Enemy();
	bool initAnim(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//Player‚ÌˆÚ“®
	void Draw(void);

	sharedListObj objList;
	int enemyType;
	bool shootFlag;
};

