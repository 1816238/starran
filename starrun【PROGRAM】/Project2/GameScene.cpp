#include "time.h"
#include "Dxlib.h"
#include "classObj.h"
#include "GameScene.h"
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
GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

unique_Base GameScene::UpDate(unique_Base own, const GameCtl & controller)
{
	if(CheckHitKey(KEY_INPUT_P)==1)
	{ 
		lpResultCtl.ResultSave(objList);
		return std::make_unique<ResultScene>();
	}
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	//叙述【ﾌﾟﾚﾃﾞｨｹｰﾄ】
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeth(); });
	/*for (auto itr = objList->begin(); itr != objList->end(); )
	{
		if ((*itr)->CheckDeth())
		{
			objList->erase(itr);
		}
		else
		{
			itr++;
		}
	}*/
	lpSpeedMng.move();

	GameDraw();
	return std::move(own);		//所有権を移す
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

	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapControl.SetUp(VECTOR2(SCREEN_SIZE_X*4, SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	auto obj = AddObjList()(objList, std::make_unique<Enemy>());
	(*obj)->init("image/map.png", VECTOR2(32, 32), VECTOR2(4, 2));
	lpMapControl.MapLoad("data/mapdata2.map",objList, false,true);
	lpMapControl.MapLoad("data/submap.map", objList, false, false);


	return 0;
}
