#pragma once
#include "BaseScene.h"
#include "classObj.h"
class ResultScene :
	public BaseScene
{
public:
	ResultScene(int play_score,int play_time);
	~ResultScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller);
private:
	sharedListObj objList;
	virtual int Init(void);
	bool ResultDraw(void);
	int score;
	int time;
	int digit_score[7];
	int digit_high_score[7];
	int digit_high;
	int digit;

};

