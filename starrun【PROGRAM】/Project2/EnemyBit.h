#pragma once
#include "Obj.h"

#define PI  3.1415926535897932384626433832795f
#define CIRCLE_PI ( PI*2 )

typedef struct Move_Circle
{
	float x;
	float y;
};

typedef struct Move_Pos
{
	Move_Circle center_pos;	//’†SÀ•W
	float time;				//üŠú
	int circle_r;			//‰~‚Ì”¼Œa
};

class EnemyBit :
	public Obj
{
public:
	EnemyBit(VECTOR2 pos, VECTOR2 offset,int bit_cnt,int HP);
	~EnemyBit();
	bool initAnim(void);
	bool init(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//
	//void Draw(void);
	double RotAngle;
	VECTOR2 offset;
	int speed;
	int time;
	bool deathFlag;
	/*‰~‰^“®ŒvZ—p*/
	Move_Pos circle_pos;
	int cnt;
	float tmp_pos_x;
	float tmp_pos_y;

};

