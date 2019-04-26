#include <Dxlib.h>
#include "ImageMng.h"
#include "GameController.h"
#include "Obj.h"

Obj::Obj(VECTOR2 drawOffset):drawOffset(drawOffset)		//	‰Šú‰»‚·‚é‚±‚Æ‚Åconst‚É’l‚ð“n‚¹‚é‚æ‚¤‚É‚È‚é
{
	dir = DIR::DOWN;
	visible = true;
}

Obj::Obj()
{
	dir = DIR::DOWN;
	visible = true;
}

bool Obj::init(string FileName, VECTOR2 DivSize, VECTOR2 DivCnt, VECTOR2 Pos)
{
	init(FileName, DivSize, DivCnt);
	SetPos(Pos);
	return false;
}

bool Obj::init(string FileName, VECTOR2 DivSize, VECTOR2 DivCnt)
{
	lpImageMng.GetID(FileName, DivSize, DivCnt);
	imageName = FileName;
	this->divSize = DivSize;
	this->divCnt = DivCnt;
	return true;
}

Obj::~Obj()
{
}

void Obj::UpDate(const GameController &controller, weekListObj objList)
{
	SetMove(controller,objList);
}

void Obj::Draw(unsigned int id)
{
	if (id < IMAGE_ID(imageName).size())
	{
		if (visible)
		{
			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[id], true);
		}
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
		int count = (animCnt / animTbl[animName][static_cast<int>(ANIM_TBL::INV)]);
		if (count < animTbl[animName][static_cast<int>(ANIM_TBL::FRAME)] 
				 || animTbl[animName][static_cast<int>(ANIM_TBL::LOOP)])
		{
			count = count % animTbl[animName][static_cast<int>(ANIM_TBL::FRAME)];
		}
		else
		{
			count = animTbl[animName][static_cast<int>(ANIM_TBL::FRAME)] - 1;
			animEndFlag = true;
			visible = false;
		}

		ID = animTbl[animName][static_cast<int>(ANIM_TBL::START_ID)] + static_cast<int>(dir)
			+ count * divCnt.x;
	}
	animCnt++;

	if (ID < IMAGE_ID(imageName).size())
	{
		if (visible)
		{
			DrawGraph(drawOffset.x + pos.x, drawOffset.y + pos.y, IMAGE_ID(imageName)[ID], true);
		}
	}

}

const VECTOR2 & Obj::GetPos(void)
{
	return pos;
}

bool Obj::AddAnim(string anim_Name, int ID_x, int ID_y, int frame, int inv,bool loop)
{
	animTbl[anim_Name][static_cast<int>(ANIM_TBL::START_ID)] = ID_y * divCnt.x + ID_x;
	animTbl[anim_Name][static_cast<int>(ANIM_TBL::INV)]		 = inv;
	animTbl[anim_Name][static_cast<int>(ANIM_TBL::FRAME)]	 = frame;
	animTbl[anim_Name][static_cast<int>(ANIM_TBL::LOOP)]	 = loop;
	return true;
}

bool Obj::SetAnim(string anim_Name)
{
	if (animName == anim_Name)
	{
		return true;
	}
	if (animTbl.find(anim_Name) == animTbl.end())
	{
		return false;
	}
	animName = anim_Name;
	Obj::animCnt = 0;
	animEndFlag = false;

	return false;
}



std::string Obj::GetAnim(void)
{
	return animName;
}

void Obj::SetPos(VECTOR2 Pos)
{
	Obj::pos = Pos;
}
