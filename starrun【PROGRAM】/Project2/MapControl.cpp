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
				if (lpSpeedMng.GetFlag(Main))//Ҳ݃}�b�v�̕\��
				{
					if (lpSpeedMng.GetSeasonFlag(Main,SEASON::SPRING))
					{
						if (mapData.main.spring[y][x] < MAP_ID_MAX)
						{
							int add = lpSpeedMng.GetSpeed(Main,SEASON::SPRING);
							if (x*CHIP_SIZE - add > -CHIP_SIZE * 4 && x*CHIP_SIZE - add < SCREEN_SIZE_X)
							{
								DrawGraph(x * CHIP_SIZE - add + CHIP_SIZE * 3, y*CHIP_SIZE, lpImageMng.GetID("image/map.png")[mapData.main.spring[y][x]], true);
								DrawFormatString(0, 120, 0xffffff, "%d", (add));
							}
						}
					}
					if (lpSpeedMng.GetSeasonFlag(Main, SEASON::SUMMER))
					{
						if (mapData.main.summer[y][x] <= MAP_ID_MAX)
						{
							int add = lpSpeedMng.GetSpeed(Main,SEASON::SUMMER);
							if (x*CHIP_SIZE - add > -CHIP_SIZE * 4 && x*CHIP_SIZE - add < SCREEN_SIZE_X)
							{
								DrawGraph(x * CHIP_SIZE - add + CHIP_SIZE * 3, y*CHIP_SIZE, lpImageMng.GetID("image/map.png")[mapData.main.summer[y][x]], true);
								DrawFormatString(0, 140, 0xffffff, "%d", (add ));
							}
						}
					}
					if (lpSpeedMng.GetSeasonFlag(Main, SEASON::AUTUMN))
					{
						if (mapData.main.autumn[y][x] <= MAP_ID_MAX)
						{
							int add = lpSpeedMng.GetSpeed(Main,SEASON::AUTUMN);
							if (x*CHIP_SIZE - add > -CHIP_SIZE * 4 && x*CHIP_SIZE - add < SCREEN_SIZE_X)
							{
								DrawGraph(x * CHIP_SIZE - add + CHIP_SIZE * 3, y*CHIP_SIZE, lpImageMng.GetID("image/map.png")[mapData.main.autumn[y][x]], true);
								DrawFormatString(0, 160, 0xffffff, "%d", ( add ));
							}
						}
					}
					if (lpSpeedMng.GetSeasonFlag(Main, SEASON::WINTER))
					{
						if (mapData.main.winter[y][x] <= MAP_ID_MAX)
						{
							int add = lpSpeedMng.GetSpeed(Main,SEASON::WINTER);
							if (x*CHIP_SIZE - add > -CHIP_SIZE * 4 && x*CHIP_SIZE - add < SCREEN_SIZE_X)
							{
								DrawGraph(x * CHIP_SIZE - add + CHIP_SIZE * 3, y*CHIP_SIZE, lpImageMng.GetID("image/map.png")[mapData.main.winter[y][x]], true);
								DrawFormatString(0, 180, 0xffffff, "%d", ( add ));
							}
						}
					}
				
					

				}
				if (lpSpeedMng.GetFlag(Sub)||lpSpeedMng.GetFlag(Sub2))
				{
					if (mapData.sub[y][x] <= MAP_ID_MAX)
					{
						int add = (lpSpeedMng.GetFlag(Sub) ? Speed(Sub) : Speed(Sub2));
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
	//�t
	mapDataBace.main.spring.resize(mapSize.x * mapSize.y);
	mapData.main.spring.resize(mapSize.y);
	for (int count = 0; count < mapData.main.spring.size(); count++)
	{
		mapData.main.spring[count] = &mapDataBace.main.spring[mapSize.x * count];
	}
	for (int j = 0; j < mapDataBace.main.spring.size(); j++)
	{
		mapDataBace.main.spring[j] = MAP_ID_NON;
	}
	//��
	mapDataBace.main.summer.resize(mapSize.x * mapSize.y);
	mapData.main.summer.resize(mapSize.y);
	for (int count = 0; count < mapData.main.summer.size(); count++)
	{
		mapData.main.spring[count] = &mapDataBace.main.summer[mapSize.x * count];
	}
	for (int j = 0; j < mapDataBace.main.summer.size(); j++)
	{
		mapDataBace.main.summer[j] = MAP_ID_NON;
	}
	//�H
	mapDataBace.main.autumn.resize(mapSize.x * mapSize.y);
	mapData.main.autumn.resize(mapSize.y);
	for (int count = 0; count < mapData.main.autumn.size(); count++)
	{
		mapData.main.spring[count] = &mapDataBace.main.autumn[mapSize.x * count];
	}
	for (int j = 0; j < mapDataBace.main.autumn.size(); j++)
	{
		mapDataBace.main.autumn[j] = MAP_ID_NON;
	}
	//�~
	mapDataBace.main.winter.resize(mapSize.x * mapSize.y);
	mapData.main.winter.resize(mapSize.y);
	for (int count = 0; count < mapData.main.winter.size(); count++)
	{
		mapData.main.spring[count] = &mapDataBace.main.winter[mapSize.x * count];
	}
	for (int j = 0; j < mapDataBace.main.winter.size(); j++)
	{
		mapDataBace.main.winter[j] = MAP_ID_NON;
	}
	//�T�u
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
bool MapControl::SetMapData(const VECTOR2 & pos, MAP_ID id,MapType type,SEASON season)	//true:main,false:Sub
{
	//VECTOR2 selPos;
	//selPos.x = pos.x / chipSize.x;
	//selPos.y = pos.y / chipSize.y;
	VECTOR2 selPos(pos / chipSize);
	if (!CheckSize()(selPos, mapSize))		//���x�����Ԃ���邱�ƂɂȂ�̂ōė��p����ۂ͒���
	{
		return false;
	}
	
	if (type == Main)
	{
		switch (season)
		{
		case SEASON::SPRING:
			mapData.main.spring[selPos.y][selPos.x] = id;
			break;
		case SEASON::SUMMER:
			mapData.main.summer[selPos.y][selPos.x] = id;
			break;
		case SEASON::AUTUMN:
			mapData.main.autumn[selPos.y][selPos.x] = id;
			break;
		case SEASON::WINTER:
			mapData.main.winter[selPos.y][selPos.x] = id;
			break;
		case SEASON::MAX:
		default:
			break;
		}
	}
	else if (type == Sub) {
		mapData.sub[selPos.y][selPos.x] = id;
	}
	else {}
	return true;
}

MAP_ID MapControl::GetMapDate(const VECTOR2 & pos,MapType type,SEASON season)
{
	VECTOR2 selpos(pos / chipSize);
	if (!CheckSize()(selpos, mapSize))
	{
		//�͈͊O�̏ꍇ�A���L��ID���Œ�ŕԂ�
		return MAP_ID_NON;//�����Ȓl�Ƃ��ĕԂ�(�V�X�e�����Ԗ�肪�N���Ȃ����낤�����g�p����)
	}
	if (type==Main)
	{
		switch (season)
		{
		case SEASON::SPRING:
			return mapData.main.spring[selpos.y][selpos.x];
			break;
		case SEASON::SUMMER:
			return mapData.main.summer[selpos.y][selpos.x];
			break;
		case SEASON::AUTUMN:
			return mapData.main.autumn[selpos.y][selpos.x];
			break;
		case SEASON::WINTER:
			return mapData.main.winter[selpos.y][selpos.x];
			break;
		case SEASON::MAX:
		default:
			break;
		}

	}
	else if(type==Sub)
	{
		return mapData.sub[selpos.y][selpos.x];
	}
	else { return MAP_ID_NON; }
}

bool MapControl::LoadSpring(string FileName, sharedListObj objList, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, FileName.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
	//ͯ�ް�̻��ޏ�������mapDataBace�̻��ނ���
	mapDataBace.main.spring.resize(expData.sizeX * expData.sizeY);
	fread(&mapDataBace.main.spring[0], sizeof(MAP_ID), mapDataBace.main.spring.size(), file);
	fclose(file);
	bool flag = true;
	int sum = 0;
	for (int count = 0; count < mapData.main.spring.size(); count++)
	{
		mapData.main.spring[count] = &mapDataBace.main.spring[mapSize.x * count];
	}
	for (auto data : mapDataBace.main.spring)
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
		for (auto &data : mapDataBace.main.spring)
		{
			data = MAP_ID_NON;
			if (MessageBox(NULL, "ERROR!!",
				"�m�F�_�C�A���O", MB_OK) == IDOK)
			{
				DxLib_End();	// DXײ���؂̏I������
			}
		}
	}
	mapDataBace.reload.spring = mapDataBace.main.spring;
	if (flag)
	{
		SetUpGameObj(objList, objFlag);
	}
	return flag;
}

bool MapControl::LoadSummer(string FileName, sharedListObj objList, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, FileName.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
	//ͯ�ް�̻��ޏ�������mapDataBace�̻��ނ���
	mapDataBace.main.summer.resize(expData.sizeX * expData.sizeY);
	fread(&mapDataBace.main.summer[0], sizeof(MAP_ID), mapDataBace.main.summer.size(), file);
	fclose(file);
	bool flag = true;
	int sum = 0;
	for (int count = 0; count < mapData.main.summer.size(); count++)
	{
		mapData.main.summer[count] = &mapDataBace.main.summer[mapSize.x * count];
	}
	for (auto data : mapDataBace.main.summer)
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
		for (auto &data : mapDataBace.main.summer)
		{
			data = MAP_ID_NON;
			if (MessageBox(NULL, "ERROR!!",
				"�m�F�_�C�A���O", MB_OK) == IDOK)
			{
				DxLib_End();	// DXײ���؂̏I������
			}
		}
	}
	mapDataBace.reload.summer = mapDataBace.main.summer;

	if (flag)
	{
		SetUpGameObj(objList, objFlag);
	}
	return flag;
}

