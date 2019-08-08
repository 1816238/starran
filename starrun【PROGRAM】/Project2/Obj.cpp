#include <Dxlib.h>
#include "ImageMng.h"
#include "GameCtl.h"
#include "BaseScene.h"
#include "Obj.h"

Obj::Obj(VECTOR2 drawOffset) :drawOffset(drawOffset)		//	‰Šú‰»‚·‚é‚±‚Æ‚Åconst‚É’l‚ð“n‚¹‚é‚æ‚¤‚É‚È‚é
{
	dir = DIR_DOWN;
}

Obj::Obj()
{
}

bool Obj::init(string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos)
{
	init(fileName, divSize, divCnt);
	SetPos(pos);
	return false;
}

bool Obj::init(string fileName, VECTOR2 divSize, VECTOR2 divCnt)
{
	lpImageMng.GetID(fileName, divSize, divCnt);
	imageName = fileName;
	this->divSize = divSize;
	this->divCnt = divCnt;
	return true;
}

Obj::~Obj()
{
}

void Obj::UpDate(const GameCtl &controller, weekListObj objList)
{
	SetMove(controller, objList);
}

bool Obj::CheckEnd(void)
{
	return EndFlag;
}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
	}
}

void Obj::Draw(void)
{
	if (imageName.length() == 0)
	{
		return;
	}
	unsigned int ID = 0;
	if (animTbl.find(animName) != animTbl.end())
	{
		int count = (animCnt / animTbl[animName][ANIM_TBL_INV]);
		if (count < animTbl[animName][ANIM_TBL_FRAME] || animTbl[animName][ANIM_TBL_LOOP])
		{
			count = count % animTbl[animName][ANIM_TBL_FRAME];
		}
		else
		{
			count = animTbl[animName][ANIM_TBL_FRAME] - 1;
			animEndFlag = true;
		}

		ID = animTbl[animName][ANIM_TBL_START_ID] + count ;
	}
	animCnt++;
	
	if (ID < IMAGE_ID(imageName).size())
	{
		if (imageName != "image/player_W.png")
		{
			DrawGraph( pos.x, pos.y, IMAGE_ID(imageName)[ID], true);

		}
	}
	//
	if (objType == TYPE_ENEMY_SHOT)
	{
		DrawCircle(pos.x+15, pos.y+16, 10, 0xffffff, false);
	}
	if (objType == TYPE_PLAYER_SHOT)
	{
		DrawCircle(pos.x + 32, pos.y+16 , 10, 0xffffff, false);
	}
	if (objType == TYPE_ENEMY_BIT)
	{
		DrawCircle(pos.x+22, pos.y+22, 22, 0xffffff, false);
	}
	if (objType == TYPE_METEO)
	{
		switch (obj_no)
		{
		case 0:
			DrawCircle(pos.x + 10+20, pos.y +  250+20, 20, 0xf0ff0f, false);

			break;
		case 1:
			DrawCircle(pos.x + 20+15, pos.y + 340+15, 15, 0xf0ff0f, false);

			break;
		case 2:
			DrawCircle(pos.x + 10+15, pos.y + 420+15, +15, 0xf0ff0f, false);

			break;
		case 3:
			DrawCircle(pos.x + 20, pos.y + 470+20, 22, 0xf0ff0f, false);

			break;
		default:
			break;
		}

	}
	//DrawFormatString(0, 20, 0x00ffff, "PLAYER‚ÌÀ•W\nX...%d\nY...%d\n", pos.x, pos.y);

}

const VECTOR2 & Obj::GetPos(void)
{
	return pos;
}

bool Obj::AddAnim(string animName, int ID_x, int ID_y, int frame, int inv, bool loop)
{
	animTbl[animName][ANIM_TBL_START_ID] = ID_y * divCnt.x + ID_x;
	animTbl[animName][ANIM_TBL_INV] = inv;
	animTbl[animName][ANIM_TBL_FRAME] = frame;
	animTbl[animName][ANIM_TBL_LOOP] = loop;
	return true;
}

bool Obj::SetAnim(string animName)
{
	if (Obj::animName == animName)
	{
		return true;
	}
	if (animTbl.find(animName) == animTbl.end())
	{
		return false;
	}
	Obj::animName = animName;
	Obj::animCnt = 0;
	animEndFlag = false;

	return false;
}

std::string Obj::GetAnim(void)
{
	return animName;
}

void Obj::SetPos(VECTOR2 pos)
{
	Obj::pos = pos;
}


bool Obj::CheckHit(VECTOR2 pos1, VECTOR2 objSize1, VECTOR2 pos2, VECTOR2 objSize2)
{
	if (pos1.x < pos2.x + objSize2.x
		&&  pos2.x < pos1.x + objSize1.x
		&&  pos1.y < pos2.y + objSize2.y
		&&  pos2.y < pos1.y + objSize1.y)
	{
		return true;
	}
	return false;
}

const void Obj::SetEnd(bool flag)
{
	EndFlag = flag;
}

const void Obj::SetDamage(bool flag, int damage)
{
	damageFlag = flag;
	Obj::damage = damage;
}

const void Obj::SetDamage(bool flag)
{
	if (!damageFlag&&flag)
	{
		damageFlag = flag;
	}
	else if (damageFlag&&flag)
	{
		SetEnd(true);
	}
	else {}
}

const int Obj::GetObjNo(void)const
{
	return obj_no;
}

const int Obj::GetHP(void)const
{
	return HP;
}

const void Obj::SetHP(int hp)
{
	HP = hp;
}

const int Obj::GetParam(void) const
{
	return 0;
}

const void Obj::SetParam(int hp)
{
	return void();
}

const int Obj::GetAttack(void) const
{
	return attack;
}

const int Obj::GetScore(void)const
{
	return Score;
}

const void Obj::AddScore(int num)
{
	Score += num;
}

const bool Obj::GetSwitchFlag(void)const
{
	return switchFlag;
}

void Obj::SetSwitchFlag(bool flag)
{
	switchFlag = flag;
}


OBJ_TYPE Obj::CheckObjType(void)
{
	return objType;
}



