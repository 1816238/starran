#include <array>
#include <functional>
#include <math.h>
#include <DxLib.h>
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
	Obj::init("image/player.png", VECTOR2(PLAYER_SIZE_X, PLAYER_SIZE_Y), VECTOR2(1, 1), setUpPos);		
	jumpFlag = false;
	DownCheck = false;
	SavePos = 0;
	DirPos = {	VECTOR2{ PLAYER_SIZE_X-1,1},				// 上
				VECTOR2{PLAYER_SIZE_X/2,PLAYER_SIZE_Y},		// 下
				VECTOR2{1,PLAYER_SIZE_Y/2},					// 左
				VECTOR2{PLAYER_SIZE_X-1,PLAYER_SIZE_Y/2},	// 右
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
	//playerのX座標を動かす
	if (lpSpeedMng.GetFlag(Main))
	{
		pos.x = CHIP_SIZE * 2 + Speed(Main);
	}
	else if (lpSpeedMng.GetFlag(Sub))
	{
		pos.x = CHIP_SIZE * 2 + Speed(Sub);

	}
	else {}
	getcnt[0] = lpSpeedMng.GetYellow();
	for (int i = 0x00; i < MOUSE_INPUT_RIGHT; i++)
	{
		Click[i] = controller.GetClick(i, NOW);
		ClickOld[i] = controller.GetClick(i, OLD);
	}
	MAP_ID id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN],true);

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
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN] + VECTOR2{0,CHIP_SIZE},true);
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
	DrawFormatString(0, 0, 0xff00ff, "time:%d", Speed(Main));
	DrawFormatString(0, 20, 0x00ffff, "PLAYERの座標\nX...%d\nY...%d\n", pos.x, pos.y);
	DrawFormatString(0, 80, 0xffff, "加算値：%d", Speed(Main) + lpSpeedMng.GetYellow());
	DrawFormatString(0, 100, 0xffff, "ジャンプ：%d\n2段目:%d",jumpFlag&1,jumpFlag>>1);
	DrawFormatString(0, 140, 0xffff, "MAP_ID：%d　MAP_ID(sub):%d", lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN],true), lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], false));
	DrawFormatString(0, 180, 0xffff, "YellowStar_player：%d", getcnt[0]);
	DrawFormatString(0, 200, 0xffff, "subFlag：%d", lpMapControl.GetSubFlag());
	DrawFormatString(0, 220, 0xffff, "SpeedFlag(main,sub):%d,%d", lpSpeedMng.GetFlag(Main), lpSpeedMng.GetFlag(Sub));



}

void Player::CheckMapHit(void)		//ﾏｯﾌﾟとの当たり判定
{
	MAP_ID id;
	bool subflag = lpMapControl.GetSubFlag();
	MAP_ID tmpIdM = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main);
	MAP_ID tmpIdS = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Sub);



	auto get_star = [&](MAP_ID id,DIR_TBL_ID dir) {
	
		if (id == MAP_ID_YELLOW)
		{
			lpSpeedMng.AddStar();
		}
		else {
			getcnt[id - 5]++;
		}
		lpMapControl.SetMapData(pos+DirPos[dir], MAP_ID_NON,!subflag);
		return true;

	};
	auto CheckHit = [&](MAP_ID id,MapType type,DIR_TBL_ID dir) {
	
		if (lpSpeedMng.GetFlag(MapType(!type)))
		{
			switch (id)
			{
				//乗る(ジャンプ中だったら判定を行わない)
			case MAP_ID_CLOUD1:
			case MAP_ID_CLOUD2:
			case MAP_ID_CLOUD3:
				if (dir == DIR_TBL_DOWN)
				{
					if (!(jumpFlag & 1))
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
				get_star(id, (DIR_TBL_ID)dir);
			case MAP_ID_NON:
			case MAP_ID_NON2:

				if (dir == DIR_DOWN)
				{
					if ((!(jumpFlag & 1)))
					{
						pos.y += 1 + time / ADD_SPEED;
					}
				}

				break;
			case MAP_ID_MAX:
			default:
				DeathFlag = true;
				break;
			}
		}
	};


	for (int i = 0; i < DIR_TBL_MAX; i++)
	{
		for (int s = 0; s < 2; s++)
		{
			if (i == DIR_TBL_DOWN)
			{
				if (tmpIdM&&tmpIdS)
				{
					id = lpMapControl.GetMapDate(pos + DirPos[i], s);


				}
				else if ((tmpIdM >= MAP_ID_CLOUD1 && tmpIdM <= MAP_ID_CLOUD3 ))
				{
					id = lpMapControl.GetMapDate(pos + DirPos[i], Main);

				}
				else if ((tmpIdS >= MAP_ID_CLOUD1 && tmpIdS <= MAP_ID_CLOUD3))
				{
					id = lpMapControl.GetMapDate(pos + DirPos[i], Sub);
				}
				else {
					id = lpMapControl.GetMapDate(pos + DirPos[i], s);
				}
			}
			else {
				id = lpMapControl.GetMapDate(pos + DirPos[i], s);

			}
			CheckHit(id, MapType(s), DIR_TBL_ID(i));
		}
	}
	
}
