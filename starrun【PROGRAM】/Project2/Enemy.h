#pragma once
#include <array>
#include "BaseScene.h"
#include "Obj.h"
#include "classObj.h"
#include "MapControl.h"

#define AT_DRAW_MAX 3
#define SHOT_SPEED 6

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
	ENEMY_ID_MAX

};

enum ENEMY_AT_TYPE
{
	SHOT,
	METEORITE,
	AT_TYPE_MAX
};

//using BOSS_ID = array<BOSS_ID[SEASONE::SEASONE_MAX], ENEMY_ID_MAX>;
using BOSS_NAME = array<BOSS_ID, ENEMY_ID_MAX>;
using BOSS_SEASONE = array<SEASONE[ENEMY_ID_MAX], SEASONE_MAX>;
using BOSS_AT_TYPE = array<bool, ENEMY_ID_MAX>;
using BOSS_ect = array<unsigned int, ENEMY_ID_MAX>;
using BOSS_DIV_ID = array<VECTOR2, ENEMY_ID_MAX>;
class Enemy :
	public Obj
{
public:
	Enemy(VECTOR2 setUpPos, VECTOR2 drawOffset);
	Enemy();
	~Enemy();
	bool init(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//Playerの移動
	VECTOR2 EnemyType(void);
	void Draw(void);
	void HitCheck(void);
	sharedListObj objList;
	BOSS_ID enemyType;
	BOSS_NAME enemy_name;
	BOSS_SEASONE seasone;
	unsigned int enemyHp;
	unsigned int maxHp;
	BOSS_ect max_hp;
	BOSS_ect enemy_hp;
	bool enemyBossFlag;
	BOSS_DIV_ID boss_ID;
	VECTOR2 meteoPos;
	VECTOR2 speed;
protected:
	BOSS_ect frequency;
	unsigned int Frequency;				//攻撃頻度
	unsigned int at_Cnt;				//一度に発射できる個数
	unsigned int at_wait;				//攻撃の間隔
	unsigned int waitCnt[AT_DRAW_MAX];	

    bool shotFlag;						//弾を発射しているかどうか
	bool meteoriteFlag;					//隕石を発射しているかどうか
	bool AttackType[AT_TYPE_MAX];		//攻撃ﾊﾟﾀｰﾝ
	BOSS_AT_TYPE At_Type;				//攻撃ﾊﾟﾀｰﾝ
	bool At_DrawFlag[AT_DRAW_MAX];		//攻撃配置できる種類
};

