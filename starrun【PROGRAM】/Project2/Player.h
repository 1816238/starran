#pragma once
#include <array>
#include "Obj.h"
#include "MapControl.h"

#define PLAYER_DF_SPEED ( 1)
#define MOUSE_ROT_VOL (Rot)
#define PLAYER_SIZE_X 50
#define PLAYER_SIZE_Y 64
#define ADD_SPEED 4
#define SHOT_DAMAGE 5

#define lpPlayer Player::GetInstance()


enum DIR_TBL_ID
{
	DIR_TBL_UP,
	DIR_TBL_DOWN,
	DIR_TBL_LEFT,
	DIR_TBL_RIGHT,
	DIR_TBL_MAX
};
enum class MAP_FLAG_TYPE
{
	DOWN,
	JUMP,
	MAX,
};

using namespace std;

using DIR_TBL_ARRAY = array<int, DIR_MAX>;
using DIR_TBL_PTR_ARRAY = array<int*, DIR_MAX>;
using DIR_TBL_ARRAY_DIR = array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL_ARRAY = array<bool, MAP_ID_MAX>;

class GameScene;

class Player :
	public Obj
{
public:
	/*static Player &GetInstance(void)
	{
		static Player s_Instance;
		return s_Instance;
	}*/
	Player(VECTOR2 setUpPos, OBJ_TYPE objType,VECTOR2 drawOffset);
	Player();
	~Player();
	Player(Player&) {};
	void operator=(Player&) {};
	bool initAnim(void);
	const bool GetDeathFlag(void);											//���S���Ƀt���O��n��
	bool init(void);													//�������p
	OBJ_TYPE CheckObjType(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//Player�̈ړ�
	void Draw(void);
	void CheckMapHit(void);									//map�Ƃ̓����蔻��

	float JSpeed;											//�ړ����x
	unsigned int jumpFlag;											//���د�������true

	int Rot;											//β�ى�]��
	array<int, MAP_ID_MAX> CheckFlag;

	ListObj_itr shot[100];					// �������������e�̱��ڽ���i�[
	bool shotFlag[100];											//�E�د���true
	int shotSpeed;
	int shotPos;
	int shotcnt;

	DIR_TBL_ARRAY keyID_Tbl;								//�ړ��Ɏg��������ð���
	DIR_TBL_ARRAY speed_Tbl;								//�ړ��ʂ�ð���
	//MAP_MOVE_TBL_ARRAY mapMove_Tbl;						//�ړ���������������ۯ�ID��ۊǂ��Ă���
	int getcnt[4];												//����̎擾��
	string meter_name[4];											//�e����Ұ���摜�̖��O
					
	map<string, int> time;

	array<VECTOR2,DIR_MAX>DirPos;
	bool DownCheck;											//�����蔻��p�t���O
	array<int, MAP_ID_MAX> ScoreTbl;

};

