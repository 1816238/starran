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
	void Draw(bool TitleFlag);		//map画像の描画
	bool SetUp(const VECTOR2& size, const VECTOR2& chipsize, const VECTOR2 drawOffSet);
	bool SetMapData(const VECTOR2& pos, MAP_ID id, MapType type);			//画像を配置しようとしている場所がmapの範囲内かの判定
	MAP_ID GetMapDate(const VECTOR2& pos,MapType type);					//指定した座標の情報の取得,typeがtrueならmainのﾏｯﾌﾟﾃﾞｰﾀをfalseならsubのﾏｯﾌﾟﾃﾞｰﾀを返す
	bool MapLoad(string FileName,sharedListObj objList, bool objFlag,bool type);		//保存されたﾏｯﾌﾟ情報の読み込み及びSUMﾁｪｯｸ
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	const VECTOR2 & GetChipSize(void);
	bool GetSubFlag(void);
	bool init(void);
private:
	MapControl();
	~MapControl();
	MapDataBase mapDataBace;		//mapの情報を入れておく配列（1次元目）
	MapData mapData;			//mapの情報を入れておく配列（2次元目）
	VECTOR2 mapSize;			//mapの縦と横を入れておく変数
	VECTOR2 chipSize;			//分割後の1つ当たりの画像のｻｲｽﾞを入れておく変数
	VECTOR2 drawOffSet;		//どれだけずらすかの数値を入れておく変数
	VECTOR2 pos;
	bool SubFlag;
	array< int, int(SEASON_ID::MAX)> offset;
};

