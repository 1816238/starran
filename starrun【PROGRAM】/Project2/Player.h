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
	const bool GetDeathFlag(void);											//死亡時にフラグを渡す
	bool init(void);													//初期化用
	OBJ_TYPE CheckObjType(void);
private:
	void SetMove(const GameCtl &controller, weekListObj objList);		//Playerの移動
	void Draw(void);
	void CheckMapHit(void);									//mapとの当たり判定

	float JSpeed;											//移動速度
	unsigned int jumpFlag;											//左ｸﾘｯｸしたらtrue

	int Rot;											//ﾎｲｰﾙ回転量
	array<int, MAP_ID_MAX> CheckFlag;

	ListObj_itr shot[100];					// 自分が撃った弾のｱﾄﾞﾚｽを格納
	bool shotFlag[100];											//右ｸﾘｯｸでtrue
	int shotSpeed;
	int shotPos;
	int shotcnt;

	DIR_TBL_ARRAY keyID_Tbl;								//移動に使うｷｰ情報のﾃｰﾌﾞﾙ
	DIR_TBL_ARRAY speed_Tbl;								//移動量のﾃｰﾌﾞﾙ
	//MAP_MOVE_TBL_ARRAY mapMove_Tbl;						//移動制限をかけるﾌﾞﾛｯｸIDを保管しておく
	int getcnt[4];												//ｽﾀｰの取得量
	string meter_name[4];											//各星のﾒｰﾀｰ画像の名前
					
	map<string, int> time;

	array<VECTOR2,DIR_MAX>DirPos;
	bool DownCheck;											//当たり判定用フラグ
	array<int, MAP_ID_MAX> ScoreTbl;

};

