#include "DxLib.h"
#include "Obj.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "ImageMng.h"
#include "ResultCtl.h"
#include "ResultScene.h"
#include "SoundMng.h"

ResultScene::ResultScene(int play_score,int play_time,Parameter param)
{
	this->score = play_score + param.Bonus + play_time/ param.Bonus;
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
	if ((ClickCheck&(~ClickCheckOld)) && (Mpos > move_title&&Mpos < move_title + title_size))
	{
		lpSoundMng.PlaySound("Sound/SE/decision27.mp3", DX_PLAYTYPE_BACK);
		return std::make_unique<TitleScene>();
	}
	if ((ClickCheck&(~ClickCheckOld)) && (Mpos > play_continue&&Mpos < play_continue + VECTOR2{ 320,160 }))
	{
		lpSoundMng.PlaySound("Sound/SE/decision27.mp3", DX_PLAYTYPE_BACK);
		return std::make_unique<GameScene>(mode);
	}
	//叙述【ﾌﾟﾚﾃﾞｨｹｰﾄ】
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckEnd(); });
	lpResultCtl.ResultLoad(objList, "data/Resultdata1.data", false);
	lpResultCtl.ResultLoad(objList, "data/Resultdata2.data", false);
	lpResultCtl.ResultLoad(objList, "data/Resultdata3.data", false);

	if (lpResultCtl.GetLoadScore(2) < this->score)
	{
		lpResultCtl.SetUp(this->score, this->time);
		lpResultCtl.RankingScore(objList);
	}
	ResultDraw();
	return std::move(own);		//所有権を移す
}

void ResultScene::RankingDraw()
{

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
	GetGraphSize(IMAGE_ID("image/title.png")[0], &title_size.x, &title_size.y);
	GetGraphSize(IMAGE_ID("image/continue.png")[0], &continue_size.x, &continue_size.y);
	move_title = { 200, 525 };
	play_continue = { 800, 525 };
	return 0;
}

bool ResultScene::ResultDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, IMAGE_ID("image/back.jpg")[0], false);
	DrawRotaGraph(175, 60, 1, 0, IMAGE_ID("image/SCORE.png")[0], true, false);
	DrawRectGraph(TIME_IMAGE_POS, 60, 0, 0, 560, 158, IMAGE_ID("image/play_time.png")[0], true, false);
	for (int num = 0; num < 3; num++)
	{
		DrawRectGraph(TIME_IMAGE_POS + 155 + 130 * num, 200, 0, 89 * num, 104, 89, IMAGE_ID("image/msf.png")[0], true, false);
	}

	//playスコアの表示
	for (int num = 0; num <= 7; num++)
	{
		if (digit != 0)
		{
			digit_score[num] = (this->score / digit) % 10;
			digit = digit / 10;
		}
		if (num != 0)
		{
			DrawRectGraph(80 + 220 + 50 * num, 30, 60 * digit_score[num], 0, 60, 58, IMAGE_ID("image/num.png")[0], true, false);
		}
	}
	//play時間の表示
	auto Time = [&](int posX, int n, int time) {
		digit_play_time[n][0] = (time / 10) % 10;
		digit_play_time[n][1] = (time / 1) % 10;
		DrawRectGraph(posX, 175, 60 * digit_play_time[n][0], 0, 60, 58, IMAGE_ID("image/num.png")[0], true, false);
		DrawRectGraph(posX + 40, 175, 60 * digit_play_time[n][1], 0, 60, 58, IMAGE_ID("image/num.png")[0], true, false);
	};

	//読み込んだﾗﾝｷﾝｸﾞｽｺｱの表示
	for (int n = 0; n < 3; n++)
	{
		digit = 10000000;
		for (int num = 0; num <= 7; num++)
		{
			if (digit != 0)
			{
				rank_score[n][num] = (lpResultCtl.GetLoadScore(n) / digit) % 10;
				digit = digit / 10;
			}
			if (num != 0)
			{
				DrawRectGraph(180 + 50 * num, 270 + 80 * n, 60 * rank_score[n][num], 0, 60, 58, IMAGE_ID("image/ranknum.png")[0], true, false);
			}
		}
		DrawRectGraph(0, 245 + 80 * n, 0, 94 * n, 196, 94, IMAGE_ID("image/rank.png")[0], true, false);
	}



	Time((TIME_IMAGE_POS)+105, 0, (this->time / 3600));
	Time(TIME_IMAGE_POS + 250, 1, (this->time / 60 % 60));
	Time(TIME_IMAGE_POS + 375, 2, (this->time % 60));/**/

	DrawGraph(0, 140, IMAGE_ID("image/Ranking.png")[0], true);
	DrawGraph(move_title.x, move_title.y, IMAGE_ID("image/title.png")[0], true);
	DrawGraph(play_continue.x, play_continue.y, IMAGE_ID("image/continue.png")[0], true);
	DrawFormatString(0, 0, 0xff, "No.1:%d", lpResultCtl.GetLoadScore(0));
	DrawFormatString(0, 25, 0xff, "No.2:%d", lpResultCtl.GetLoadScore(1));
	DrawFormatString(0, 50, 0xff, "No.3:%d", lpResultCtl.GetLoadScore(2));
	VECTOR2 Mpos = { 0,0 };
	GetMousePoint(&Mpos.x, &Mpos.y);
	ScreenFlip();
	return true;
}
