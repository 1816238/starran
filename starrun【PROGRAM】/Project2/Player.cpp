#include <array>
#include <functional>
#include <math.h>
#include <DxLib.h>
#include "SceneMng.h"
#include "MapControl.h"
#include "GameCtl.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "SpeedMng.h"
#include "Shot.h"
#include "Effect.h"
#include "SoundMng.h"
#include "Enemy.h"
#include "Player.h"

Player::Player(VECTOR2 setUpPos,OBJ_TYPE objType, VECTOR2 drawOffset) :Obj(drawOffset)
{

	/*MAIN*/

	initAnim();
	this->objType = objType;
	pos = setUpPos;
	Obj::init("image/player.png", VECTOR2(PLAYER_SIZE_X, PLAYER_SIZE_Y), VECTOR2(2, 1), setUpPos);	
	Sound_ID("Sound/SE/pshot.mp3")[0];
	init();
}

Player::Player()
{
}

Player::~Player() 
{
	OutputDebugString("player消えたよ\n");

};

bool Player::initAnim(void)
{
	//AddAnim("通常", 0, 0, 1, 1, true);
	return true;
}



bool Player::init(void)
{
	for (int a = 0; a < 100; a++)
	{
		shotFlag[a] = true;
	}
	jumpFlag = false;
	DownCheck = false;
	EndFlag = false;
	damageFlag = false;
	JSpeed = 8;
	shotcnt = 100;

	keyID_Tbl = { MOUSE_INPUT_LEFT,//左
				  MOUSE_INPUT_RIGHT,//右
				  MOUSE_ROT_VOL		//ﾎｲｰﾙ回転量
				  };

	for (int i = 1; i < 4; i++)
	{
		getcnt[i] = 0;

	}
	getcnt[0] = 100;
	meter_name[0] = "image/blumeter.png";
	meter_name[1] = "image/grnmeter.png";
	meter_name[2] = "image/redmeter.png";
	meter_name[3] = "image/yelmeter.png";
	DirPos = {	VECTOR2{ PLAYER_SIZE_X-1,1},				// 上
				VECTOR2{PLAYER_SIZE_X/2,PLAYER_SIZE_Y},		// 下
				VECTOR2{1,PLAYER_SIZE_Y/2},					// 左
				VECTOR2{PLAYER_SIZE_X-1,PLAYER_SIZE_Y/2},	// 右
			};

	CheckFlag = {
	//Jump,Down,
	0b01,			//MAP_ID_NON,
	0b11,			//MAP_ID_CLOUD1,
	0b11,			//MAP_ID_CLOUD2,
	0b11,			//MAP_ID_CLOUD3,
	0b01,			//MAP_ID_BLUE,
	0b01,			//MAP_ID_YELLOW,
	0b01,			//MAP_ID_GREEN,
	0b01,			//MAP_ID_RED,
	0b01,			//MAP_ID_PURPLE,
	0b10,			//MAP_ID_CLOUD_DOWN1,
	0b10,			//MAP_ID_CLOUD_DOWN2,
	0b10,			//MAP_ID_CLOUD_DOWN3,
	0b01,			//MAP_ID_FULL_MOON,
	0b01,			//MAP_ID_HALF_MOON,
	0b01			//MAP_ID_CRESCENT_MOON,
	};
	Score = 0;
	ScoreTbl = {
	0,			//MAP_ID_NON,
	0,			//MAP_ID_CLOUD1,
	0,			//MAP_ID_CLOUD2,
	0,			//MAP_ID_CLOUD3,
	10,			//MAP_ID_BLUE,
	10,			//MAP_ID_YELLOW,
	10,			//MAP_ID_GREEN,
	10,			//MAP_ID_RED,
	-100,			//MAP_ID_PURPLE,
	0,			//MAP_ID_CLOUD_DOWN1,
	0,			//MAP_ID_CLOUD_DOWN2,
	0,			//MAP_ID_CLOUD_DOWN3,
	1000,		//MAP_ID_FULL_MOON,
	500,		//MAP_ID_HALF_MOON,
	250			//MAP_ID_CRESCENT_MOON,
	};

	OutputDebugString("player初期化したよ\n");

	return false;
}

