#pragma once
#include "BaseScene.h"
#include "classObj.h"
#include "VECTOR2.h"
#define TIME_IMAGE_POS		(50 + 340 * 2)
#define SCORE_IMAGE_POS		(50 + 163 / 2)
class ResultScene :
	public BaseScene
{
private:
	void RankingDraw();
	virtual int Init(void);
	bool ResultDraw(void);
public:
	ResultScene(int play_score,int play_time);
	~ResultScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller);
private:
	sharedListObj objList;
	int score;
	int time;

	int time_digit;

	int digit_score[7];
	int digit_high_score[7];
	int digit_play_time[2][2];
	int digit_high;
	int digit;

	int rank_score[3][7];
	int rank_time[3][7];
	bool ClickCheck;
	bool ClickCheckOld;

	VECTOR2 move_title;
	VECTOR2 play_continue;

};

