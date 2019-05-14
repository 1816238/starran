#include "DxLib.h"
#include "Obj.h"
#include "SceneMng.h"
#include "ResultCtl.h"
#include "ResultScene.h"

ResultScene::ResultScene()
{
	Init();
}


ResultScene::~ResultScene()
{
}

unique_Base ResultScene::UpDate(unique_Base own, const GameCtl & controller)
{

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	//叙述【ﾌﾟﾚﾃﾞｨｹｰﾄ】
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeth(); });
	lpResultCtl.ResultLoad(objList, false);
	ResultDraw();
	return std::move(own);		//所有権を移す
}

int ResultScene::Init(void)
{
	if (!objList)//objListの中に何も入ってないと例外が走るので何も入ってない場合はobjListの中に入れる処理を行う
	{
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	lpResultCtl.SetUp(0,0);

	SetWindowText("AGS.exe Result");
	return 0;
}

bool ResultScene::ResultDraw(void)
{
	ClsDrawScreen();
	ScreenFlip();
	return true;
}
