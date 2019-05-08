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
		//ËŞ¯Ä‰‰Z‚ğ‚µ‚Ä~‚ÅËŞ¯Ä‚ğ”½“]‚³‚¹‚é”½“]‚³‚¹‚½î•ñ‚Æ”ä‚×”»’è‚·‚é
	{
		return std::make_unique<GameScene>();
	}
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	//–qyÌßÚÃŞ¨¹°Äz
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeth(); });
	TitleDraw();
	return std::move(own);		//Š—LŒ ‚ğˆÚ‚·
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
	if (!objList)//objList‚Ì’†‚É‰½‚à“ü‚Á‚Ä‚È‚¢‚Æ—áŠO‚ª‘–‚é‚Ì‚Å‰½‚à“ü‚Á‚Ä‚È‚¢ê‡‚ÍobjList‚Ì’†‚É“ü‚ê‚éˆ—‚ğs‚¤
	{
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	SetWindowText("AGS.exe Title");
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapControl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	return 0;
}
