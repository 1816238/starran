#include "SpeedMng.h"



void SpeedMng::move(void)
{
	time+=SPEED;

}

int SpeedMng::GetTime(void)
{
	return time;
}

void SpeedMng::AddStar(void)
{
	yellowstar++;
}

int SpeedMng::GetYellow(void)
{
	return yellowstar;
}

SpeedMng::SpeedMng()
{
	time = 0;
	yellowstar = 0;
}


SpeedMng::~SpeedMng()
{
}