OBJ_TYPE Player::CheckObjType(void)
{
	return objType;
}


void Player::SetMove(const GameCtl & controller, weekListObj objList)
{
	auto &key_Tbl = controller.GetCtl(NOW);
	auto &key_Old_Tbl = controller.GetCtl(OLD);
	bool Click[2];
	bool ClickOld[2];
	MAP_ID id=MAP_ID_NON;
	SEASON season = lpSpeedMng.GetSeason();
	if (season == SEASON::MAX)
	{
		if (lpSpeedMng.GetFlag(Sub))
		{
			pos.x = Speed(Sub) - CHIP_SIZE;
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Sub);
		}
		else if(lpSpeedMng.GetFlag(Sub2)) {
			pos.x = Speed(Sub2) - CHIP_SIZE;
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Sub2);
		}
	}
	else {
		pos.x = lpSpeedMng.GetSpeed(Main,season) - CHIP_SIZE;
		id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main,season);
	}
	//playerのX座標を動かす
	/*if (lpSpeedMng.GetFlag(Main)&lpSpeedMng.GetFlag(Sub) == 1)
	{
		if (Speed(Main,SEASON::SPRING) < 0)
		{
			pos.x = Speed(Sub) - CHIP_SIZE;
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Sub);
		}
		else if (Speed(Sub) < 0)
		{
			pos.x = lpSpeedMng.GetSpeed(Main,SEASON::SPRING)-CHIP_SIZE;
			id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main);
		}
		else {
			pos.x = lpSpeedMng.GetSpeed(Main) - CHIP_SIZE;
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
*/
	for (int i = 0x00; i < MOUSE_INPUT_RIGHT; i++)
	{
		Click[i] = controller.GetClick(i+1, NOW);
		ClickOld[i] = controller.GetClick(i+1, OLD);
	}
	//MAP_ID id = lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN],Main);

	//ショット
	if (Click[1] & (~ClickOld[1]))
	{
		if (getcnt[0] > 0)
		{
		
			AddObjList()(objList, std::make_unique<Shot>(VECTOR2{ CHIP_SIZE * 3,pos.y }, VECTOR2(CHIP_SIZE * 2, 0), TYPE_PLAYER_SHOT, getcnt[0],getcnt[2]));
			getcnt[0]--;
			lpSoundMng.PlaySound("Sound/SE/pshot.mp3", DX_PLAYTYPE_BACK);
		}
	
		
	}


	//ジャンプ
	if (Click[0] & (~ClickOld[0]))
	{

		if (CheckFlag[id] >> static_cast<int>(MAP_FLAG_TYPE::JUMP))
		{

			if (!(jumpFlag & 1))//1回目
			{
				jumpFlag += 1;

				time["ｼﾞｬﾝﾌﾟ"] = 0.00f;
				lpSoundMng.PlaySound("Sound/SE/jump.mp3", DX_PLAYTYPE_BACK);
			}
		}
		else {
			if (!((jumpFlag) & 2))//空中ジャンプ
			{
				time["ｼﾞｬﾝﾌﾟ"] = 0.0;
				jumpFlag += 2;
				lpSoundMng.PlaySound("Sound/SE/jump.mp3", DX_PLAYTYPE_BACK);

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
				lpSoundMng.PlaySound("Sound/SE/Landing.mp3", DX_PLAYTYPE_BACK);
			}
		}



	}
	//降りる
	if (controller.WheelCheck(NOW)&~controller.WheelCheck(OLD))
	{
		if (!((CheckFlag[id]>>static_cast<int> (MAP_FLAG_TYPE::DOWN))&1))
		{
				pos.y += CHIP_SIZE * 1.5;
		}
	}
	if (pos.y > SCREEN_SIZE_Y)
	{
		Obj::SetEnd(true);
	}
	if (damageFlag)
	{
		if (time["ﾀﾞﾒｰｼﾞ"] >= 180)
		{
			damageFlag = false;
			time["ﾀﾞﾒｰｼﾞ"] = 0;
		}
	}
	CheckMapHit(season);
	time["ｼﾞｬﾝﾌﾟ"] += (CheckFlag[id]>>static_cast<int>(MAP_FLAG_TYPE::JUMP) ? 0.0 : 1.0);
	time["ﾀﾞﾒｰｼﾞ"] += (damageFlag ? 1 : 0);
}