bool MapControl::LoadAutumn(string FileName, sharedListObj objList, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, FileName.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
	//ͯ�ް�̻��ޏ�������mapDataBace�̻��ނ���
	mapDataBace.main.autumn.resize(expData.sizeX * expData.sizeY);
	fread(&mapDataBace.main.autumn[0], sizeof(MAP_ID), mapDataBace.main.autumn.size(), file);
	fclose(file);
	bool flag = true;
	int sum = 0;
	for (int count = 0; count < mapData.main.autumn.size(); count++)
	{
		mapData.main.autumn[count] = &mapDataBace.main.autumn[mapSize.x * count];
	}
	for (auto data : mapDataBace.main.autumn)
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
		for (auto &data : mapDataBace.main.autumn)
		{
			data = MAP_ID_NON;
			if (MessageBox(NULL, "ERROR!!",
				"�m�F�_�C�A���O", MB_OK) == IDOK)
			{
				DxLib_End();	// DXײ���؂̏I������
			}
		}
	}
	mapDataBace.reload.autumn = mapDataBace.main.autumn;

	if (flag)
	{
		SetUpGameObj(objList, objFlag);
	}
	return flag;
}

bool MapControl::LoadWinter(string FileName, sharedListObj objList, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, FileName.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
	//ͯ�ް�̻��ޏ�������mapDataBace�̻��ނ���
	mapDataBace.main.winter.resize(expData.sizeX * expData.sizeY);
	fread(&mapDataBace.main.winter[0], sizeof(MAP_ID), mapDataBace.main.winter.size(), file);
	fclose(file);
	bool flag = true;
	int sum = 0;
	for (int count = 0; count < mapData.main.winter.size(); count++)
	{
		mapData.main.winter[count] = &mapDataBace.main.winter[mapSize.x * count];
	}
	for (auto data : mapDataBace.main.winter)
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
		for (auto &data : mapDataBace.main.winter)
		{
			data = MAP_ID_NON;
			if (MessageBox(NULL, "ERROR!!",
				"�m�F�_�C�A���O", MB_OK) == IDOK)
			{
				DxLib_End();	// DXײ���؂̏I������
			}
		}
	}
	mapDataBace.reload.winter = mapDataBace.main.winter;

	if (flag)
	{
		SetUpGameObj(objList, objFlag);
	}
	return flag;
}

