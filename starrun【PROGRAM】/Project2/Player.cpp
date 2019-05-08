#include <array>
#include <functional>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "MapControl.h"
#include "GameCtl.h"
#include "ImageMng.h"

Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{


	jumpFlag = false;
	shotFlag = false;

	/*MAIN*/
	keyID_Tbl = { MOUSE_INPUT_LEFT,//ç∂
				  MOUSE_INPUT_RIGHT,//âE
				  MOUSE_ROT_VOL		//Œ≤∞ŸâÒì]ó 
				  };

	speed = PLAYER_DF_SPEED;
	initAnim();
	pos = {64,0};
}

Player::Player()
{
}

Player::~Player()
{
}

bool Player::initAnim(void)
{
	AddAnim("í èÌ", 0, 0, 1, 1, true);
	return true;
}

void Player::SetMove(const GameCtl & controller, weekListObj objList)
{
	auto &key_Tbl = controller.GetCtl(NOW);
	auto &key_Old_Tbl = controller.GetCtl(OLD);
	MAP_ID id;
	if (key_Tbl[MOUSE_INPUT_RIGHT])
	{
		shotFlag = true;
	}
	
	if (key_Tbl[MOUSE_INPUT_LEFT] & (~key_Old_Tbl[MOUSE_INPUT_LEFT]))
	{
		jumpFlag = true;
	}
	
	auto &chipSize = lpMapControl.GetChipSize().x;
	//ë´å≥Çå©ÇÈ
	
	id = lpMapControl.GetMapDate({ pos.x,pos.y + CHIP_SIZE * 2 });
	switch (id)
	{
		//èÊÇÈ
	case MAP_ID_CLOUD1:
	case MAP_ID_CLOUD2:
	case MAP_ID_CLOUD3:
		if (!jumpFlag)
		{
			pos.y++;
		}
		break;

		//óéÇøÇÈ
	case MAP_ID_NON:
	case MAP_ID_NON2:
		pos.y++;
		break;

		//éÊìæÇ∑ÇÈ
	case MAP_ID_YELLOW:
	case MAP_ID_GREEN:
	case MAP_ID_RED:

		break;

	case MAP_ID_MAX:
	default:
		pos.y++;
		break;
	}

	

}

void Player::Draw(void)
{
	DrawGraph(pos.x, pos.y, IMAGE_ID("image/player.png")[0], true);
}
