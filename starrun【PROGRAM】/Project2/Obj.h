#pragma once
#include <map>
#include <string>
#include "VECTOR2.h"
#include "classObj.h"

enum DIR
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_MAX
};

enum ANIM_TBL {
	ANIM_TBL_START_ID,	//
	ANIM_TBL_FRAME,		//画像数
	ANIM_TBL_INV,		//間隔
	ANIM_TBL_LOOP,		//ループするかどうか
	ANIM_TBL_MAX
};

enum OBJ_TYPE {
	TYPE_PLAYER,
	TYPE_ENEMY,
	TYPE_PLAYER_SHOT,
	TYPE_ENEMY_SHOT,
	TYPE_METEO,
	TYPE_ENEMY_BIT,
	TYPE_MAX
};


class GameCtl;
using namespace std;


class Obj
{
public:
	Obj(VECTOR2 drawOffset);
	Obj();
	bool init(string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos);//画像のﾌｧｲﾙ名､分割数､分割総数､座標
	bool init(string fileName, VECTOR2 divSize, VECTOR2 divCnt);			//画像のﾌｧｲﾙ名､分割数､分割総数
	virtual bool initAnim(void) { return true; };
	virtual ~Obj();
	void UpDate(const GameCtl &controller, weekListObj objList);
	virtual bool CheckEnd(void);
	void Draw(unsigned int id);				//固定IDでの生成
	virtual void Draw(void);						//map画像の描画関係
	const VECTOR2 & GetPos(void);			//posの取得
	bool AddAnim(string animName, int ID_x, int ID_y, int frame, int inv, bool loop);		//画像の間隔や枚数などをanimTblに代入
	bool SetAnim(string animName);			//表示画像ﾌｧｲﾙ名及びｱﾆﾒｰｼｮﾝｶｳﾝﾀｰの初期化
	string GetAnim(void);			//表示画像ﾌｧｲﾙ名の取得
	virtual OBJ_TYPE CheckObjType(void);
	const void SetEnd(bool flag);
	const void SetDamage(bool flag, int damage);
	const void SetDamage(bool flag);
	const int  GetObjNo(void)const;
	const int  GetHP(void)const;
	const void SetHP(int hp);
	const int  GetParam(void)const;
	const void SetParam(int hp);
	const int  GetAttack(void)const;
	const int  GetScore(void)const;
	const void AddScore(int num);
	const bool GetSwitchFlag(void)const;
	void SetSwitchFlag(bool flag);
private:
	virtual void SetMove(const GameCtl &controller, weekListObj objList) = 0;		//画像移動のｷｰ制御		純粋仮想関数
	virtual bool init(void) = 0;		//純粋仮想関数

	map<string, int[ANIM_TBL_MAX]> animTbl;
	string animName;				//表示画像ﾌｧｲﾙ名
protected:
	bool animEndFlag;				//ｱﾆﾒｰｼｮﾝ最終ｺﾏ到達ﾌﾗｸﾞ
	unsigned int animCnt;			//ｱﾆﾒｰｼｮﾝｶｳﾝﾀｰ
	const VECTOR2 drawOffset;		//描画ｵﾌｾｯﾄ
	VECTOR2 pos;					//座標
	VECTOR2 pos2;					//座標
	void SetPos(VECTOR2 pos);
	string imageName;				//表示ｱﾆﾒｰｼｮﾝ名
	VECTOR2 divSize;				//分割ｻｲｽﾞ
	VECTOR2 divCnt;					//分割数
	DIR dir;						//進行方向
	bool CheckHit(VECTOR2 pos1, VECTOR2 objSize1, VECTOR2 pos2, VECTOR2 objSize2);
	VECTOR2 VSpos[2];
	OBJ_TYPE objType;
	bool damageFlag;
	int damage;
	bool EndFlag;
	int HP;
	int obj_no;
	int attack;
	int Score;
	bool switchFlag;
};

