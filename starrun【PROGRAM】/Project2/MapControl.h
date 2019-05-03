#pragma once
#include <vector>
#include "VECTOR2.h"
#include "classObj.h"

enum MAP_ID
{
	MAP_ID_CUR,
	MAP_ID_FLOOR1,
	MAP_ID_FLOOR2,
	MAP_ID_BOMB,
	MAP_ID_NON,
	MAP_ID_WALL1,
	MAP_ID_WALL2,
	MAP_ID_BLOCK,
	MAP_ID_ITEM_FIRE,
	MAP_ID_ITEM_BOMB,
	MAP_ID_ITEM_CTL,
	MAP_ID_ITEM_SPEED,
	MAP_ID_MAX
};

#define lpMapControl MapControl::GetInstance()

class Obj;
using namespace std;

class MapControl
{
public:
	static MapControl &GetInstance(void)
	{
		static MapControl s_Instance;
		return s_Instance;
	}
	void Draw(bool TitleFlag);		//map�摜�̕`��
	bool SetUp(const VECTOR2& size, const VECTOR2& chipsize, const VECTOR2 drawOffSet);
	bool SetMapData(const VECTOR2& pos, MAP_ID id);			//�摜��z�u���悤�Ƃ��Ă���ꏊ��map�͈͓̔����̔���
	MAP_ID GetMapDate(const VECTOR2& pos/*���W*/);					//�w�肵�����W�̏��̎擾
	bool MapSave(sharedListObj objList);					//�V�������삵��ϯ�ߏ��̾��ދy��SUM����
	bool MapLoad(sharedListObj objList, bool objFlag);		//�ۑ����ꂽϯ�ߏ��̓ǂݍ��݋y��SUM����
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	const VECTOR2 & GetChipSize(void);
private:
	MapControl();
	~MapControl();
	vector<MAP_ID> mapDataBace;		//map�̏������Ă����z��i1�����ځj
	vector<MAP_ID*> mapData;			//map�̏������Ă����z��i2�����ځj
	VECTOR2 mapSize;			//map�̏c�Ɖ������Ă����ϐ�
	VECTOR2 chipSize;			//�������1������̉摜�̻��ނ����Ă����ϐ�
	VECTOR2 drawOffSet;		//�ǂꂾ�����炷���̐��l�����Ă����ϐ�


};

