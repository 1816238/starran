#include "Shot.h"



Shot::Shot(VECTOR2 pos, VECTOR2 offset, bool objType)
{
	init("image/starlight.png", VECTOR2{ 32,32 }, VECTOR2{ 1,1 });
	this->pos = pos;
	
	
}


Shot::~Shot()
{
}

void Shot::SetMove(const GameCtl & controller, weekListObj objList)
{

}
//
//void Shot::Draw(void)
//{
//}
