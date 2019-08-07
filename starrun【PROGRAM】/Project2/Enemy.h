#pragma once
#include <array>
#include "BaseScene.h"
#include "Obj.h"
#include "classObj.h"
#include "MapControl.h"

#define AT_DRAW_MAX 3
#define SHOT_SPEED -6

#define CENTER_POS_X ( SCREEN_SIZE_X - SCREEN_SIZE_X / 4 + 125  - 43 / 2) 
#define CENTER_POS_Y ( SCREEN_SIZE_Y / 4 + 125 - 43 / 2)
#define CIRCLE_RANGE ( 250 -(60+43))

struct enemy
{
	unsigned int maxHp;
	unsigned int Hp;
	int bit_cnt;
};

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

enum METEO_ANGLE
{
	ANGLE_15,
	ANGLE_30,
	ANGLE_45,
	ANGLE_60,
	ANGLE_MAX
};

//using BOSS_ID = array<BOSS_ID[SEASONE::SEASONE_MAX], ENEMY_ID_MAX>;
using BOSS_NAME = array<BOSS_ID, ENEMY_ID_MAX>;
using BOSS_SEASONE = array<SEASONE[( ENEMY_ID_MAX - 1)/ SEASONE_MAX], SEASONE_MAX>;
using BOSS_AT_TYPE = array<bool[AT_TYPE_MAX], ENEMY_ID_MAX>;
using BOSS_ect = array<float, ENEMY_ID_MAX>;
using BOSS_DIV_ID = array<VECTOR2, ENEMY_ID_MAX>;
using BOSS_SHOT = array<int, 0x10>;

class Enemy :
	public Obj
{
public:
	Enemy(OBJ_TYPE objType,Mode mode);
	Enemy();
	~Enemy();
	bool init(void);
	OBJ_TYPE CheckObjType(void);
	bool meteo[3];

private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//PlayerÇÃà⁄ìÆ
	//void CircleMove(void);
	VECTOR2 GetCircleMove_pos(void);
	//VECTOR2 EnemyType(void);
	void Draw(void);
	void HitCheck(void);
	//BOSS_NAME enemy_name;
	//BOSS_SEASONE seasone;
	enemy enemy;
	bool enemyBossFlag;
	//BOSS_DIV_ID boss_ID;
	//VECTOR2 meteoPos;
	VECTOR2 speed;
 	//int meteo_waitCnt;
	int shot_waitCnt;
    bool shotFlag[AT_DRAW_MAX];						//íeÇî≠éÀÇµÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©
	//bool enemy_shift_flag;
	unsigned int at_Cnt;				//àÍìxÇ…î≠éÀÇ≈Ç´ÇÈå¬êî
	unsigned int at_wait;				//çUåÇÇÃä‘äu
	unsigned int waitCnt[AT_DRAW_MAX];
	unsigned int shotcnt;
	vector<ListObj_itr> BitObj;
	BOSS_SHOT enemy_shot_tbl;
	Mode mode;

protected:
	//BOSS_ID enemyType;
	sharedListObj objList;
	BOSS_ect frequency;
	unsigned int Frequency;				//çUåÇïpìx
	bool meteoriteFlag;					//Ë¶êŒÇî≠éÀÇµÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©
	bool AttackType[AT_TYPE_MAX];		//çUåÇ ﬂ¿∞›
	//BOSS_AT_TYPE At_Type;				//çUåÇ ﬂ¿∞›
};