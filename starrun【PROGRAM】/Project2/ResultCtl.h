#pragma once
#include "classObj.h"

#define lpResultCtl ResultCtl::GetInstance()

class Obj;

class ResultCtl
{
public:
	static ResultCtl &GetInstance(void)
	{
		static ResultCtl s_Instance;
		return s_Instance;
	}
	ResultCtl();
	~ResultCtl();
	bool SetUp(const int score, const int time);
	bool ResultSave(sharedListObj objList);					//�V�������삵��ϯ�ߏ��̾��ދy��SUM����
	bool ResultLoad(sharedListObj objList, bool objFlag);		//�ۑ����ꂽϯ�ߏ��̓ǂݍ��݋y��SUM����
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);

private:
	int score;
	int time;
};

