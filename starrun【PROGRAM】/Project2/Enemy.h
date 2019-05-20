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
	CANCER,
	LEO,
	VIRGO,
	LIBRA,
	SCORPIO,
	SAGITTARIUS,
	ARIES,
	TAURUS,
	GEMINI,
	CAPRICORN,
	AQUARIUS,
	PISCES,
	NON,
	ENEMY_ID_MAX,

};

enum ENEMY_AT_TYPE
{
	SHOT,
	METEORITE,
	AT_TYPE_MAX
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
	unsigned int enemyHp;
	unsigned int maxHp;
	bool enemyBossFlag;
	VECTOR2 meteoPos;
	VECTOR2 speed;
protected:
    bool shotFlag;
	bool meteoriteFlag;
	bool AttackType[AT_TYPE_MAX];
	unsigned int frequency;
	unsigned int at_Cnt;
};

