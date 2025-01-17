#pragma once
#include <vector>
#include "VECTOR2.h"
#include "classObj.h"

enum MAP_ID
{
	MAP_ID_NON,
	MAP_ID_CLOUD1,
	MAP_ID_CLOUD2,
	MAP_ID_CLOUD3,
	MAP_ID_BLUE,
	MAP_ID_YELLOW,
	MAP_ID_GREEN,
	MAP_ID_RED,
	MAP_ID_PURPLE,
	MAP_ID_CLOUD_DOWN1,
	MAP_ID_CLOUD_DOWN2,
	MAP_ID_CLOUD_DOWN3,
	MAP_ID_FULL_MOON,
	MAP_ID_HALF_MOON,
	MAP_ID_CRESCENT_MOON,
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
	void Draw(bool EditFlag);		//map画像の描画
	bool SetUp(const VECTOR2& size, const VECTOR2& chipsize, const VECTOR2 drawOffSet);
	bool SetMapData(const VECTOR2& pos, MAP_ID id);			//画像を配置しようとしている場所がmapの範囲内かの判定
	MAP_ID GetMapDate(const VECTOR2& pos/*座標*/);					//指定した座標の情報の取得
	bool MapSave(sharedListObj objList);					//新しく制作したﾏｯﾌﾟ情報のｾｰﾌﾞ及びSUMﾁｪｯｸ
	bool MapLoad(sharedListObj objList, bool objFlag);		//保存されたﾏｯﾌﾟ情報の読み込み及びSUMﾁｪｯｸ
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	const VECTOR2 & GetChipSize(void);
	void SetPos(VECTOR2 pos);
private:
	MapControl();
	~MapControl();
	vector<MAP_ID> mapDataBace;		//mapの情報を入れておく配列（1次元目）
	vector<MAP_ID*> mapData;			//mapの情報を入れておく配列（2次元目）
	VECTOR2 mapSize;			//mapの縦と横を入れておく変数
	VECTOR2 chipSize;			//分割後の1つ当たりの画像のｻｲｽﾞを入れておく変数
	VECTOR2 drawOffSet;		//どれだけずらすかの数値を入れておく変数
	VECTOR2 pos;

};

