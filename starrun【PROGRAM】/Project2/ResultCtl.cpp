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

bool ResultCtl::SetUp(const int score, const int time)
{
	ResultCtl::score = score;
	ResultCtl::time = time;
	return false;
}

bool ResultCtl::ResultSave(sharedListObj objList)
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
	fopen_s(&file, "data/Resultdata.data", "wb");
	fwrite(&expData, sizeof(expData), 1, file);
	fclose(file);
	return true;
}

bool ResultCtl::ResultLoad(sharedListObj objList, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, "data/Resultdata.data", "rb");
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

const int ResultCtl::GetLoadTime()
{
	return time;
}
