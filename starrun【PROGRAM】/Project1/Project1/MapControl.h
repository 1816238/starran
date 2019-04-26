#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"
#include "MAP_ID.h"

enum class FIRE_ACT
{
	NON,		//�@���Ă���
	STOP,		//�@���Ă��Ȃ�
	STOP_ER,	//�@���Ă����ɂ���Ͻ������
	POP_ENEMY,	//�@���Ă�����œG�̏o��
	ERR,		//�@�װ
	MAX
};



#define lpMapControl MapControl::GetInstance()

// �v�Z��`
#define PI    ( 3.1415926535897932384626433832795f )
#define RAD( X )((X * PI) / 180.0 )

class Obj;
using namespace std;
using u_int = unsigned int;

using FIRE_ACT_TBL_ARRAY = array<FIRE_ACT, static_cast<int>(MAP_ID::MAX)>;

class MapControl
{
public:
	static MapControl &GetInstance(void)
	{
		static MapControl s_Instance;
		return s_Instance;
	}
	void UpDate();
	void  Draw(bool EditFlag);									//map�摜�̕`��
	//void  Draw_Fire(void);
	bool  SetUp(const VECTOR2& size ,const VECTOR2& chipsize,const VECTOR2 drawOffSet);
	bool  SetMapData(const VECTOR2& pos,MAP_ID id );			// �摜��z�u���悤�Ƃ��Ă���ꏊ��map�͈͓̔����̔���
	//bool  SetMapData_Fire(const VECTOR2 &pos, FIRE_DIR dir);

	//MAP_ID GetMapDate(const VECTOR2& pos/*���W*/);		// �w�肵�����W�̏��̎擾
	//unsigned int GetMapDate_Fire(const VECTOR2& pos/*���W*/);		// �w�肵�����W�̏��̎擾

	bool  MapSave(sharedListObj objList);						// �V�������삵��ϯ�ߏ��̾��ދy��SUM����
	bool  MapLoad(sharedListObj objList,bool objFlag);			// �ۑ����ꂽϯ�ߏ��̓ǂݍ��݋y��SUM����

	//bool  SetUpGameObj(sharedListObj objList, bool DrawFlag);

	const VECTOR2 & GetChipSize(void);
private:
	MapControl();
	~MapControl();

	//void InitTblData(void);			// �����p��]ð��ق̏������p	

	vector<MAP_ID> mapDataBace;		// map�̏������Ă����z��i1�����ځj
	vector<MAP_ID*> mapData;		// map�̏������Ă����z��i2�����ځj
	//vector<unsigned int > mapDataBace_Fire;		// �����̏������Ă����z��i1�����ځj4�޲Ă���
	//vector<unsigned int*> mapData_Fire;			// �����̏������Ă����z��i2�����ځj4�޲Ă���

	//array<double, static_cast<int>(FIRE_DIR::MAX)>rotPtnTbl;		// �����p��]ð���
	//FIRE_ACT_TBL_ARRAY fireActTbl;		// �����p��]ð���

	VECTOR2 mapSize;				// map�̏c�Ɖ������Ă����ϐ�
	VECTOR2 chipSize;				// �������1������̉摜�̻��ނ����Ă����ϐ�
	VECTOR2 drawOffSet;				// �ǂꂾ�����炷���̐��l�����Ă����ϐ�
	
	int bgImage;					//�w�i��חp�����

	template<typename mapType, typename idType>
	bool SetData(mapType maps , const VECTOR2& pos, idType id);
	
	template<typename mapType, typename idType>
	idType GetDate(mapType maps, const VECTOR2& pos/*���W*/, idType defID);		// �w�肵�����W�̏��̎擾
};


