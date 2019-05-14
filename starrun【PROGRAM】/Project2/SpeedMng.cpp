#include "SpeedMng.h"



void SpeedMng::move(void)
{
	for (int s = 0; s < Max; s++)
	{
		if (speedFlag[s])
		{
			speedTime[s] += speed;
		}
	}
if (speedTime[Main] > 1280 * 2&&speedFlag[Main])
	{
		//time[Sub] = -1280;
		speedFlag[Sub] = true;
		SpeedCnt++;
	}
	if (speedTime[Sub] > 1280 * 2&speedFlag[Sub])
	{
		//time[Main] = -1280;
		speedFlag[Main] = true;
		SpeedCnt++;
	}

	if(speedTime[Main]>1280*4)
	{
		speedTime[Main] = -1280;
		speedFlag[Main] = false;
	}
	
	if (speedTime[Sub] > 1280 * 4)
	{
		speedTime[Sub] = -1280;
		speedFlag[Sub] = false;
	}
	time++;
}

int SpeedMng::GetTime(void)
{
	return time;
}

void SpeedMng::AddStar(void)
{
	yellowstar++;
	speed += (yellowstar % 30==29?1:0);

}

int SpeedMng::GetYellow(void)
{
	return yellowstar;
}

int SpeedMng::GetSpeed(MapType type)
{
	return speedTime[type];
}

bool SpeedMng::GetFlag(MapType type)
{
	return speedFlag[type];
}

SpeedMng::SpeedMng()
{
	speedTime[Main] = 0;
	speedTime[Sub] = -1280;
	yellowstar = 0;
	SpeedCnt = 0;
	speed = SPEED;
	speedFlag[Main] = true;
	speedFlag[Sub] = false;
}


SpeedMng::~SpeedMng()
{
}