void Player::Draw(void)
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, !(time["ﾀﾞﾒｰｼﾞ"] / 10 % 2) * 255);
	DrawGraph(CHIP_SIZE * 2, pos.y, IMAGE_ID("image/player.png",)[time["ﾀﾞﾒｰｼﾞ"] / 10%2], true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int i = 0; i < 4; i++)
	{
		double star = getcnt[i] % 15;
		double tmp = (i != 0 ? star / 15.0 * 100:static_cast<double>(getcnt[0])/100.0*100.0);

		DrawCircleGauge(i*CHIP_SIZE*3 +48, 48,tmp, IMAGE_ID(meter_name[i])[0],0.0);
		DrawCircle(i*CHIP_SIZE * 3 + 48, 48, 48, 0xffffff, false);

		(i!=0?DrawFormatString(i*CHIP_SIZE*3+10, 48, 0x000000, "Level.%d", getcnt[i] / 15): DrawFormatString(i*CHIP_SIZE * 3 + 10, 48, 0x000000, "残り%d発", getcnt[i]));
	}

	//デバッグ用	
	/*DrawBox(64+14,pos.y,64+PLAYER_SIZE_X, pos.y + PLAYER_SIZE_Y, 0x0000ff, false);
	DrawFormatString(0, 0, 0xff00ff, "time(main,sub,std):%d,%d,%d", Speed(Main), Speed(Sub), Speed(Std));
	DrawFormatString(0, 20, 0x00ffff, "PLAYERの座標\nX...%d\nY...%d\n", pos.x, pos.y);
	DrawFormatString(0, 80, 0xffff, "加算値：%d", Speed(Main) + lpSpeedMng.GetYellow());
	DrawFormatString(0, 100, 0xffff, "ジャンプ：%d\n2段目:%d,time%d", jumpFlag & 1, jumpFlag >> 1,time["ｼﾞｬﾝﾌﾟ"]);
	DrawFormatString(0, 140, 0xffff, "MAP_ID：%d　\nMAP_ID(sub):%d", lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Main), lpMapControl.GetMapDate(pos + DirPos[DIR_TBL_DOWN], Sub));
	DrawFormatString(0, 180, 0xffff, "YellowStar_player：%d", lpSpeedMng.GetYellow());
	DrawFormatString(0, 200, 0xffff, "subFlag：%d", lpMapControl.GetSubFlag());
	DrawFormatString(0, 220, 0xffff, "SpeedFlag(main,sub):%d,%d", lpSpeedMng.GetFlag(Main), lpSpeedMng.GetFlag(Sub));
	DrawFormatString(0, 240, 0xffff, "star:青%d,緑%d,赤%d", getcnt[0], getcnt[1], getcnt[2]);
	DrawFormatString(0, 280, 0xffff, "残弾:%d",shotcnt );*/

	DrawFormatString(0, 100, 0xffffff, "%d", lpSpeedMng.GetSpeed(MapType::Std));


}

