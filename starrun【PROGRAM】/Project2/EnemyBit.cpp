#include <DxLib.h>
#include "ImageMng.h"
#include "Enemy.h"
#include "VECTOR2.h"
#include "EnemyBit.h"

#define PI  3.1415926535897932384626433832795f
#define CIRCLE_PI ( PI*2 )

EnemyBit::EnemyBit(VECTOR2 pos, VECTOR2 offset,int bit_cnt,int HP)
{
	//Obj::init("image/player_W.png", VECTOR2(40, 64), VECTOR2(1, 1), pos);

	this->pos = pos;
	this->offset = offset;
	this->speed = 1;
	this->objType = TYPE_ENEMY_BIT;
	this->HP = HP;
	this->bit_no = bit_cnt;
	OutputDebugString("pop\n");

	EnemyBit::init();

}

EnemyBit::~EnemyBit()
{
}

bool EnemyBit::initAnim(void)
{
	return false;
}

bool EnemyBit::init(void)
{
	if (objType == TYPE_ENEMY_BIT)
	{
		Obj::init("image/boss.png", VECTOR2(43, 45), VECTOR2(5, 1), pos);
		AddAnim("í èÌ", 1, 0, 4, 10, true);
		SetAnim("í èÌ");
	}

	circle_pos.center_pos = { CENTER_POS_X,CENTER_POS_Y };
	circle_pos.circle_r = CIRCLE_RANGE;
	circle_pos.time = 3600;
	return true;
}


void EnemyBit::SetMove(const GameCtl & controller, weekListObj objList)
{
	float x=0;
	float y=0;
	SetAnim("í èÌ");

	cnt++;
	auto Circle_Drwa = [&](int num)
	{
		if(bit_no < 2)
		{
			tmp_pos_x = circle_pos.center_pos.x + num * sin(CIRCLE_PI / circle_pos.time * cnt) * circle_pos.circle_r;
			tmp_pos_y = circle_pos.center_pos.y - num * cos(CIRCLE_PI / circle_pos.time * cnt) * circle_pos.circle_r;
		}
		else
		{
			tmp_pos_x = circle_pos.center_pos.x + num * cos(CIRCLE_PI / circle_pos.time * cnt) * circle_pos.circle_r;
			tmp_pos_y = circle_pos.center_pos.y + num * sin(CIRCLE_PI / circle_pos.time * cnt) * circle_pos.circle_r;
		}
	};

	if (bit_no == 0 || bit_no == 2)
	{
		Circle_Drwa(1);
	}
	if (bit_no == 1 || bit_no == 3)
	{
		Circle_Drwa(-1);
	}
	deathFlag = (HP <= 0 ? true : false);
/*
	tmp_pos_x = circle_pos.center_pos.x - cos(CIRCLE_PI / circle_pos.time*cnt) * circle_pos.circle_r;
	tmp_pos_y = circle_pos.center_pos.y - sin(CIRCLE_PI / circle_pos.time*cnt) * circle_pos.circle_r;ç∂*/
	SetPos(VECTOR2(tmp_pos_x, tmp_pos_y));
}

//void EnemyBit::Draw(void)
//{
//	SetAnim("í èÌ");
//	DrawGraph(0, 0, IMAGE_ID("image/boss.png")[0],true);
//	DrawBox(tmp_pos_x, tmp_pos_y, tmp_pos_x + 100, tmp_pos_y + 100, 0x00ff00, false);
//}
