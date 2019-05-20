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
	void SelectAct(VECTOR2 pos, VECTOR2 pos2, int frequency , bool at_shot, bool at_meteorite);
	const bool GetshotFlag();
	const bool GetmeteoriteFlag();
	const int SetPos();
	const int SetAngle();
private:
	void ShotCtl(VECTOR2 pos, VECTOR2 pos2);
	void MeteoCtl(VECTOR2 pos, VECTOR2 pos2);
	int randPos;
	int randAngle;
};

