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
	dir = DIR_RIGHT;
	/*MAIN*/
	keyID_Tbl = { KEY_INPUT_NUMPAD2,//下 
				  KEY_INPUT_NUMPAD4,//左
				  KEY_INPUT_NUMPAD6,//右
				  KEY_INPUT_NUMPAD8,/*上*/ };

	/*MAIN*/
	pos_Tbl = { &pos.y,/*下*/
				&pos.x,/*左*/
				&pos.x,/*右*/
				&pos.y /*上*/ };

	/*MAIN*/
	speed_Tbl = { (PLAYER_DF_SPEED),/*下*/
				  (-PLAYER_DF_SPEED),/*左*/
				  (PLAYER_DF_SPEED),/*右*/
				  (-PLAYER_DF_SPEED) /*上*/ };

	/*MAIN	  OPP	  SUB1	   SUB2*/
	dir_Tbl = { DIR_DOWN,DIR_UP	,DIR_LEFT	 ,DIR_RIGHT ,/*下*/
				DIR_LEFT	,DIR_RIGHT	,DIR_DOWN,DIR_UP,/*左*/
				DIR_RIGHT	,DIR_LEFT	,DIR_DOWN,DIR_UP,/*右*/
				DIR_UP	,DIR_DOWN,DIR_LEFT	 ,DIR_RIGHT  /*上*/ };
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
	auto &key_Tbl = controller.GetCtl(KEY_TYPE_NOW);
	auto &key_Old_Tbl = controller.GetCtl(KEY_TYPE_OLD);

	if (key_Tbl[KEY_INPUT_SPACE] & (~key_Old_Tbl[KEY_INPUT_SPACE]))
	{
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

		if (key_Tbl[keyID_Tbl[dir_Tbl[dir][Dir]]])
		{
			dir = dir_Tbl[dir][Dir];

			//補正処理
			if (dir == DIR_DOWN || dir == DIR_UP)
			{
				pos.x = (((pos.x + (chipSize / 2))) / chipSize) * chipSize;
			}
			if (dir == DIR_LEFT || dir == DIR_RIGHT)
			{
				pos.y = (((pos.y + (chipSize / 2))) / chipSize) * chipSize;
			}
			if (!mapMove_Tbl[lpMapControl.GetMapDate(sidePos(dir))])
			{
				//移動不可のｵﾌﾞｼﾞｪｸﾄが隣に存在した場合
				SetAnim("停止");
				return false;

			}
			//移動処理
			(*pos_Tbl[dir]) += speed_Tbl[dir];

			SetAnim("移動");
			return true;
		}
		return false;
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
