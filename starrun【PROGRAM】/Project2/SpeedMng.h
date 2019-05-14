#pragma once

#include "VECTOR2.h"
class MapControl;
using namespace std;
#define lpSpeedMng SpeedMng::GetInstance()
#define Speed(x) SpeedMng::GetInstance().GetSpeed(x)	//Main��Ҳ݂����+���F�����̎擾��/10*30�ASub�Ż�ނ����+���F�����̎擾��/10*30���擾�ł���
#define SPEED 3

enum MapType {
	Main,
	Sub,
	Max
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
	int GetSpeed(MapType type);
	bool GetFlag(MapType type);
private:
	SpeedMng();
	~SpeedMng();
	int speedTime[Max];
	int yellowstar;
	int SpeedCnt;
	int speed;
	bool speedFlag[Max];
	int time;
};

