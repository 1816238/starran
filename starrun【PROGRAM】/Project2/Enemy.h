#pragma once
#include <array>
#include "BaseScene.h"
#include "Obj.h"
#include "classObj.h"
#include "MapControl.h"

#define AT_DRAW_MAX 3

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
	bool init(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//Player�̈ړ�
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
	unsigned int frequency;				//�U���p�x
	unsigned int at_Cnt;				//��x�ɔ��˂ł����
	unsigned int at_wait;				//�U���̊Ԋu
	unsigned int waitCnt[AT_DRAW_MAX];	

    bool shotFlag;						//�e�𔭎˂��Ă��邩�ǂ���
	bool meteoriteFlag;					//覐΂𔭎˂��Ă��邩�ǂ���
	bool AttackType[AT_TYPE_MAX];		//�U�������
	bool At_DrawFlag[AT_DRAW_MAX];		//�U���z�u�ł�����
};

