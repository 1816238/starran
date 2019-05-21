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
#include "Shot.h"

Player::Player(VECTOR2 setUpPos, VECTOR2 drawOffset) :Obj(drawOffset)
{



	/*MAIN*/

	initAnim();

	pos = setUpPos;
	Obj::init("image/player_W.png", VECTOR2(PLAYER_SIZE_X, PLAYER_SIZE_Y), VECTOR2(1, 1), setUpPos);	

	Init();
}

Player::Player()
{
}

Player::~Player() = default;

bool Player::initAnim(void)
{
	//AddAnim("通常", 0, 0, 1, 1, true);
	return true;
}

const bool Player::GetDeathFlag(void)
{
	return DeathFlag;
}

bool Player::Init(void)
{
	shotFlag = true;
	jumpFlag = false;
	DownCheck = false;
	DeathFlag = false;
	damageFlag = true;
	JSpeed = 3;
	keyID_Tbl = { MOUSE_INPUT_LEFT,//左
				  MOUSE_INPUT_RIGHT,//右
				  MOUSE_ROT_VOL		//ﾎｲｰﾙ回転量
				  };

	for (int i = 0; i < 4; i++)
	{
		getcnt[i] = 0;

	}
	DirPos = {	VECTOR2{ PLAYER_SIZE_X-1,1},				// 上
				VECTOR2{PLAYER_SIZE_X/2,PLAYER_SIZE_Y},		// 下
				VECTOR2{1,PLAYER_SIZE_Y/2},					// 左
				VECTOR2{PLAYER_SIZE_X-1,PLAYER_SIZE_Y/2},	// 右
			};

	CheckFlag = {
	//Jump,Down,
	0b01,			//MAP_ID_NON,
	0b10,			//MAP_ID_CLOUD1,
	0b10,			//MAP_ID_CLOUD2,
	0b10,			//MAP_ID_CLOUD3,
	0b01,			//MAP_ID_BLUE,
	0b01,			//MAP_ID_YELLOW,
	0b01,			//MAP_ID_GREEN,
	0b01,			//MAP_ID_RED,
	0b01,			//MAP_ID_PURPLE,
	0b11,			//MAP_ID_CLOUD_DOWN1,
	0b11,			//MAP_ID_CLOUD_DOWN2,
	0b11			//MAP_ID_CLOUD_DOWN3,
	};
	
	return false;
}


