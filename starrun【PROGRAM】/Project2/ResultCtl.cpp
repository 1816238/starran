#include "DxLib.h"
#include "ResultScene.h"
#include "ResultCtl.h"

#define BBM_VER_ID 0x01		//fail�ް�ޮ�ID
#define BBM_FILE_ID "RESULT_DATA"		//failID

ResultCtl::ResultCtl()
{
}


ResultCtl::~ResultCtl()
{
}

bool ResultCtl::SetUp(const int tmp_score, const int tmp_time)
{
	ResultCtl::score = tmp_score;
	ResultCtl::time = tmp_time;
	return false;
}

bool ResultCtl::ResultSave(sharedListObj objList,string f_name,int score)
{
	DataHeader expData = {
			BBM_FILE_ID,
			BBM_VER_ID,
			{0,0},
			score,
			time,
			{ 0,0,0 },
			0xff
	};
	//SUM����-------------------------------------------------------------------
	unsigned int sum = 0;
	expData.sum = (char)sum;

	FILE *file;
	fopen_s(&file, f_name.c_str(), "wb");
	fwrite(&expData, sizeof(expData), 1, file);
	fclose(file);
	return true;
}

bool ResultCtl::ResultLoad(sharedListObj objList, string f_name, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, f_name.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
	DrawFormatString(0, 20, 0x00ff00, "F1�ŃR���e�j���[", expData.score);
	DrawFormatString(0, 40, 0x00ff00, "F1�ŃR���e�j���[", expData.time);

	fclose(file);
	ResultCtl::SetUp(expData.score,expData.time);
	bool flag = true;
	int sum = 0;

	//ͯ�ް��̧��ID���Ɠ����Ŏ����Ă���ID�Ɣ�ׂ�
	//ͯ�ް���ް�ޮݔԍ��Ɠ��������Ă���ԍ����ׂ�	
	//sum�l���v�Z��ͯ�ް��SUM�l�Ɣ�ׂĈ������A
	//if(strcmp(expData.fileID, BBM_FILE_ID))
	if ((std::string)expData.fileID != BBM_FILE_ID
		|| expData.verID != BBM_VER_ID || expData.sum != (char)sum)
	{
		flag = false;
	}
	//�ް���ر����
	if (!flag)
	{
		if (MessageBox(NULL, "���Ă̓I���[�A���`����",
			"�m�F�_�C�A���O", MB_OK) == IDOK)
		{
			DxLib_End();	// DXײ���؂̏I������
		}
	}
	if (flag)
	{
		SetUpGameObj(objList, objFlag);
	}
	return false;
}

bool ResultCtl::SetUpGameObj(sharedListObj objList, bool objFlag)
{
	if (objFlag)
	{
		return false;
	}


	return true;
}

const int ResultCtl::GetLoadScore()
{
	return score;
}

const int ResultCtl::GetLoadScore(int num)
{
	return rankscore[num];
}

const int ResultCtl::GetLoadTime()
{
	return time;
}

const int ResultCtl::GetLoadTime(int num)
{
	return ranktime[num];
}

void ResultCtl::RankingScore(sharedListObj objList)
{
	if (score > rankscore[0])
	{
		rankscore[2] = rankscore[1];
		rankscore[1] = rankscore[0];
		rankscore[0] = score;
		ranktime[2] = ranktime[1];
		ranktime[1] = ranktime[0];
		ranktime[0] = time;
		lpResultCtl.ResultSave(objList, "data/Resultdata1.data", rankscore[0]);
	}
	if ((score < rankscore[0]) && score > rankscore[1])
	{
		rankscore[2] = rankscore[1];
		rankscore[1] = score;
		ranktime[2] = ranktime[1];
		ranktime[1] = time;
		lpResultCtl.ResultSave(objList, "data/Resultdata2.data", rankscore[1]);
	}
	if ((score < rankscore[1]) && score > rankscore[2])
	{
		rankscore[2] = score;
		ranktime[2] = time;
		lpResultCtl.ResultSave(objList, "data/Resultdata3.data", rankscore[2]);
	}

}
