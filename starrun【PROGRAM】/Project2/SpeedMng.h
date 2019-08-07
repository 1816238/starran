#pragma once

#include <vector>
#include "VECTOR2.h"
class MapControl;
using namespace std;
#define lpSpeedMng SpeedMng::GetInstance()
#define Speed(x) SpeedMng::GetInstance().GetSpeed(x)	//Mainでﾒｲﾝのﾀｲﾑ+黄色い星の取得量/10*30、Subでｻﾌﾞのﾀｲﾑ+黄色い星の取得量/10*30が取得できる
#define SPEED 3

enum MapType {
	Main,
	Sub,
	Std,
	Max
};
enum class SEASON {
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER,
	MAX
};

class SpeedMng
{
public:
	static SpeedMng &GetInstance(void)
	{
		static SpeedMng s_Instance;
		return s_Instance;
	}
	void move(void);
	int GetTime(void);
	void AddStar(void);
	int GetYellow(void);
	int GetSpeed(MapType type,SEASON season=SEASON::MAX);
	bool GetFlag(MapType type);
	bool Init(void);
	SpeedMng(SpeedMng& in) {};
	void operator=(SpeedMng& in) {};
	bool GetSeasonFlag(MapType type,SEASON season=SEASON::MAX);
	vector<int> switchFlag;
private:
	SpeedMng();
	~SpeedMng();
	void reset(void);

	int speedTime[Max];
	int seasonTime[static_cast<int>(SEASON::MAX)];
	int yellowstar;
	int SpeedCnt;
	int speed;
	bool speedFlag[Max];	
	int time;				//経過時間
	int standardTime;		//speedflagの判定に使用する基本となるｶｳﾝﾄ
	vector<bool> Seasonflag;			//0で春、1で夏、2で秋、3で冬、4でEX
	bool subseasonFlag;
	
};

