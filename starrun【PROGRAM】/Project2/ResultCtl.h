#pragma once
#include "classObj.h"

#define lpResultCtl ResultCtl::GetInstance()

class Obj;

struct DataHeader
{
	char fileID[12];		//̧�ق�ID���
	char verID;			//�ް�ޮ�ID
	char reserve1[3];	//�\��̈�
	int score;
	int time;
	char reserve2[3];	//�\��̈�
	char sum;
};

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
	bool ResultSave(sharedListObj objList,string f_name, int score);					//�V�������삵��ϯ�ߏ��̾��ދy��SUM����
	bool ResultLoad(sharedListObj objList, string f_name, bool objFlag);		//�ۑ����ꂽϯ�ߏ��̓ǂݍ��݋y��SUM����
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	void RankingScore(sharedListObj objList);
	const int GetLoadScore();		//�ۑ����ꂽscore���Ăяo��
	const int GetLoadScore(int num);		//�ۑ����ꂽ�����L���Oscore���Ăяo��
	const int GetLoadTime();		//�ۑ����ꂽtime���Ăяo��
	const int GetLoadTime(int num);		//�ۑ����ꂽ�����L���Otime���Ăяo��
private:
	int score;
	int time;
	int rankscore[3];
	int ranktime[3];
};
