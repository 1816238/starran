#include "DxLib.h"	
#include "SceneMng.h"
#include "Obj.h"
#include "ImageMng.h"
#include "MapControl.h"
#include "Enemy.h"
#include "Player.h"


#define BBM_VER_ID 0x01		//failﾊﾞｰｼﾞｮﾝID
#define BBM_FILE_ID "BBM_MAP_DATA"		//failID

struct DataHeader
{
	char fileID[13];		//ﾌｧｲﾙのID情報
	char verID;			//ﾊﾞｰｼﾞｮﾝID
	char reserve1[2];	//予約領域
	int sizeX;
	int sizeY;
	char reserve2[3];	//予約領域
	char sum;
};

void MapControl::Draw(bool TitleFlag)
{
	SubFlag = (Speed(Main) > SCREEN_SIZE_X * 4 - CHIP_SIZE * 4 ? true : false);
		for (int y = 0; y < SCREEN_SIZE_Y / CHIP_SIZE; y++)
		{
			for (int x = 0; x < (SCREEN_SIZE_X * 4) / CHIP_SIZE; x++)
			{
				if (lpSpeedMng.GetFlag(Main))
				{
					if (mapData.main[y][x] <= MAP_ID_MAX)
					{
						int add = Speed(Main);
						if (x*CHIP_SIZE-add> -CHIP_SIZE*4&& x*CHIP_SIZE - add<SCREEN_SIZE_X)
						{
							DrawGraph(x * CHIP_SIZE - add + CHIP_SIZE * 3, y*CHIP_SIZE, lpImageMng.GetID("image/map.png")[mapData.main[y][x]], true);

						}
					}

				}
				if (lpSpeedMng.GetFlag(Sub))
				{
					if (mapData.sub[y][x] <= MAP_ID_MAX)
					{
						int add = Speed(Sub);
						if (x*CHIP_SIZE - add > -CHIP_SIZE * 4 && x*CHIP_SIZE - add < SCREEN_SIZE_X)
						{

							DrawGraph(x * CHIP_SIZE - add+ CHIP_SIZE * 3, y*CHIP_SIZE, lpImageMng.GetID("image/map.png")[mapData.sub[y][x]], true);

						}
					}

				}

			}
		}
}

bool MapControl::SetUp(const VECTOR2 & size, const VECTOR2 &chipSize, const VECTOR2 drawOffSet)
{
	mapSize = VECTOR2(size.x / chipSize.x, size.y / chipSize.y);
	MapControl::chipSize = chipSize;
	MapControl::drawOffSet = drawOffSet;

	mapDataBace.main.resize(mapSize.x * mapSize.y);
	mapData.main.resize(mapSize.y);
	for (int count = 0; count < mapData.main.size(); count++)
	{
		mapData.main[count] = &mapDataBace.main[mapSize.x * count];
	}
	for (int j = 0; j < mapDataBace.main.size(); j++)
	{
		mapDataBace.main[j] = MAP_ID_NON;
	}

	mapDataBace.sub.resize(mapSize.x * mapSize.y);
	mapData.sub.resize(mapSize.y);
	for (int count = 0; count < mapData.sub.size(); count++)
	{
		mapData.sub[count] = &mapDataBace.sub[mapSize.x * count];
	}
	for (int j = 0; j < mapDataBace.sub.size(); j++)
	{
		mapDataBace.sub[j] = MAP_ID_NON;
	}
	
	return false;
}
struct CheckSize
{
	bool operator()(const VECTOR2 &selPos, const VECTOR2 &mapSize) {

		if ((selPos.x < 0) || (selPos.x >= mapSize.x)
			|| (selPos.y < 0) || (selPos.y >= mapSize.y))
		{
			return false;
		}
		return true;
	}
};
bool MapControl::SetMapData(const VECTOR2 & pos, MAP_ID id,MapType type)	//true:main,false:Sub
{
	//VECTOR2 selPos;
	//selPos.x = pos.x / chipSize.x;
	//selPos.y = pos.y / chipSize.y;
	VECTOR2 selPos(pos / chipSize);
	if (!CheckSize()(selPos, mapSize))		//何度も実態を作ることになるので再利用する際は注意
	{
		return false;
	}
	if (type==Main)
	{
		mapData.main[selPos.y][selPos.x] = id;
	}
	else if(type==Sub){
		mapData.sub[selPos.y][selPos.x] = id;
	}else{}
	return true;
}

MAP_ID MapControl::GetMapDate(const VECTOR2 & pos,MapType type)
{
	VECTOR2 selpos(pos / chipSize);
	if (!CheckSize()(selpos, mapSize))
	{
		//範囲外の場合、下記のIDを固定で返す
		return MAP_ID_NON;//無効な値として返す(システム上一番問題が起きないだろう物を使用する)
	}
	if (type==Main)
	{
		return mapData.main[selpos.y][selpos.x];

	}
	else if(type==Sub)
	{
		return mapData.sub[selpos.y][selpos.x];
	}
	else { return MAP_ID_NON; }
}

bool MapControl::MapLoad(string FileName,sharedListObj objList, bool objFlag,bool type)
{

	FILE *file;
	DataHeader expData;
	fopen_s(&file, FileName.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
	if (type)
	{
		//ﾍｯﾀﾞｰのｻｲｽﾞ情報を元にmapDataBaceのｻｲｽﾞする
		mapDataBace.main.resize(expData.sizeX * expData.sizeY);
		fread(&mapDataBace.main[0], sizeof(MAP_ID), mapDataBace.main.size(), file);
		fclose(file);
		bool flag = true;
		int sum = 0;
		for (int count = 0; count < mapData.main.size(); count++)
		{
			mapData.main[count] = &mapDataBace.main[mapSize.x * count];
		}
		for (auto data : mapDataBace.main)
		{
			sum += (int)data;
		}

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
			for (auto &data : mapDataBace.main)
			{
				data = MAP_ID_NON;
				if (MessageBox(NULL, "ERROR!!",
					"確認ダイアログ", MB_OK) == IDOK)
				{
					DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
				}
			}
		}
		if (flag)
		{
			SetUpGameObj(objList, objFlag);
		}
		return flag;
	}
	else {
		//ﾍｯﾀﾞｰのｻｲｽﾞ情報を元にmapDataBaceのｻｲｽﾞする
		mapDataBace.sub.resize(expData.sizeX * expData.sizeY);
		fread(&mapDataBace.sub[0], sizeof(MAP_ID), mapDataBace.sub.size(), file);
		fclose(file);
		bool flag = true;
		int sum = 0;
		for (int count = 0; count < mapData.sub.size(); count++)
		{
			mapData.sub[count] = &mapDataBace.sub[mapSize.x * count];
		}
		for (auto data : mapDataBace.sub)
		{
			sum += (int)data;
		}

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
			for (auto &data : mapDataBace.sub)
			{
				data = MAP_ID_NON;
				if (MessageBox(NULL, "ERROR!!",
					"確認ダイアログ", MB_OK) == IDOK)
				{
					DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
				}
			}
		}
		if (flag)
		{
			SetUpGameObj(objList, objFlag);
		}
		return flag;
	}
}

bool MapControl::SetUpGameObj(sharedListObj objList, bool objFlag)
{
	return true;
}

const VECTOR2 & MapControl::GetChipSize(void)
{
	return chipSize;
}

bool MapControl::GetSubFlag(void)
{
	return SubFlag;
}

bool MapControl::init(void)
{

	return false;
}

MapControl::MapControl()
{
	init();
}


MapControl::~MapControl()
{
}
