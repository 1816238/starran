#include "Dxlib.h"
#include "classObj.h"
#include "GameScene.h"
#include "SceneMng.h"
#include "MapControl.h"
#include "Obj.h"
#include "GameCtl.h"
#include "ImageMng.h"
#include "Player.h"

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

	GameDraw();
	return std::move(own);		//所有権を移す
}

bool GameScene::GameDraw(void)
{
	(*objList).sort([](uniqueObj& obj1, uniqueObj& obj2) {return ((*obj1).GetPos().y < (*obj2).GetPos().y); });
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/back.jpg")[0], true);

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

	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapControl.SetUp(VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	auto obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2{0,0}, lpSceneMng.GetDrawOffset()));

	return 0;
}