void Player::SetMove(const GameCtl & controller, weekListObj objList)
{
	auto &key_Tbl = controller.GetCtl(NOW);
	auto &key_Old_Tbl = controller.GetCtl(OLD);
	bool Click[2];
	bool ClickOld[2];
	MAP_ID id;
	//playerのX座標を動かす
	if (lpSpeedMng.GetFlag(Main)&lpSpeedMng.GetFlag(Sub) == 1)
	{
		if (Speed(Main) < 0)
		{
			pos.x = Speed(Sub) - CHIP_SIZE;
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Sub);
		}
		else if (Speed(Sub) < 0)
		{
			pos.x = Speed(Main) - CHIP_SIZE;
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main);
		}
		else {
			pos.x = Speed(Main) - CHIP_SIZE;
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main);
		}
	}
	else if (lpSpeedMng.GetFlag(Sub))
	{
		pos.x = Speed(Sub) - CHIP_SIZE;
		id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Sub);
	}
	else if (lpSpeedMng.GetFlag(Main))
	{
		pos.x = Speed(Main) - CHIP_SIZE;
		id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main);

	}
	else { id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main); }

	for (int i = 0x00; i < MOUSE_INPUT_RIGHT; i++)
	{
		Click[i] = controller.GetClick(i, NOW);
		ClickOld[i] = controller.GetClick(i, OLD);
	}
	//MAP_ID id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN],Main);

	//ショット
	//if (Click[MOUSE_INPUT_RIGHT]/* & (~ClickOld[MOUSE_INPUT_RIGHT])*/)
	//{
	//	shotFlag = false;
	//	auto shot=&AddObjList()(objList, std::make_unique<Shot>(pos, VECTOR2(CHIP_SIZE * 2, CHIP_SIZE * 15),true));
	//}
	//ジャンプ
	if (Click[MOUSE_INPUT_LEFT] & (~ClickOld[MOUSE_INPUT_LEFT]))
	{

		if (CheckFlag[id] >> static_cast<int>(MAP_FLAG_TYPE::JUMP))
		{

			if (!(jumpFlag & 1))//1回目
			{
				jumpFlag += 1;

				time["ｼﾞｬﾝﾌﾟ"] = 0.00f;

			}
		}
		else {
			if (!((jumpFlag) & 2))//空中ジャンプ
			{
				time["ｼﾞｬﾝﾌﾟ"] = 0.0;
				jumpFlag += 2;
			}

		}

	}
	if ((jumpFlag & 0b01) || ((jumpFlag) & 0b10))
	{

		pos.y -= JSpeed - time["ｼﾞｬﾝﾌﾟ"] / ADD_SPEED;//ジャンプ処理
		//pos.y -= time["ｼﾞｬﾝﾌﾟ"] / 2 * CHIP_SIZE;
		if ((JSpeed - time["ｼﾞｬﾝﾌﾟ"] / ADD_SPEED)<=0)
		{
			if ((CheckFlag[id] >> static_cast<int> (MAP_FLAG_TYPE::JUMP)))
			{
				jumpFlag = 0;
				time["ｼﾞｬﾝﾌﾟ"] = 0.0;
			}
		}



	}
	//降りる
	if (controller.WheelCheck(NOW)&~controller.WheelCheck(OLD))
	{
		if (!(CheckFlag[id]>>static_cast<int> (MAP_FLAG_TYPE::DOWN)))
		{
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN] + VECTOR2{ 0,CHIP_SIZE }, Main);
			if (id == MAP_ID_NON || id >= MAP_ID_BLUE)
			{
				pos.y += CHIP_SIZE * 1.5;

			}
		}
	}
	if (pos.y > SCREEN_SIZE_Y)
	{
		DeathFlag = true;
	}
	if (damageFlag)
	{
		if (time["ﾀﾞﾒｰｼﾞ"] >= 180)
		{
			damageFlag = false;
		}
	}
	CheckMapHit();
	time["ｼﾞｬﾝﾌﾟ"] += (CheckFlag[id]>>static_cast<int>(MAP_FLAG_TYPE::JUMP) ? 0.0 : 1.0);
	time["ﾀﾞﾒｰｼﾞ"] += (damageFlag ? 1 : 0);
}




void Player::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, !(time["ﾀﾞﾒｰｼﾞ"] / 10 % 2) * 255);
	DrawGraph(CHIP_SIZE * 2, pos.y, IMAGE_ID("image/player_W.png")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//デバッグ用
	DrawFormatString(0, 0, 0xff00ff, "time(main,sub,std):%d,%d,%d", Speed(Main), Speed(Sub), Speed(Std));
	DrawFormatString(0, 20, 0x00ffff, "PLAYERの座標\nX...%d\nY...%d\n", pos.x, pos.y);
	DrawFormatString(0, 80, 0xffff, "加算値：%d", Speed(Main) + lpSpeedMng.GetYellow());
	DrawFormatString(0, 100, 0xffff, "ジャンプ：%d\n2段目:%d,time%d", jumpFlag & 1, jumpFlag >> 1,time["ｼﾞｬﾝﾌﾟ"]);
	DrawFormatString(0, 140, 0xffff, "MAP_ID：%d　\nMAP_ID(sub):%d", lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main), lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Sub));
	DrawFormatString(0, 180, 0xffff, "YellowStar_player：%d", lpSpeedMng.GetYellow());
	DrawFormatString(0, 200, 0xffff, "subFlag：%d", lpMapControl.GetSubFlag());
	DrawFormatString(0, 220, 0xffff, "SpeedFlag(main,sub):%d,%d", lpSpeedMng.GetFlag(Main), lpSpeedMng.GetFlag(Sub));



}

