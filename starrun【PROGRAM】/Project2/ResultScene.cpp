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
	ClickCheckOld = ClickCheck;
	ClickCheck = (GetMouseInput()&MOUSE_INPUT_LEFT ? true : false);
	VECTOR2 Mpos = { 0,0 };
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	GetMousePoint(&Mpos.x, &Mpos.y);
	if ((ClickCheck&(~ClickCheckOld)) && (Mpos > move_title&&Mpos < move_title + VECTOR2{ 320,160 }))
	{
		lpSoundMng.PlaySound("Sound/SE/decision27.mp3", DX_PLAYTYPE_BACK);
		return std::make_unique<TitleScene>();
	}
	if ((ClickCheck&(~ClickCheckOld)) && (Mpos > play_continue&&Mpos < play_continue + VECTOR2{ 320,160 }))
	{
		lpSoundMng.PlaySound("Sound/SE/decision27.mp3", DX_PLAYTYPE_BACK);
		return std::make_unique<GameScene>();
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
	time_digit = 10;

	move_title = { 140, 500 };
	play_continue = { 800, 500 };
	return 0;
}

bool ResultScene::ResultDraw(void)
{
	int time = lpResultCtl.GetLoadTime();
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/back.jpg")[0], false);
	DrawRectGraph(50, 100, 0, 0, 340, 100, IMAGE_ID("image/HIGHSCORE.png")[0], true, false);
	DrawRectGraph(SCORE_IMAGE_POS, 200, 0, 0, 175, 100, IMAGE_ID("image/SCORE.png")[0], true, false);
	DrawRectGraph(TIME_IMAGE_POS, 150, 0, 0, 175, 100, IMAGE_ID("image/play_time.png")[0], true, false);
	DrawGraph(TIME_IMAGE_POS + 155, 200,IMAGE_ID("image/Unit.png")[0], true);

	for (int num = 0; num <= 7; num++)
	{
		if (digit_high != 0)
		{
			digit_high_score[num] = (lpResultCtl.GetLoadScore() / digit_high) % 10;
			digit_high = digit / 10;
		}

		if (digit != 0)
		{
			digit_score[num] = (this->score / digit) % 10;
			digit = digit / 10;
		}
		DrawRectGraph(70 + 340 + 35 * num, 125, 25 * digit_high_score[num], 0, 25, 51, IMAGE_ID("image/num.png")[0], true, false);
		DrawRectGraph(70 + 340 + 35 * num, 220, 25 * digit_score[num], 0, 25, 51, IMAGE_ID("image/num.png")[0], true, false);
	}


	auto Time = [&](int posX, int n, int time) {
		digit_play_time[n][0] = (time / 10) % 10;
		digit_play_time[n][1] = (time / 1) % 10;
		DrawRectGraph(posX, 175, 25 * digit_play_time[n][0], 0, 25, 51, IMAGE_ID("image/num.png")[0], true, false);
		DrawRectGraph(posX + 30, 175, 25 * digit_play_time[n][1], 0, 25, 51, IMAGE_ID("image/num.png")[0], true, false);
	};

		Time((TIME_IMAGE_POS)+155, 0, (this->time / 3600));
		Time(TIME_IMAGE_POS + 250, 1, (this->time / 60 % 60));
		Time(TIME_IMAGE_POS + 345, 2, (this->time % 60));

	DrawGraph(move_title.x, move_title.y, IMAGE_ID("image/TITLEbutton.png")[0], true);
	DrawGraph(play_continue.x, play_continue.y, IMAGE_ID("image/CONTINUEbutton.png")[0], true);
	VECTOR2 Mpos = { 0,0 };
	GetMousePoint(&Mpos.x, &Mpos.y);
	ScreenFlip();
	return true;
}
