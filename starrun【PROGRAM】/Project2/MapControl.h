#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"
#include "SpeedMng.h"

enum MAP_ID
{
	MAP_ID_NON,
	MAP_ID_CLOUD1,
	MAP_ID_CLOUD2,
	MAP_ID_CLOUD3,
	MAP_ID_NON2,
	MAP_ID_YELLOW,
	MAP_ID_GREEN,
	MAP_ID_RED,
	MAP_ID_MAX
};

enum class SEASON_ID
{
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER,
	EX,
	MAX
};

typedef struct{
	vector<MAP_ID> main;
	vector<MAP_ID> sub;
}MapDataBase;

typedef struct {
	vector<MAP_ID*> main;
	vector<MAP_ID*> sub;
}MapData;


#define lpMapControl MapControl::GetInstance()

class Obj;
//class SpeedMng;
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
	bool SetMapData(const VECTOR2& pos, MAP_ID id, MapType type);			//�摜��z�u���悤�Ƃ��Ă���ꏊ��map�͈͓̔����̔���
	MAP_ID GetMapDate(const VECTOR2& pos,MapType type);					//�w�肵�����W�̏��̎擾,type��true�Ȃ�main��ϯ���ް���false�Ȃ�sub��ϯ���ް���Ԃ�
	bool MapLoad(string FileName,sharedListObj objList, bool objFlag,bool type);		//�ۑ����ꂽϯ�ߏ��̓ǂݍ��݋y��SUM����
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	const VECTOR2 & GetChipSize(void);
	bool GetSubFlag(void);
	bool init(void);
private:
	MapControl();
	~MapControl();
	MapDataBase mapDataBace;		//map�̏������Ă����z��i1�����ځj
	MapData mapData;			//map�̏������Ă����z��i2�����ځj
	VECTOR2 mapSize;			//map�̏c�Ɖ������Ă����ϐ�
	VECTOR2 chipSize;			//�������1������̉摜�̻��ނ����Ă����ϐ�
	VECTOR2 drawOffSet;		//�ǂꂾ�����炷���̐��l�����Ă����ϐ�
	VECTOR2 pos;
	bool SubFlag;
	array< int, int(SEASON_ID::MAX)> offset;
};

