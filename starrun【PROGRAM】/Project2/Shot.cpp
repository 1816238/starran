#include <DxLib.h>
#include "ImageMng.h"
#include "Shot.h"
#include "GameScene.h"


Shot::Shot(VECTOR2 pos, VECTOR2 offset, bool objType) 
{
	this->pos = pos;
	this->offset = offset;
	Shot::init();
}


Shot::~Shot()
{
}

bool Shot::init(void)
{
Obj::init("image/starlight.png", VECTOR2{ 32,32 }, VECTOR2{ 1,1 });

	RotAngle = 0.0;
	return true;
}

void Shot::SetMove(const GameCtl & controller, weekListObj objList)
{
	RotAngle += 0.1;
	pos.x+=5;
}

void Shot::Draw(void)
{
	VECTOR2 tmp = { pos.x + CHIP_SIZE / 2 + offset.x, pos.y + CHIP_SIZE / 2 + offset.y };
	if (tmp > VECTOR2{ 0 , 0 }&&tmp < VECTOR2{ SCREEN_SIZE_X,SCREEN_SIZE_Y })
	{
	DrawRotaGraph(pos.x+ CHIP_SIZE / 2 +offset.x, pos.y+ CHIP_SIZE / 2+offset.y, 1.0, RotAngle, IMAGE_ID("image/starlight.png")[0], true);

	}

}
