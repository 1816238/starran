#include <array>
#include <functional>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "MapControl.h"
#include "GameCtl.h"


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

	if (key_Tbl[MOUSE_INPUT_RIGHT])
	{
		shotFlag = true;
	}
	
	if (key_Tbl[MOUSE_INPUT_LEFT] & (~key_Old_Tbl[MOUSE_INPUT_LEFT]))
	{
		jumpFlag = true;
	}

	auto &chipSize = lpMapControl.GetChipSize().x;
}
