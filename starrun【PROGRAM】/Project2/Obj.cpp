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

bool Obj::CheckDeath(void)
{
	return deathFlag;
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
	if (objType == TYPE_ENEMY_SHOT)
	{
		DrawCircle(pos.x+15, pos.y+16, 10, 0xffffff, false);
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

void Obj::Setdeath(bool flag)
{
	deathFlag = flag;
}

void Obj::SetDamageFlag(bool flag, int damage)
{
	if (!damageFlag&&flag)
	{
		damageFlag = flag;
		HP -= damage;
	}
	else if(damageFlag&&flag)
	{
		Setdeath(true);
	}else{}
	Obj::damage = damage;
}

int Obj::GetBitNo(void)
{
	return bit_no;
}

OBJ_TYPE Obj::CheckObjType(void)
{
	return objType;
}

void Obj::SetVSpos(VECTOR2 pos,int set)
{
	
	VSpos[set] = pos;
}

VECTOR2 Obj::GetVSpos(int set)
{

	return VSpos[set];
}

