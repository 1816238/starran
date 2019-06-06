#include "DxLib.h"
#include "Obj.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ImageMng.h"
#include "ResultCtl.h"
#include "ResultScene.h"
#include "SoundMng.h"

ResultScene::ResultScene(int play_score,int play_time)
{
	this->score = play_score;
	this->time = play_time;
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
	//叙述【ﾌﾟﾚﾃﾞｨｹｰﾄ】
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeath(); });
	lpResultCtl.ResultLoad(objList, false);
	if (lpResultCtl.GetLoadScore()< this->score)
	{
		lpResultCtl.SetUp(this->score, this->time);
		lpResultCtl.ResultSave(objList);
	}
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
	//lpResultCtl.SetUp(0,0);
	SetWindowText("AGS.exe Result");
	
	lpSoundMng.StopSound(SOUND_METEO);
	for (int num = 0; num <= 7; num++)
	{
		digit_score[num] = 0;
	}

	digit = 10000000;
	digit_high = 10000000;
	return 0;
}

bool ResultScene::ResultDraw(void)
{

	ClsDrawScreen();
	DrawRectGraph(50, 100,0,0,340,100, IMAGE_ID("image/HIGHSCORE.png")[0],true, false);
	DrawRectGraph(50+163/2, 200,0,0,175,100, IMAGE_ID("image/SCORE.png")[0],true, false);

	for (int num = 0; num <= 7; num++)
	{
		if (digit_high != 0 )
		{
			digit_high_score[num] = ( lpResultCtl.GetLoadScore() / digit_high) % 10;
			digit_high = digit / 10;
		}

		if (digit != 0 )
		{
			digit_score[num] = ( this->score / digit) % 10;
			digit = digit / 10;
		}
		DrawRectGraph(50 + 340 + 25 * num, 200, 25 * digit_score[num], 0, 25, 51, IMAGE_ID("image/num.png")[0], true, false);
		DrawRectGraph(50 + 340 + 25 * num, 100, 25 * digit_high_score[num], 0, 25, 51, IMAGE_ID("image/num.png")[0], true, false);
	}

	DrawFormatString(0, 0, 0x00ff00, "ENTERでTitleへ",0);
	DrawFormatString(0, 20, 0x00ff00, "F1でコンテニュー",0);
	DrawFormatString(0, 40, 0x00ff00, "SCORE...%d",lpResultCtl.GetLoadScore());
	int time = lpResultCtl.GetLoadTime();
	DrawFormatString(0, 60, 0x00ff00, "TIME...%d.%d.%d",time/3600,time/60%60,time%60);
	SetFontSize(70);
	DrawString(500, 300, "工事中", 0xffffff);
	SetFontSize(-1);
	ScreenFlip();
	return true;
}
