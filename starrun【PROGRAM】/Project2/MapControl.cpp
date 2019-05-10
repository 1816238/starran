#include "DxLib.h"	
#include "SceneMng.h"
#include "Obj.h"
#include "ImageMng.h"
#include "MapControl.h"
#include "Enemy.h"
#include "Player.h"
#include "SpeedMng.h"

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
	
		for (int y = 0; y < SCREEN_SIZE_Y / CHIP_SIZE; y++)
		{
			for (int x = 0; x < (SCREEN_SIZE_X * 4) / CHIP_SIZE; x++)
			{
				if (mapData[y][x] <= MAP_ID_MAX)
				{
					int add = Time + lpSpeedMng.GetInstance().GetYellow();
					if (VECTOR2{ x * CHIP_SIZE - add, y*CHIP_SIZE } < VECTOR2{ SCREEN_SIZE_X,SCREEN_SIZE_Y }&&VECTOR2{ x * CHIP_SIZE - add, y*CHIP_SIZE } > VECTOR2{ -CHIP_SIZE,0 })
					{
						DrawGraph(x * CHIP_SIZE - add , y*CHIP_SIZE, lpImageMng.GetID("image/map.png")[mapData[y][x]], true);

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

	mapDataBace.resize(mapSize.x * mapSize.y);
	mapData.resize(mapSize.y);
	for (int count = 0; count < mapData.size(); count++)
	{
		mapData[count] = &mapDataBace[mapSize.x * count];
	}
	for (int j = 0; j < mapDataBace.size(); j++)
	{
		mapDataBace[j] = MAP_ID_NON;
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
bool MapControl::SetMapData(const VECTOR2 & pos, MAP_ID id)
{
	//VECTOR2 selPos;
	//selPos.x = pos.x / chipSize.x;
	//selPos.y = pos.y / chipSize.y;
	VECTOR2 selPos(pos / chipSize);
	if (!CheckSize()(selPos, mapSize))		//���x�����Ԃ���邱�ƂɂȂ�̂ōė��p����ۂ͒���
	{
		return false;
	}
	mapData[selPos.y][selPos.x] = id;
	return true;
}

MAP_ID MapControl::GetMapDate(const VECTOR2 & pos)
{
	VECTOR2 selpos(pos / chipSize);
	if (!CheckSize()(selpos, mapSize))
	{
		//�͈͊O�̏ꍇ�A���L��ID���Œ�ŕԂ�
		return MAP_ID_MAX;//�����Ȓl�Ƃ��ĕԂ�(�V�X�e�����Ԗ�肪�N���Ȃ����낤�����g�p����)
	}

	return mapData[selpos.y][selpos.x];
}

bool MapControl::MapLoad(sharedListObj objList, bool objFlag)
{

	FILE *file;
	DataHeader expData;
	fopen_s(&file, "data/mapdata2.map", "rb");
	fread(&expData, sizeof(expData), 1, file);
	//ͯ�ް�̻��ޏ�������mapDataBace�̻��ނ���
	mapDataBace.resize(expData.sizeX * expData.sizeY);
	fread(&mapDataBace[0], sizeof(MAP_ID), mapDataBace.size(), file);
	fclose(file);
	bool flag = true;
	int sum = 0;
	for (int count = 0; count < mapData.size(); count++)
	{
		mapData[count] = &mapDataBace[mapSize.x * count];
	}
	for (auto data : mapDataBace)
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
		for (auto &data : mapDataBace)
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

bool MapControl::SetUpGameObj(sharedListObj objList, bool objFlag)
{
	if (objFlag)
	{
		return false;
	}
	bool MakePlayerflag = false;
	bool MakeEnemyflag = false;
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			MAP_ID id = mapData[y][x];

			if (MakePlayerflag)
			{
				break;
			}
			{
				//��ڲ԰�L������ݽ�ݽ����
				ListObj_itr obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(CHIP_SIZE * 2, CHIP_SIZE * 15), lpSceneMng.GetDrawOffset()));

				MakePlayerflag = true;
			}
			ListObj_itr obj = AddObjList()(objList, std::make_unique<Enemy>());

			break;
		}
	}

	return true;
}

const VECTOR2 & MapControl::GetChipSize(void)
{
	return chipSize;
}

MapControl::MapControl()
{
}


MapControl::~MapControl()
{
}
