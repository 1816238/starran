#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"
#include "MAP_ID.h"

enum class FIRE_ACT
{
	NON,		//　延焼する
	STOP,		//　延焼しない
	STOP_ER,	//　延焼せずにそのﾏｽを消す
	POP_ENEMY,	//　延焼した上で敵の出現
	ERR,		//　ｴﾗｰ
	MAX
};



#define lpMapControl MapControl::GetInstance()

// 計算定義
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
	void  Draw(bool EditFlag);									//map画像の描画
	//void  Draw_Fire(void);
	bool  SetUp(const VECTOR2& size ,const VECTOR2& chipsize,const VECTOR2 drawOffSet);
	bool  SetMapData(const VECTOR2& pos,MAP_ID id );			// 画像を配置しようとしている場所がmapの範囲内かの判定
	//bool  SetMapData_Fire(const VECTOR2 &pos, FIRE_DIR dir);

	//MAP_ID GetMapDate(const VECTOR2& pos/*座標*/);		// 指定した座標の情報の取得
	//unsigned int GetMapDate_Fire(const VECTOR2& pos/*座標*/);		// 指定した座標の情報の取得

	bool  MapSave(sharedListObj objList);						// 新しく制作したﾏｯﾌﾟ情報のｾｰﾌﾞ及びSUMﾁｪｯｸ
	bool  MapLoad(sharedListObj objList,bool objFlag);			// 保存されたﾏｯﾌﾟ情報の読み込み及びSUMﾁｪｯｸ

	//bool  SetUpGameObj(sharedListObj objList, bool DrawFlag);

	const VECTOR2 & GetChipSize(void);
private:
	MapControl();
	~MapControl();

	//void InitTblData(void);			// 爆風用回転ﾃｰﾌﾞﾙの初期化用	

	vector<MAP_ID> mapDataBace;		// mapの情報を入れておく配列（1次元目）
	vector<MAP_ID*> mapData;		// mapの情報を入れておく配列（2次元目）
	//vector<unsigned int > mapDataBace_Fire;		// 爆風の情報を入れておく配列（1次元目）4ﾊﾞｲﾄある
	//vector<unsigned int*> mapData_Fire;			// 爆風の情報を入れておく配列（2次元目）4ﾊﾞｲﾄある

	//array<double, static_cast<int>(FIRE_DIR::MAX)>rotPtnTbl;		// 爆風用回転ﾃｰﾌﾞﾙ
	//FIRE_ACT_TBL_ARRAY fireActTbl;		// 爆風用回転ﾃｰﾌﾞﾙ

	VECTOR2 mapSize;				// mapの縦と横を入れておく変数
	VECTOR2 chipSize;				// 分割後の1つ当たりの画像のｻｲｽﾞを入れておく変数
	VECTOR2 drawOffSet;				// どれだけずらすかの数値を入れておく変数
	
	int bgImage;					//背景ｸﾞﾗ用ﾊﾝﾄﾞﾙ

	template<typename mapType, typename idType>
	bool SetData(mapType maps , const VECTOR2& pos, idType id);
	
	template<typename mapType, typename idType>
	idType GetDate(mapType maps, const VECTOR2& pos/*座標*/, idType defID);		// 指定した座標の情報の取得
};


