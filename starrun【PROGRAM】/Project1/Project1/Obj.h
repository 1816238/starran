#pragma once
#include <map>
#include <string>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"

enum class DIR
{
	DOWN,		//下
	LEFT,		//左
	RIGHT,		//右
	UP,			//上
	MAX
};

enum class ANIM_TBL {
	START_ID,	//
	FRAME,		//画像数
	INV,		//間隔
	LOOP,		//ループするかどうか
	MAX
};

enum OBJ_TYPE{
	PLAYER,
	ENEMY,
	BOMB,
	EDIT_CUR,
	MAX
};



class GameController;
using namespace std;
using DIR_STRING_ARRAY = array<string, static_cast<size_t>(DIR::MAX)>;
using Type_long = unsigned long long;															// 長いので省略する
 
class Obj
{
public:
	Obj(VECTOR2 drawOffset);
	Obj();
	bool init(string fileName, VECTOR2 divSize, VECTOR2 divCnt,VECTOR2 pos);				// 画像のﾌｧｲﾙ名､分割数､分割総数､座標
	bool init(string fileName, VECTOR2 divSize, VECTOR2 divCnt);							// 画像のﾌｧｲﾙ名､分割数､分割総数
	virtual bool initAnim(void) { return true; };
	virtual ~Obj();
	void UpDate(const GameController &controller, weekListObj objList);
	virtual bool CheckDeth(void) { return false; };
	virtual bool CheackObjType(OBJ_TYPE Obj_type) = 0;										// 現在のクラス確認
	void Draw(unsigned int id);																// 固定IDでの生成
	virtual void Draw(void);																// map画像の描画関係
	const VECTOR2 & GetPos(void);															// posの取得
	bool AddAnim(string animName, int ID_x, int ID_y, int frame, int inv,bool loop);		// 画像の間隔や枚数などをanimTblに代入
	bool SetAnim(string animName);															// 表示画像ﾌｧｲﾙ名及びｱﾆﾒｰｼｮﾝｶｳﾝﾀｰの初期化
	string GetAnim(void);																	// 表示画像ﾌｧｲﾙ名の取得
private:
	virtual void SetMove(const GameController &controller, weekListObj objList) = 0;		// 画像移動のｷｰ制御		純粋仮想関数

	map<string, int[static_cast<Type_long>(ANIM_TBL::MAX)]> animTbl;
	string animName;																		// 表示画像ﾌｧｲﾙ名
protected:
	bool animEndFlag;																		// ｱﾆﾒｰｼｮﾝ最終ｺﾏ到達ﾌﾗｸﾞ
	unsigned int animCnt;																	// ｱﾆﾒｰｼｮﾝｶｳﾝﾀｰ
	const VECTOR2 drawOffset;																// 描画ｵﾌｾｯﾄ
	VECTOR2 pos;																			// 座標
	void SetPos(VECTOR2 pos);
	string imageName;																		// 表示ｱﾆﾒｰｼｮﾝ名
	VECTOR2 divSize;																		// 分割ｻｲｽﾞ
	VECTOR2 divCnt;																			// 分割数
	DIR dir;																				// 進行方向

	bool visible;																			// 表示・非表示
};

