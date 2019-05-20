#include "SpeedMng.h"

#define SCREEN_SIZE 1280
#define MAP_SIZE SCREEN_SIZE*4
#define OFFSET 1280

void SpeedMng::move(void)
{
	int start;
	int end ;
	//‹Gß‚Ì•Ï‚í‚è–Ú
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
	//ƒTƒuÏ¯Ìß‚Ì‹Gß‚Ì•Ï‚í‚è–Ú
	if (standardTime >= -1280 || standardTime >= 40960)
	{
		subseasonFlag = 0;
	}
	if (standardTime >= 10240)
	{
		subseasonFlag = 1;
	}
	if (standardTime >= 20480)
	{
		subseasonFlag = 2;
	}
	if (standardTime >= 30720)
	{
		subseasonFlag = 3;
	}

	//Seasonflag += (standardTime % 10240 == 10239 ? 1 : 0);

	start = -1280 + Seasonflag * MAP_SIZE * 2;
	end = 5120 + Seasonflag * MAP_SIZE * 2;
	speedFlag[Main] = (standardTime >= start && standardTime <= end  ? true : false);

	start = 3840 + subseasonFlag * MAP_SIZE * 2;
	end = 10240 + subseasonFlag * MAP_SIZE * 2;
	speedFlag[Sub] = (standardTime >= start && standardTime <= end  ? true : false);
	if (standardTime <= 0)
	{
		start = 0-1280 + subseasonFlag * MAP_SIZE * 2;
		end = 0 + subseasonFlag * MAP_SIZE * 2;
		speedFlag[Sub] = (standardTime >= start && standardTime <= end ? true : false);


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
	if (standardTime > MAP_SIZE * 8-SCREEN_SIZE)
	{
		reset();
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
	
	yellowstar = 0;
	speed = SPEED;
	time = 0;
	reset();
	return false;
	
}

SpeedMng::SpeedMng()
{
	Init();
}


SpeedMng::~SpeedMng()
{
}

void SpeedMng::reset(void)
{
	speedTime[Main] = -1280;
	speedTime[Sub] =MAP_SIZE-SCREEN_SIZE;
	speedFlag[Main] = true;
	speedFlag[Sub] = false;
	standardTime = -1280;
	Seasonflag = 0;
	subseasonFlag=0;
}