void Player::CheckMapHit(void)		//ﾏｯﾌﾟとの当たり判定
{
	MAP_ID id;
	bool mainflag = lpSpeedMng.GetFlag(Main);
	bool subflag = lpSpeedMng.GetFlag(Sub);

	MapType type;



	auto get_star = [&](MAP_ID id, DIR_TBL_ID dir) {


		switch (id)
		{

		case MAP_ID_BLUE:			//弾のｽﾋﾟｰﾄﾞｱｯﾌﾟ
			getcnt[0]++;
			break;
		case MAP_ID_YELLOW:			//ｽﾋﾟｰﾄﾞｱｯﾌﾟ
			lpSpeedMng.AddStar();
			break;
		case MAP_ID_GREEN:			//
			getcnt[1]++;
			break;
		case MAP_ID_RED:			//攻撃力ｱｯﾌﾟ
			getcnt[2]++;
			break;
		case MAP_ID_PURPLE:			//ﾀﾞﾒｰｼﾞ
			if (!damageFlag)
			{
				damageFlag = true;
				time["ﾀﾞﾒｰｼﾞ"] = 0;
			}
			else {
				DeathFlag = true;
			}
			break;
		case MAP_ID_NON:
		case MAP_ID_CLOUD1:
		case MAP_ID_CLOUD2:
		case MAP_ID_CLOUD3:
		case MAP_ID_CLOUD_DOWN1:
		case MAP_ID_CLOUD_DOWN2:
		case MAP_ID_CLOUD_DOWN3:
		case MAP_ID_MAX:
		default:
			return false;
			break;
		}

		lpMapControl.SetMapData(pos + DirPos[dir], MAP_ID_NON, type);
		return true;

	};
	auto CheckHit = [&](MAP_ID id, MapType type, DIR_TBL_ID dir) {


		switch (id)
		{
			//乗る(ジャンプ中だったら判定を行わない)
		case MAP_ID_CLOUD1:
		case MAP_ID_CLOUD2:
		case MAP_ID_CLOUD3:
		case MAP_ID_CLOUD_DOWN1:
		case MAP_ID_CLOUD_DOWN2:
		case MAP_ID_CLOUD_DOWN3:
			if (dir == DIR_TBL_DOWN)
			{
				if (!(jumpFlag & 0b11))
				{
					if (pos.y%CHIP_SIZE > CHIP_SIZE / 2)
					{
						pos.y = pos.y / CHIP_SIZE * CHIP_SIZE;

					}
				}
			}
			break;
			//落ちる

		case MAP_ID_YELLOW:
		case MAP_ID_GREEN:
		case MAP_ID_RED:
		case MAP_ID_BLUE:
		case MAP_ID_PURPLE:
			get_star(id, (DIR_TBL_ID)dir);
			if (dir == DIR_DOWN)
			{
				if ((!(jumpFlag & 1)))
				{
					pos.y += 1 + time["ｼﾞｬﾝﾌﾟ"] / ADD_SPEED;
				}
			}
			break;

		case MAP_ID_NON:

			if (dir == DIR_DOWN)
			{
				if ((!(jumpFlag & 1)))
				{
					pos.y += 1 + time["ｼﾞｬﾝﾌﾟ"] / ADD_SPEED;
				}
			}

			break;
		case MAP_ID_MAX:
			break;
		default:
			DeathFlag = true;
			break;
		}

	};


	if (mainflag&&subflag)
	{
		if (Speed(Main) < 0)
		{
			type = Sub;
		}
		else if (Speed(Sub) < 0)
		{
			type = Main;

		}
		else {

		}

	}
	else if (mainflag) {
		type = Main;
	}
	else if (subflag)
	{
		type = Sub;
	}
	else {}
	for (int i = 0; i < DIR_TBL_MAX; i++)
	{

		id = lpMapControl.GetMapDate(pos + DirPos[i], type);


		if (id == MAP_ID_MAX)
		{
			id = lpMapControl.GetMapDate(pos + DirPos[i], type);
			if (id == MAP_ID_MAX)
			{
				id = lpMapControl.GetMapDate(pos + DirPos[i], type);

			}

		}


		CheckHit(id, type, DIR_TBL_ID(i));
	}




}
