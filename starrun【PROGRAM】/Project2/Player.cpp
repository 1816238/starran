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
	keyID_Tbl = { MOUSE_INPUT_LEFT,//��
				  MOUSE_INPUT_RIGHT,//�E
				  MOUSE_ROT_VOL		//β�ى�]��
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
	AddAnim("�ʏ�", 0, 0, 1, 1, true);
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
	//����������
	
	id = lpMapControl.GetMapDate({ pos.x,pos.y + CHIP_SIZE * 2 });
	switch (id)
	{
		//���
	case MAP_ID_CLOUD1:
	case MAP_ID_CLOUD2:
	case MAP_ID_CLOUD3:
		if (!jumpFlag)
		{
			pos.y++;
		}
		break;

		//������
	case MAP_ID_NON:
	case MAP_ID_NON2:
		pos.y++;
		break;

		//�擾����
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