void Player::CheckMapHit(SEASON season)		//ﾏｯﾌﾟとの当たり判定
{
	MAP_ID id;
	bool mainflag = lpSpeedMng.GetFlag(Main);
	bool subflag = lpSpeedMng.GetFlag(Sub)||lpSpeedMng.GetFlag(Sub2);
	
	MapType type;



	auto get_star = [&](MAP_ID id, DIR_TBL_ID dir) {


		switch (id)
		{

		case MAP_ID_BLUE:			//残弾回復
			getcnt[0]++;
			getcnt[0] = (getcnt[0] > 100 ? 100 : getcnt[0]);
			lpSoundMng.PlaySound("Sound/SE/get.mp3", DX_PLAYTYPE_BACK);

			break;
		case MAP_ID_YELLOW:			//ｽﾋﾟｰﾄﾞｱｯﾌﾟ
			lpSpeedMng.AddStar();
			getcnt[3]++;
			lpSoundMng.PlaySound("Sound/SE/get.mp3", DX_PLAYTYPE_BACK);

			break;
		case MAP_ID_GREEN:			//弾のｽﾋﾟｰﾄﾞｱｯﾌﾟ
			getcnt[1]++;
			lpSoundMng.PlaySound("Sound/SE/get.mp3", DX_PLAYTYPE_BACK);

			break;
		case MAP_ID_RED:			//攻撃力ｱｯﾌﾟ
			getcnt[2]++;
			lpSoundMng.PlaySound("Sound/SE/get.mp3", DX_PLAYTYPE_BACK);

			break;
		case MAP_ID_PURPLE:			//ﾀﾞﾒｰｼﾞ
			if (!damageFlag)
			{
				damageFlag = true;
				time["ﾀﾞﾒｰｼﾞ"] = 0;
				lpSoundMng.PlaySound("Sound/SE/stardamage.mp3", DX_PLAYTYPE_BACK);
				lpEffect.SetEffectFlag(SHAKE,true);

			}
			else {
				SetEnd(true);
			}
			break;
		case MAP_ID_FULL_MOON:
		case MAP_ID_HALF_MOON:
		case MAP_ID_CRESCENT_MOON:
			lpSoundMng.PlaySound("Sound/SE/getmoon.mp3", DX_PLAYTYPE_BACK);
			break;
		default:
		case MAP_ID_NON:
		case MAP_ID_CLOUD1:
		case MAP_ID_CLOUD2:
		case MAP_ID_CLOUD3:
		case MAP_ID_CLOUD_DOWN1:
		case MAP_ID_CLOUD_DOWN2:
		case MAP_ID_CLOUD_DOWN3:

		case MAP_ID_MAX:

			return false;
			break;
		}
		Score += ScoreTbl[id]; 
		lpMapControl.SetMapData(pos + DirPos[dir], MAP_ID_NON, type,season);
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
		case MAP_ID_FULL_MOON:
		case MAP_ID_HALF_MOON:
		case MAP_ID_CRESCENT_MOON:
			get_star(id, (DIR_TBL_ID)dir);
			if (dir == DIR_DOWN)
			{
				if (!(jumpFlag & 0b11))
				{
					pos.y += 5;
				}
			}
			break;

		case MAP_ID_NON:

			if (dir == DIR_DOWN)
			{
				if (!(jumpFlag & 0b11))
				{
					pos.y += 5;
				}
			}

			break;
		case MAP_ID_MAX:
			break;
		default:
			break;
		}

	};


	if (season == SEASON::MAX)
	{
		if (lpSpeedMng.GetFlag(Sub))
		{
			type = Sub;
		}
		else if(lpSpeedMng.GetFlag(Sub2)){
		
			type = Sub2;
		}
		else {
			type = Main;
		}

	}
	else {
		type = Main;
	}
	for (int i = 0; i < DIR_TBL_MAX; i++)
	{

		id = lpMapControl.GetMapDate(pos + DirPos[i], type,season);


		if (id == MAP_ID_MAX)
		{
			id = lpMapControl.GetMapDate(pos + DirPos[i], type,season);
			if (id == MAP_ID_MAX)
			{
				id = lpMapControl.GetMapDate(pos + DirPos[i], type,season);

			}

		}


		CheckHit(id, type, DIR_TBL_ID(i));
	}




}
