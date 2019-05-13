#pragma once
#include <array>
#include "Obj.h"
#include "MapControl.h"

#define PLAYER_DF_SPEED ( 1)
#define MOUSE_ROT_VOL (Rot)
#define PLAYER_SIZE_X 40
#define PLAYER_SIZE_Y CHIP_SIZE*2
#define ADD_SPEED 10

enum DIR_TBL_ID
{
	DIR_TBL_UP,
	DIR_TBL_DOWN,
	DIR_TBL_LEFT,
	DIR_TBL_RIGHT,
	DIR_TBL_MAX
};


using namespace std;

using DIR_TBL_ARRAY = array<int, DIR_MAX>;
using DIR_TBL_PTR_ARRAY = array<int*, DIR_MAX>;
using DIR_TBL_ARRAY_DIR = array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL_ARRAY = array<bool, MAP_ID_MAX>;

class Player :
	public Obj
{
public:
	Player(VECTOR2 setUpPos, VECTOR2 drawOffset);
	Player();
	virtual ~Player();
	bool initAnim(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//Playerの移動
	void Draw(void);
	//void Draw(void);
	float JSpeed;											//移動速度

	int Rot;											//ﾎｲｰﾙ回転量

	unsigned int jumpFlag;											//左ｸﾘｯｸしたらtrue
	bool shotFlag;											//右ｸﾘｯｸでtrue
	int SavePos;
	DIR_TBL_ARRAY keyID_Tbl;								//移動に使うｷｰ情報のﾃｰﾌﾞﾙ
	DIR_TBL_ARRAY speed_Tbl;								//移動量のﾃｰﾌﾞﾙ
	//MAP_MOVE_TBL_ARRAY mapMove_Tbl;						//移動制限をかけるﾌﾞﾛｯｸIDを保管しておく
	int getcnt[3];											//星を取得した数
	void CheckMapHit(void);									//mapとの当たり判定
	double time;
	array<VECTOR2,DIR_MAX>DirPos;
	bool DownCheck;											//当たり判定用フラグ
	bool DeathFlag;											//死亡判定用フラグ
};

