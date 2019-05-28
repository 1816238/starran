#include "DxLib.h"	
#include "SceneMng.h"
#include "Obj.h"
#include "ImageMng.h"
#include "MapControl.h"
#include "Enemy.h"
#include "Player.h"


#define BBM_VER_ID 0x01		//fail�ް�ޮ�ID
#define BBM_FILE_ID "BBM_MAP_DATA"		//failID

struct DataHeader
{
	char fileID[13];		//̧�ق�ID���
	char verID;			//�ް�ޮ�ID
	char reserve1[2];	//�\��̈�
	int sizeX;
	int sizeY;
	char reserve2[3];	//�\��̈�
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
	if (!CheckSize()(selPos, mapSize))		//���x�����Ԃ���邱�ƂɂȂ�̂ōė��p����ۂ͒���
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
		//�͈͊O�̏ꍇ�A���L��ID���Œ�ŕԂ�
		return MAP_ID_NON;//�����Ȓl�Ƃ��ĕԂ�(�V�X�e�����Ԗ�肪�N���Ȃ����낤�����g�p����)
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
		//ͯ�ް�̻��ޏ�������mapDataBace�̻��ނ���
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
			for (auto &data : mapDataBace.main)
			{
				data = MAP_ID_NON;
				if (MessageBox(NULL, "ERROR!!",
					"�m�F�_�C�A���O", MB_OK) == IDOK)
				{
					DxLib_End();	// DXײ���؂̏I������
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
		//ͯ�ް�̻��ޏ�������mapDataBace�̻��ނ���
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
			for (auto &data : mapDataBace.sub)
			{
				data = MAP_ID_NON;
				if (MessageBox(NULL, "ERROR!!",
					"�m�F�_�C�A���O", MB_OK) == IDOK)
				{
					DxLib_End();	// DXײ���؂̏I������
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
