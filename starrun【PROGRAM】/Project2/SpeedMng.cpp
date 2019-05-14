#include "SpeedMng.h"



void SpeedMng::move(void)
{
	for (int s = 0; s < Max; s++)
	{
		if (speedFlag[s])
		{
			time[s] += speed;
		}
	}
if (time[Main] > 1280 * 2&&speedFlag[Main])
	{
		//time[Sub] = -1280;
		speedFlag[Sub] = true;
		SpeedCnt++;
	}
	if (time[Sub] > 1280 * 2&speedFlag[Sub])
	{
		//time[Main] = -1280;
		speedFlag[Main] = true;
		SpeedCnt++;
	}

	if(time[Main]>1280*4)
	{
		time[Main] = -1280;
		speedFlag[Main] = false;
	}
	
	if (time[Sub] > 1280 * 4)
	{
		time[Sub] = -1280;
		speedFlag[Sub] = false;
	}

}

int SpeedMng::GetTime(MapType type)
{
	return time[type];
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
	return time[type];
}

SpeedMng::SpeedMng()
{
	time[Main] = 0;
	time[Sub] = -1280;
	yellowstar = 0;
	SpeedCnt = 0;
	speed = SPEED;
	speedFlag[Main] = true;
	speedFlag[Sub] = false;
}


SpeedMng::~SpeedMng()
{
}
