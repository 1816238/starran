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
	keyID_Tbl = { KEY_INPUT_NUMPAD2,//�� 
				  KEY_INPUT_NUMPAD4,//��
				  KEY_INPUT_NUMPAD6,//�E
				  KEY_INPUT_NUMPAD8,/*��*/ };

	/*MAIN*/
	pos_Tbl = { &pos.y,/*��*/
				&pos.x,/*��*/
				&pos.x,/*�E*/
				&pos.y /*��*/ };

	/*MAIN*/
	speed_Tbl = { (PLAYER_DF_SPEED),/*��*/
				  (-PLAYER_DF_SPEED),/*��*/
				  (PLAYER_DF_SPEED),/*�E*/
				  (-PLAYER_DF_SPEED) /*��*/ };

	/*MAIN	  OPP	  SUB1	   SUB2*/
	dir_Tbl = { DIR_DOWN,DIR_UP	,DIR_LEFT	 ,DIR_RIGHT ,/*��*/
				DIR_LEFT	,DIR_RIGHT	,DIR_DOWN,DIR_UP,/*��*/
				DIR_RIGHT	,DIR_LEFT	,DIR_DOWN,DIR_UP,/*�E*/
				DIR_UP	,DIR_DOWN,DIR_LEFT	 ,DIR_RIGHT  /*��*/ };
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
	AddAnim("��~", 0, 0, 1, 1, true);
	AddAnim("�ړ�", 0, 2, 2, 7, true);
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

	[/*���������*/](/*�������i�ȗ��ł���j*/) {/*���s��*/};
	auto Mover = [&](DIR_TBL_ID Dir)
	{

		if (key_Tbl[keyID_Tbl[dir_Tbl[dir][Dir]]])
		{
			dir = dir_Tbl[dir][Dir];

			//�␳����
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
				//�ړ��s�̵�޼ު�Ă��ׂɑ��݂����ꍇ
				SetAnim("��~");
				return false;

			}
			//�ړ�����
			(*pos_Tbl[dir]) += speed_Tbl[dir];

			SetAnim("�ړ�");
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
