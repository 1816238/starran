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
	//���q�y����ި��āz
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeth(); });
	lpResultCtl.ResultLoad(objList, false);
	ResultDraw();
	return std::move(own);		//���L�����ڂ�
}

int ResultScene::Init(void)
{
	if (!objList)//objList�̒��ɉ��������ĂȂ��Ɨ�O������̂ŉ��������ĂȂ��ꍇ��objList�̒��ɓ���鏈�����s��
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
