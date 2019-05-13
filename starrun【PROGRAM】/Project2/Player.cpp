#include <array>
#include <functional>
#include <math.h>
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
	keyID_Tbl = { MOUSE_INPUT_LEFT,//左
				  MOUSE_INPUT_RIGHT,//右
				  MOUSE_ROT_VOL		//ﾎｲｰﾙ回転量
				  };

	JSpeed = 3;
	initAnim();

	for (int i = 0; i < 3; i++)
	{
		getcnt[i] = 0;

	}
	pos = setUpPos;
	init("image/player.png", VECTOR2(PLAYER_SIZE_X, PLAYER_SIZE_Y), VECTOR2(1, 1), setUpPos);		
	jumpFlag = false;
	DownCheck = false;
	SavePos = 0;
	DirPos = {	VECTOR2{ PLAYER_SIZE_X-1,1},// 上
				VECTOR2{PLAYER_SIZE_X/2,PLAYER_SIZE_Y}, // 下
				VECTOR2{1,PLAYER_SIZE_Y/2}, // 左
				VECTOR2{PLAYER_SIZE_X-1,PLAYER_SIZE_Y/2}, // 右
			};
	DeathFlag = false;
}

Player::Player()
{
}

Player::~Player()
{
}

bool Player::initAnim(void)
{
	//AddAnim("通常", 0, 0, 1, 1, true);
	return true;
}

void Player::SetMove(const GameCtl & controller, weekListObj objList)
{
	auto &key_Tbl = controller.GetCtl(NOW);
	auto &key_Old_Tbl = controller.GetCtl(OLD);
	bool Click[2];
	bool ClickOld[2];
	pos.x = CHIP_SIZE * 2 + Time+lpSpeedMng.GetInstance().GetYellow();	//playerのX座標を動かす
	getcnt[0] = lpSpeedMng.GetInstance().GetYellow();
	for (int i = 0x00; i < MOUSE_INPUT_RIGHT; i++)
	{
		Click[i] = controller.GetClick(i, NOW);
		ClickOld[i] = controller.GetClick(i, OLD);

	}
	MAP_ID id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN]);

	//ショット
	if (Click[MOUSE_INPUT_RIGHT]&(~ClickOld[MOUSE_INPUT_RIGHT]))
	{
		shotFlag = true;
	}
	//ジャンプ
	if (Click[MOUSE_INPUT_LEFT] & (~ClickOld[MOUSE_INPUT_LEFT]))
	{
		
		if (id >= MAP_ID_CLOUD1 && id <= MAP_ID_CLOUD3)
		{

			if (!(jumpFlag&1))//1回目
			{
				jumpFlag += 1;
				SavePos = pos.y;
				time = 0.00f;

			}
		}
		else {
			if (!((jumpFlag)&2))//空中ジャンプ
			{
				time = 0.0;
				jumpFlag+=2;
			}
			
		}
		
	}
	if ((jumpFlag & 1) || ( (jumpFlag) & 2 ))
	{

		pos.y -= JSpeed - time / ADD_SPEED;//ジャンプ処理
		if (JSpeed - time / ADD_SPEED <= 0)
		{
			if (id >= MAP_ID_CLOUD1 && id <= MAP_ID_CLOUD3)
			{
				jumpFlag = 0;
				time = 0.0;
			}
		}


	
	}
	if (controller.WheelCheck(NOW)&~controller.WheelCheck(OLD))
	{
		if (id >= MAP_ID_CLOUD1 && id <= MAP_ID_CLOUD3)
		{
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN] + VECTOR2{0,CHIP_SIZE});
			if (id==MAP_ID_NON||id>=MAP_ID_NON2)
			{
				pos.y += CHIP_SIZE * 1.5;

			}
		}
	}
	if (pos.y > SCREEN_SIZE_Y)
	{
		DeathFlag = true;
	}

	CheckMapHit();
	time += ((id >= MAP_ID_CLOUD1 && id <= MAP_ID_CLOUD3) ? 0.0:1.0);

}



void Player::Draw(void)
{

	DrawGraph(CHIP_SIZE*2, pos.y, IMAGE_ID("image/player.png")[0], true);

	//デバッグ用
	DrawFormatString(0, 0, 0xff00ff, "time:%d", Time);
	DrawFormatString(0, 20, 0x00ffff, "PLAYERの座標\nX...%d\nY...%d\n", pos.x, pos.y);
	DrawFormatString(0, 80, 0xffff, "加算値：%d", Time + lpSpeedMng.GetInstance().GetYellow());
	DrawFormatString(0, 100, 0xffff, "ジャンプ：%d\n2段目:%d",jumpFlag&1,jumpFlag>>1);
	DrawFormatString(0, 140, 0xffff, "MAP_ID：%d", lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN]));
	DrawFormatString(0, 160, 0xffff, "YellowStar：%d",lpSpeedMng.GetInstance().GetYellow());
	DrawFormatString(0, 180, 0xffff, "YellowStar_player：%d", getcnt[0]);




}

void Player::CheckMapHit(void)		//ﾏｯﾌﾟとの当たり判定
{
	MAP_ID id;
	auto get_star = [&](MAP_ID id,DIR_TBL_ID dir) {
	
		if (id == MAP_ID_YELLOW)
		{
			lpSpeedMng.GetInstance().AddStar();
		}
		else {
			getcnt[id - 5]++;
		}
		lpMapControl.GetInstance().SetMapData(pos+DirPos[dir], MAP_ID_NON);
		return true;

	};


	for (int i = 0; i < DIR_MAX; i++)
	{
		id = lpMapControl.GetMapDate(pos+DirPos[i]);
		switch (id)
		{
			//乗る(ジャンプ中だったら判定を行わない)
		case MAP_ID_CLOUD1:
		case MAP_ID_CLOUD2:
		case MAP_ID_CLOUD3:
			if (i == DIR_DOWN)
			{
				if (!(jumpFlag&1))
				{
					if (pos.y%CHIP_SIZE > CHIP_SIZE / 2)
					{
						pos.y = pos.y / CHIP_SIZE * CHIP_SIZE;

					}
				}
				if (DownCheck)
				{
					
				}
			}
			
			break;
			//落ちる

		case MAP_ID_YELLOW:
		case MAP_ID_GREEN:
		case MAP_ID_RED:
			get_star(id, (DIR_TBL_ID)i);
		case MAP_ID_NON:
		case MAP_ID_NON2:
		case MAP_ID_MAX:
			if (i == DIR_DOWN)
			{
				if ((!(jumpFlag & 1)))
				{
					pos.y+=1+time/ADD_SPEED;
				}
			}

			break;
	
		default:
			break;
		}
	}
}
