#pragma once
#include "classObj.h"
#include "Enemy.h"

#define lpEnemyAct EnemyAct::GetInstance()


class EnemyAct:
	public Enemy
{
public:
	static EnemyAct &GetInstance(void)
	{
		static EnemyAct s_Instance;
		return s_Instance;
	}
	EnemyAct();
	~EnemyAct();
	void SelectAct(VECTOR2 pos, VECTOR2 pos2, int frequency ,BOSS_ID enemy_name, int at_wait,int waitcnt,int waitcnt2,int waitcnt3);
	const bool GetmeteoriteFlag();
	const int SetPos();
	const int SetAngle();
	void SetMeteoFlag(bool flag);
private:
	int randPos;
	int randAngle;
	int max_waitCnt;

};

