#include "DxLib.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "SceneMng.h"
#include "MapControl.h"
#include "GameCtl.h"
#include "TitleScene.h"



TitleScene::TitleScene()
{
	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::UpDate(unique_Base own, const GameCtl & controller)
{
	if (controller.GetCtl(KEY_TYPE::NOW)[KEY_INPUT_SPACE]
		& (~controller.GetCtl(KEY_TYPE::OLD)[KEY_INPUT_SPACE]))
		//�ޯĉ��Z������~���ޯĂ𔽓]�����锽�]���������Ɣ�ה��肷��
	{
		return std::make_unique<GameScene>();
	}
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	//���q�y����ި��āz
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeth(); });
	TitleDraw();
	return std::move(own);		//���L�����ڂ�
}

bool TitleScene::TitleDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/backImage.png")[0], true);
	ScreenFlip();
	return false;
}

int TitleScene::Init(void)
{
	if (!objList)//objList�̒��ɉ��������ĂȂ��Ɨ�O������̂ŉ��������ĂȂ��ꍇ��objList�̒��ɓ���鏈�����s��
	{
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	SetWindowText("AGS.exe Title");
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapControl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	return 0;
}
