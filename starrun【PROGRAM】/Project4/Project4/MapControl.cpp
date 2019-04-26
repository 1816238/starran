#include "DxLib.h"	
#include "SceneMng.h"
#include "Obj.h"
#include "ImageMng.h"
#include "MapControl.h"


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

void MapControl::Draw(bool EditFlag)
{

	//if (!EditFlag)
	//{
	//	int Cnt = 0;
	//	for (int y = 0; y < mapSize.y; y++)
	//	{
	//		Cnt = (y % 2);
	//		for (int x = 0; x < mapSize.x; x++)
	//		{
	//			Cnt++;
	//			DrawGraph(drawOffSet.x + x * chipSize.x, drawOffSet.y + y * chipSize.y
	//				, lpImageMng.GetID("image/map.png")[MAP_ID_FLOOR1 + (Cnt % 2)], true);
	//		}
	//	}
	//}

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			MAP_ID id = mapData[y][x];
			switch (id)
			{
				//��ɕ`�悵�Ȃ�
		

	//�w�i

			case MAP_ID_RED:
			case MAP_ID_BLUE:
			case MAP_ID_GReEN:
			case MAP_ID_YELLOW:
				DrawGraph(drawOffSet.x + x * chipSize.x, drawOffSet.y + y * chipSize.y
					, lpImageMng.GetID("image/EDGE1.png")[id], true);
				break;
			
				break;
				//�װ
			default:
#ifdef _DEBUG
				DrawGraph( x * chipSize.x, y * chipSize.y
					, lpImageMng.GetID("image/EDGE1.png")[MAP_ID_YELLOW], true);
#endif
				break;
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
		mapDataBace[j] = MAP_ID_RED;
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
		return MAP_ID_BLUE;//�����Ȓl�Ƃ��ĕԂ�(�V�X�e�����Ԗ�肪�N���Ȃ����낤�����g�p����)
	}

	return mapData[selpos.y][selpos.x];
}

bool MapControl::MapSave(sharedListObj objList)
{
	DataHeader expData = {
		BBM_FILE_ID,
		BBM_VER_ID,
		{0,0},
		mapSize.x,
		mapSize.y,
		{ 0,0,0 },
		0xff
	};
	//SUM����-------------------------------------------------------------------
	int sum = 0;

	for (auto data : mapDataBace)
	{
		sum += (int)data;
	}
	expData.sum = (char)sum;

	FILE *file;
	fopen_s(&file, "date/mapdate.map", "wb");
	fwrite(&expData, sizeof(expData), 1, file);
	fwrite(&mapDataBace[0], sizeof(MAP_ID)*mapDataBace.size(), 1, file);
	fclose(file);
	return true;
}

bool MapControl::MapLoad(sharedListObj objList, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, "date/mapdate.map", "rb");
	fread(&expData, sizeof(expData), 1, file);
	//ͯ�ް�̻��ޏ�������mapDataBace�̻��ނ���
	mapDataBace.resize(expData.sizeX * expData.sizeY);
	fread(&mapDataBace[0], sizeof(MAP_ID), mapDataBace.size(), file);
	fclose(file);
	bool flag = true;
	int sum = 0;
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
			data = MAP_ID_RED;
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
