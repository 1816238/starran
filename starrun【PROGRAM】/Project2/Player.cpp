#include <array>
#include <functional>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "MapControl.h"
#include "GameCtl.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "SpeedMng.h"

Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{


	shotFlag = false;

	/*MAIN*/
	keyID_Tbl = { MOUSE_INPUT_LEFT,//��
				  MOUSE_INPUT_RIGHT,//�E
				  MOUSE_ROT_VOL		//β�ى�]��
				  };

	speed = PLAYER_DF_SPEED;
	initAnim();

	for (int i = 0; i < 3; i++)
	{
		getcnt[i] = 0;

	}
	pos = setUpPos;
	init("image/player.png", VECTOR2(PLAYER_SIZE_X, PLAYER_SIZE_Y), VECTOR2(1, 1), setUpPos);
	for (int j = 0; j < 2; j++)
	{
		
		jumpFlag[j] = false;

	}
	SavePos = 0;
	DirPos = {	VECTOR2{ PLAYER_SIZE_X-1,1},// ��
				VECTOR2{PLAYER_SIZE_X/2,PLAYER_SIZE_Y}, // ��
				VECTOR2{1,PLAYER_SIZE_Y/2}, // ��
				VECTOR2{PLAYER_SIZE_X-1,PLAYER_SIZE_Y/2}, // �E
			};
}

Player::Player()
{
}

Player::~Player()
{
}

bool Player::initAnim(void)
{
	//AddAnim("�ʏ�", 0, 0, 1, 1, true);
	return true;
}

void Player::SetMove(const GameCtl & controller, weekListObj objList)
{
	auto &key_Tbl = controller.GetCtl(NOW);
	auto &key_Old_Tbl = controller.GetCtl(OLD);
	bool Click[2];
	bool ClickOld[2];
	pos.x = CHIP_SIZE * 2 + Time;
	for (int i = 0x00; i < MOUSE_INPUT_RIGHT; i++)
	{
		Click[i] = controller.GetClick(i, NOW);
		ClickOld[i] = controller.GetClick(i, OLD);

	}
	MAP_ID id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN]);

	//�V���b�g
	if (Click[MOUSE_INPUT_RIGHT]&(~ClickOld[MOUSE_INPUT_RIGHT]))
	{
		shotFlag = true;
	}
	//�W�����v
	if (Click[MOUSE_INPUT_LEFT] & (~ClickOld[MOUSE_INPUT_LEFT]))
	{
		
		if (id >= MAP_ID_CLOUD1 && id <= MAP_ID_CLOUD3)
		{

			if (!jumpFlag[0])
			{
				jumpFlag[0] = true;
				SavePos = pos.y;

			}
		}
		else
		{
			if (!jumpFlag[1])
			{
				jumpFlag[1] = true;
				SavePos = pos.y;
			}
		}
		
	}
	
	if (jumpFlag[0])
	{
		pos.y -= 4;
		if (SavePos - pos.y > CHIP_SIZE * 2.5)
		{
			jumpFlag[0] = false;
		}
	}
	if (jumpFlag[1])
	{
		pos.y -= 4;
		if (id >= MAP_ID_CLOUD1 && id <= MAP_ID_CLOUD3)
		{
			

			jumpFlag[1] = false;
		}

	}

	auto &chipSize = lpMapControl.GetChipSize().x;

	CheckMapHit();
	

}



void Player::Draw(void)
{

	DrawGraph(CHIP_SIZE*2, pos.y, IMAGE_ID("image/player.png")[0], true);
	DrawFormatString(0, 0, 0xff00ff, "time:%d", Time);
}

void Player::CheckMapHit(void)
{
	MAP_ID id;
	auto get_star = [&](MAP_ID id,DIR_TBL_ID dir) {
		getcnt[((int)id) - ((int)MAP_ID_YELLOW)]++;
		lpMapControl.GetInstance().SetMapData(pos+DirPos[dir], MAP_ID_NON);
		return true;

	};


	for (int i = 0; i < DIR_MAX; i++)
	{
		id = lpMapControl.GetMapDate(pos+DirPos[i]);
		switch (id)
		{
			//���(�W�����v���������画����s��Ȃ�)
		case MAP_ID_CLOUD1:
		case MAP_ID_CLOUD2:
		case MAP_ID_CLOUD3:
			if (i == DIR_DOWN)
			{
				if (!jumpFlag[0]&&!jumpFlag[1])
				{
					pos.y = pos.y / CHIP_SIZE * CHIP_SIZE;
				}
				
			}
			
			break;
			//������

		case MAP_ID_YELLOW:
		case MAP_ID_GREEN:
		case MAP_ID_RED:
			get_star(id, (DIR_TBL_ID)i);
		case MAP_ID_NON:
		case MAP_ID_NON2:
			if (i == DIR_DOWN)
			{
				if (!jumpFlag[0]&&!jumpFlag[1])
				{
					pos.y+=3;
				}
			}
			break;
		case MAP_ID_MAX:
		default:
			break;
		}
	}
}
