#pragma once
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
	void SelectAct(VECTOR2 pos, VECTOR2 pos2, int frequency , bool at_shot, bool at_meteorite, int at_wait,int waitcnt,int waitcnt2,int waitcnt3);
	const bool GetshotFlag();
	const bool GetmeteoriteFlag();
	const bool GetAtDrawFlag(int num);
	const int SetPos();
	const int SetAngle();
private:
	void ShotCtl(VECTOR2 pos, VECTOR2 pos2, int waitcnt, int waitcnt2, int waitcnt3);
	void MeteoCtl(VECTOR2 pos, VECTOR2 pos2);
	int randPos;
	int randAngle;
	int max_waitCnt;
};

