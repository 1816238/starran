#include "SpeedMng.h"



void SpeedMng::move(void)
{
	time+=SPEED;
}

int SpeedMng::GetTime(void)
{
	return time;
}

SpeedMng::SpeedMng()
{
	time = 0;
}


SpeedMng::~SpeedMng()
{
}
