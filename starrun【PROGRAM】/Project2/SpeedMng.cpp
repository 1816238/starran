#include "SpeedMng.h"

#define SCREEN_SIZE 1280
#define MAP_SIZE SCREEN_SIZE*4

void SpeedMng::move(void)
{
	if (time)
	{
		speedFlag[Main] = true;
	}
	if (time)
	{
		speedFlag[Sub] = true;
	}
	speedTime[Main] += (speedFlag[Main] ? speed : 0);
	speedTime[Sub] += (speedFlag[Sub] ? speed : 0);


	//ŠeêŠ‚ÌãŒÀ
	if (speedTime[Sub] > MAP_SIZE)
	{
		speedTime[Sub] = -SCREEN_SIZE;
		speedFlag[Sub] = false;
	}
	if (speedTime[Main] > MAP_SIZE)
	{
		speedTime[Main] = -SCREEN_SIZE;
		speedFlag[Main] = false;
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
	speed += (yellowstar % 30==19?1:0);

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

bool SpeedMng::Init(void)
{
	speedTime[Main] = 0;
	speedTime[Sub] = -SCREEN_SIZE;
	yellowstar = 0;
	SpeedCnt = 0;
	speed = SPEED;
	speedFlag[Main] = true;
	speedFlag[Sub] = false;
	return false;
}

SpeedMng::SpeedMng()
{
	Init();
}


SpeedMng::~SpeedMng()
{
}
