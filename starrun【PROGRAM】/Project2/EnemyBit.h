#pragma once
#include "Obj.h"

typedef struct Move_Circle
{
	float x;
	float y;
};

typedef struct Move_Pos
{
	Move_Circle center_pos;	//���S���W
	float time;				//����
	int circle_r;			//�~�̔��a
};

class EnemyBit :
	public Obj
{
public:
	EnemyBit(VECTOR2 pos, VECTOR2 offset);
	~EnemyBit();
	bool initAnim(void);
	bool init(void);
	OBJ_TYPE CheckObjType(void);
	bool CheckDeath(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//
	//void Draw(void);
	double RotAngle;
	VECTOR2 offset;
	int speed;
	int time;
	bool deathFlag;
	/*�~�^���v�Z�p*/
	Move_Pos circle_pos;
	int cnt;
	float tmp_pos_x;
	float tmp_pos_y;
};

