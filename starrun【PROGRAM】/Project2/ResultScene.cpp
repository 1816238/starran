#include "DxLib.h"
#include "Obj.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
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

	if (CheckHitKey(KEY_INPUT_F1) == 1)
	{
		return std::make_unique<GameScene>();
	}

	if (CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		return std::make_unique<TitleScene>();
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
	DrawFormatString(0, 0, 0x00ff00, "ENTER��Title��",0);
	DrawFormatString(0, 20, 0x00ff00, "F1�ŃR���e�j���[",0);
	DrawFormatString(0, 40, 0x00ff00, "SCORE...%d",lpResultCtl.GetLoadScoreData());
	DrawFormatString(0, 60, 0x00ff00, "TIME...%d",lpResultCtl.GetLoadTimeData());
	ScreenFlip();
	return true;
}
