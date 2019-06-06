#include "DxLib.h"
#include "ResultScene.h"
#include "ResultCtl.h"

#define BBM_VER_ID 0x01		//failﾊﾞｰｼﾞｮﾝID
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
	//SUMﾁｪｯｸ-------------------------------------------------------------------
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
	DrawFormatString(0, 20, 0x00ff00, "F1でコンテニュー", expData.score);
	DrawFormatString(0, 40, 0x00ff00, "F1でコンテニュー", expData.time);

	fclose(file);
	ResultCtl::SetUp(expData.score,expData.time);
	bool flag = true;
	int sum = 0;

	//ﾍｯﾀﾞｰのﾌｧｲﾙID情報と内部で持っているIDと比べる
	//ﾍｯﾀﾞｰのﾊﾞｰｼﾞｮﾝ番号と内部持っている番号を比べる	
	//sum値を計算しﾍｯﾀﾞｰのSUM値と比べて違ったら、
	//if(strcmp(expData.fileID, BBM_FILE_ID))
	if ((std::string)expData.fileID != BBM_FILE_ID
		|| expData.verID != BBM_VER_ID || expData.sum != (char)sum)
	{
		flag = false;
	}
	//ﾃﾞｰﾀをｸﾘｱする
	if (!flag)
	{
		if (MessageBox(NULL, "さてはオメーアンチだな",
			"確認ダイアログ", MB_OK) == IDOK)
		{
			DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
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
