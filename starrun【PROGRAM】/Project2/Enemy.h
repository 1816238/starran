#pragma once
#include <array>
#include "BaseScene.h"
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

//using BOSS_ID = array<BOSS_ID[SEASONE::SEASONE_MAX], ENEMY_ID_MAX>;

class Enemy :
	public Obj
{
public:
	Enemy(VECTOR2 setUpPos, VECTOR2 drawOffset);
	Enemy();
	~Enemy();
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//Player‚ÌˆÚ“®
	VECTOR2 EnemyType(void);
	void Draw(void);
	void HitCheck(void);

	sharedListObj objList;
	BOSS_ID enemyType;
	float enemyHp;
	float maxHp;
	bool enemyBossFlag;
	VECTOR2 meteoPos;
	VECTOR2 speed;
protected:
    bool shotFlag;
	bool meteoriteFlag;
};

