#include<math.h>
#include "Dxlib.h"
#include "time.h"
#include "classObj.h"
#include "SceneMng.h"
#include "MapControl.h"
#include "Obj.h"
#include "GameCtl.h"
#include "ImageMng.h"
#include "Enemy.h"
#include "Player.h"
#include "ResultCtl.h"
#include "ResultScene.h"
#include "SpeedMng.h"
#include "SoundMng.h"
#include "GameScene.h"

GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

unique_Base GameScene::UpDate(unique_Base own, const GameCtl & controller)
{
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	//叙述【ﾌﾟﾚﾃﾞｨｹｰﾄ】
	//(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeth(); });
	for (auto itr = objList->begin(); itr != objList->end(); )
	{
		if ((*itr)->CheckObjType() == TYPE_PLAYER)
		{
			(*itr)->Setdeath(playerPos.deathFlag);
			(*itr)->SetDamageFlag(playerPos.damageFlag, 0);
			if ((*itr)->CheckDeath())
			{
				objList->erase(itr);
				lpResultCtl.SetUp(1000, 10);
				lpResultCtl.ResultSave(objList);
				return std::make_unique<ResultScene>();

			}
			playerPos.pos = VECTOR2{ 64,(*itr)->GetPos().y };	
			itr++;
		}
		else if ((*itr)->CheckObjType() == TYPE_ENEMY_BIT)
		{

		}
		else if ((*itr)->CheckObjType() == TYPE_PLAYER_SHOT || (*itr)->CheckObjType() == TYPE_ENEMY_SHOT|| (*itr)->CheckObjType() == TYPE_METEO)
		{
			if ((*itr)->CheckObjType() == TYPE_PLAYER_SHOT)
			{
			
			}
			else 
			{
				if (circleHit((*itr)->GetPos() + 16, 16, playerPos.pos, VECTOR2{ PLAYER_SIZE_X,PLAYER_SIZE_Y }))
				{
					if (playerPos.damageFlag)
					{
						playerPos.deathFlag = true;
					}
					else {
						playerPos.damageFlag = true;

					}

					(*itr)->Setdeath(true);
				}
			}
			

			if ((*itr)->CheckDeath())
			{
				objList->erase(itr);
				break;
			}
			else { itr++; }
		}
		else {
			itr++;
		}
	}
	SeasonSwitch();
	lpSpeedMng.move();
	GameDraw();

	return std::move(own);		//所有権を移す
}

bool GameScene::circleHit(VECTOR2 CePos, int CeRad, VECTOR2 SquPos, VECTOR2 SquRange)
{
	if (abs(CePos.x - SquPos.x) < CeRad && abs(CePos.y - SquPos.y) < CeRad)					//左上
	{
		return true;
	}
	if (abs(CePos.x - SquPos.x) < CeRad && abs(CePos.y - (SquPos.y+SquRange.y)) < CeRad)	//左下
	{
		return true;
	}
	if (abs(CePos.x - (SquPos.x+SquRange.x)) < CeRad && abs(CePos.y - SquPos.y) < CeRad)	//右上
	{
		return true;
	}	if (abs(CePos.x - SquPos.x) < CeRad && abs(CePos.y - (SquPos.y+SquRange.y)) < CeRad)//右下
	{
		return true;
	}
	return false;
}



bool GameScene::GameDraw(void)
{
	(*objList).sort([](uniqueObj& obj1, uniqueObj& obj2) {return ((*obj1).GetPos().y < (*obj2).GetPos().y); });
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/back.jpg")[0], true);
	lpMapControl.Draw(false);
	for (auto &data : (*objList))
	{
		(*data).Draw();
	}
	for (int i = 0; i < 21; i++)
	{
		DrawLine(0, i*CHIP_SIZE, 1280, i*CHIP_SIZE, 0xffff00);

	}
	//[]() {};		←ラムダ式の一つ→[]{};引数を省略した形
	//std::for_each((*objList).begin(), (*objList).end(), [](std::unique_ptr<Obj>&itr) {itr->Draw(); }/*ラムダ式*/);
	ScreenFlip();
	return false;
}

int GameScene::Init(void)
{
	if (!objList)//objListの中に何も入ってないと例外が走るので何も入ってない場合はobjListの中に入れる処理を行う
	{
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	SetWindowText("AGS.exe Game");

	srand(time(NULL));
	lpSoundMng.StopSound("Sound/BGM/milkyway.mp3");
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapControl.SetUp(VECTOR2(SCREEN_SIZE_X*4, SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	player = AddObjList()(objList, std::make_unique<Player>(VECTOR2(CHIP_SIZE * 2, CHIP_SIZE * 15),TYPE_PLAYER, lpSceneMng.GetDrawOffset()));
	auto obj = AddObjList()(objList, std::make_unique<Enemy>(TYPE_ENEMY));
	(*obj)->init("image/map.png", VECTOR2(32, 32), VECTOR2(4, 2));
	lpMapControl.MapLoad("data/mapdata2.map",objList, false,true);
	lpMapControl.MapLoad("data/submap.map", objList, false, false);
	lpSpeedMng.Init();
	SeasonSwitchFlag = 0;
	pShot_itr = pShotObj.begin();
	playerPos.damageFlag = false;
	playerPos.deathFlag = false;
	return 0;
}
void GameScene::SeasonSwitch(void)
{
	if (lpSpeedMng.GetSeasoonFlag(Main) == SeasonSwitchFlag)
	{
		switch (SeasonSwitchFlag)
		{
		case 0:
			lpMapControl.MapLoad("data/mapdata1.map", objList, false, true);
			SeasonSwitchFlag++;
				break;
		case 1:
			lpMapControl.MapLoad("data/mapdata2.map", objList, false, true);
			SeasonSwitchFlag++;
			break;
		case 2:
			break;
		case 3:

			break;
		case 4:
			break;
		default:
			break;
		}
	}
}
