#include <array>
#include <functional>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "MapControl.h"
#include "GameCtl.h"


Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{

	speed = PLAYER_DF_SPEED;

	jumpFlag = false;
	shotFlag = false;

	/*MAIN*/
	keyID_Tbl = { MOUSE_INPUT_LEFT,//左
				  MOUSE_INPUT_RIGHT,//右
				  MOUSE_ROT_VOL		//ﾎｲｰﾙ回転量
				  };

	/*MAIN*/
	speed_Tbl = { (PLAYER_DF_SPEED),/*下*/
				  (-PLAYER_DF_SPEED),/*左*/
				  (PLAYER_DF_SPEED),/*右*/
				  (-PLAYER_DF_SPEED) /*上*/ };

	mapMove_Tbl = {
		true,		//MAP_ID_CUR,
		true,		//MAP_ID_FLOOR1,
		true,		//MAP_ID_FLOOR2,
		true,		//MAP_ID_BOMB,
		true,		//MAP_ID_NON,
		false,		//MAP_ID_WALL1,
		false,		//MAP_ID_WALL2,
		false,		//MAP_ID_BLOCK,
		true,		//MAP_ID_ITEM_FIRE,
		true,		//MAP_ID_ITEM_BOMB,
		true,		//MAP_ID_ITEM_CTL,
		true,		//MAP_ID_ITEM_SPEED,
	};
	init("image/bomberman.png", VECTOR2(100 / 5, 128 / 4), VECTOR2(5, 4), setUpPos);
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
	AddAnim("停止", 0, 0, 1, 1, true);
	AddAnim("移動", 0, 2, 2, 7, true);
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
	auto sidePos = [&](DIR dir) {
		VECTOR2 side;
		switch (dir)
		{
		case DIR_DOWN:
			side = { 0,chipSize + speed_Tbl[dir] - 2 };
			break;
		case DIR_LEFT:
			side = { speed_Tbl[dir],0 };
			break;
		case DIR_RIGHT:
			side = { speed_Tbl[dir] + chipSize - 2, 0 };
			break;
		case DIR_UP:
			side = { 0,speed_Tbl[dir] };
			break;
		default:
			break;
		}
		return pos + side;
	};

	[/*ｷｬﾌﾟﾁｬｰ部*/](/*引数部（省略できる）*/) {/*実行部*/};
	auto Mover = [&](DIR_TBL_ID Dir)
	{
		//補正処理
		if (!mapMove_Tbl[lpMapControl.GetMapDate(sidePos(dir))])
		{
			//移動不可のｵﾌﾞｼﾞｪｸﾄが隣に存在した場合
			SetAnim("停止");
			return false;

		}
		SetAnim("移動");
		return true;
	};
	Mover(DIR_TBL_MAIN);
	Mover(DIR_TBL_OPP);
	for (int n = 0; n < DIR_TBL_MAX; n++)
	{

		if (!Mover(DIR_TBL_SUB1))
		{
			Mover(DIR_TBL_SUB2);
		}
	}
}
