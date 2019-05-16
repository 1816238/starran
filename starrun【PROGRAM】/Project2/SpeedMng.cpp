#include "SpeedMng.h"

#define SCREEN_SIZE 1280
#define MAP_SIZE SCREEN_SIZE*4
#define OFFSET 1280

void SpeedMng::move(void)
{
	int start;
	int end ;

	if (standardTime >= -1280 || standardTime >= 39680)
	{
		Seasonflag = 0;
	}
	if (standardTime >= 8960)
	{
		Seasonflag = 1;
	}
	if (standardTime >= 19200)
	{
		Seasonflag = 2;
	}
	if (standardTime >= 29440)
	{
		Seasonflag = 3;
	}
	
	//Seasonflag += (standardTime % 10240 == 10239 ? 1 : 0);

	start = -1280;
	end = 5120;
	speedFlag[Main] = (standardTime >= start + Seasonflag * MAP_SIZE * 2 && standardTime <= end + Seasonflag * MAP_SIZE * 2 ? true : false);

	start = 3840;
	end = 10240;
	speedFlag[Sub] = (standardTime >= start + Seasonflag * MAP_SIZE * 2 && standardTime <= end + Seasonflag * MAP_SIZE * 2 ? true : false);
	if (standardTime <= 0)
	{
		start = 0-1280;
		end = 0;
		speedFlag[Sub] = (standardTime >= start + Seasonflag * MAP_SIZE * 2 && standardTime <= end + Seasonflag * MAP_SIZE * 2 ? true : false);


	}
	/*switch (Seasonflag)
	{
	case 0:

		if (standardTime >= -1280 && standardTime <= 5120)
		{
			speedFlag[Main] = true;
		}
		else {
			speedTime[Main] = false;
		}
		break;
	case 1:
		if (standardTime >= 8960 && standardTime <= 15360)
		{
			speedTime[Main] = true;
		}
		else {
			speedTime[Main] = false;
		}
		break;
	case 2:
		if (standardTime >= 1920 && standardTime <= 25600)
		{
			speedTime[Main] = true;
		}
		else {
			speedTime[Main] = false;
		}
		break;
	case 3:
		if (standardTime >= 29440 && standardTime <= 34560)
		{
			speedTime[Main] = true;
		}
		else {
			speedTime[Main] = false;
		}
		break;
	case 4:
		break;
	default:
		break;
	}*/


	
	// if (standardTime >= 39680)
	//{
	//	speedTime[Main] = true;
	//}
	//‰ÁŽZˆ—
	speedTime[Main] += (speedFlag[Main] ? speed : 0);
	speedTime[Sub] += (speedFlag[Sub] ? speed : 0);
	//ŠeêŠ‚ÌãŒÀ
	if (speedTime[Sub] > MAP_SIZE+SCREEN_SIZE||speedFlag[Sub]==false)
	{
		speedTime[Sub] = -SCREEN_SIZE;
		//speedFlag[Sub] = false;
	}
	if (speedTime[Main] > MAP_SIZE||speedFlag[Main]==false)
	{
		speedTime[Main] = -SCREEN_SIZE;
		//speedFlag[Main] = false;
	}
	if (standardTime > MAP_SIZE * 8)
	{
		standardTime = -1280;
		Seasonflag = 0;
	}
	standardTime += speed;
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
	if (type == MapType::Std)
	{
		return standardTime;
	}
	else {
		return speedTime[type];

	}
}

bool SpeedMng::GetFlag(MapType type)
{
	return speedFlag[type];
}

bool SpeedMng::Init(void)
{
	speedTime[Main] = -1280;
	speedTime[Sub] =0;
	yellowstar = 0;
	SpeedCnt = 0;
	speed = SPEED;
	speedFlag[Main] = true;
	speedFlag[Sub] = false;
	standardTime = -1280;
	return false;
	Seasonflag = 0;
}

SpeedMng::SpeedMng()
{
	Init();
}


SpeedMng::~SpeedMng()
{
}