bool MapControl::LoadSub(string FileName, sharedListObj objList, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, FileName.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
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

bool MapControl::MapLoad(string FileName,sharedListObj objList, bool objFlag,bool type,SEASON season)
{

	
	if (type)
	{
		switch (season)
		{
		case SEASON::SPRING:
			
			return LoadSpring(FileName, objList, objFlag);
			
			break;
		case SEASON::SUMMER:
			return LoadSummer(FileName, objList, objFlag);
			break;
		case SEASON::AUTUMN:
			return LoadAutumn(FileName, objList, objFlag);
			break;
		case SEASON::WINTER:
			return LoadWinter(FileName, objList, objFlag);
			break;
		case SEASON::MAX:
		default:
			return false;
			break;
		}
	}
	else {
		return LoadSub(FileName, objList, objFlag);
	}
	return false;
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

void MapControl::ReLoadMap(void)
{
	for (int count = 0; count < mapData.main.winter.size(); count++)
	{
		mapData.main.spring[count] = &mapDataBace.reload.spring[mapSize.x * count];
		mapData.main.summer[count] = &mapDataBace.reload.summer[mapSize.x * count];
		mapData.main.autumn[count] = &mapDataBace.reload.autumn[mapSize.x * count];
		mapData.main.winter[count] = &mapDataBace.reload.winter[mapSize.x * count];
	}
}

MapControl::MapControl()
{
	init();
}


MapControl::~MapControl()
{
}
