#pragma once

#include "VECTOR2.h"

using namespace std;
#define lpSpeedMng SpeedMng::GetInstance()
#define Time SpeedMng::GetInstance().GetTime()
#define SPEED 3
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
private:
	SpeedMng();
	~SpeedMng();
	int time;
};

