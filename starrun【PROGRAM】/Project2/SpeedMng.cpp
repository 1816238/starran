#include "SpeedMng.h"
#include <DxLib.h>
#include"MapControl.h"
#define SCREEN_SIZE 1280
#define MAP_SIZE SCREEN_SIZE*4
#define OFFSET 1280

void SpeedMng::move(void)
{
	int start;
	int end ;
	/*if (Seasonflag != 4 && subseasonFlag != 4)
	{
		for (int i = 0; i < switchFlag.size(); i++)
		{
			if (standardTime >= switchFlag[i])
			{
				if (i / 5==0)
				{
					Seasonflag = i;
					if (i%5 == 4)
					{
						Seasonflag = 0;
					}
				}
				else {
					subseasonFlag = i%5;
					if (i%5 == 4)
					{
						subseasonFlag = 0;
					}
				}
			}
		}
		//Seasonflag += (standardTime % 10240 == 10239 ? 1 : 0);

		start = -1280 + Seasonflag * MAP_SIZE * 2;
		end = 5120 + Seasonflag * MAP_SIZE * 2;
		speedFlag[Main] = (standardTime >= start && standardTime <= end ? true : false);

		start = 3840 + subseasonFlag * MAP_SIZE * 2;
		end = 10240 + subseasonFlag * MAP_SIZE * 2;
		speedFlag[Sub] = (standardTime >= start && standardTime <= end ? true : false);
		if (standardTime <= 0)
		{
			start = 0 - 1280 + subseasonFlag * MAP_SIZE * 2;
			end = 0 + subseasonFlag * MAP_SIZE * 2;
			speedFlag[Sub] = (standardTime >= start && standardTime <= end ? true : false);
		}
	}
	else {

	}*/
	bool flag=false;
	for (int a = 0; a < static_cast<int>(SEASON::MAX); a++)
	{
		
		if (standardTime >= switchFlag[a] && standardTime <= switchFlag[a] + MAP_SIZE+1280)
		{
			Seasonflag[a] = true;
			flag = true;
		}
		else {
			Seasonflag[a] = false;
			
		}

	}
	speedFlag[Main] = (flag ? true : false);
	if ((standardTime >= switchFlag[4] && standardTime <=1280))
	{
		speedFlag[Sub] = true;
	}
	else {
		speedFlag[Sub] = false;
	}
	if (standardTime >= switchFlag[5] && standardTime <= switchFlag[5] + 1280*2)
	{
		speedFlag[Sub2] = true;
	}
	else {
		speedFlag[Sub2] = false;
	}
	

	//â¡éZèàóù
	speedTime[Main] += (speedFlag[Main] ? speed : 0);
	speedTime[Sub] += (speedFlag[Sub] ? speed : 0);
	speedTime[Sub2] += (speedFlag[Sub2] ? speed : 0);
	for (int a = 0; a < static_cast<int>(SEASON::MAX); a++)
	{
		seasonTime[a] += (Seasonflag[a] ? speed : 0);
		
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		speed += 2;
	}
	else
	{
		speed = SPEED;
	}
	//äeèÍèäÇÃè„å¿
	if (speedTime[Sub] > MAP_SIZE+SCREEN_SIZE||speedFlag[Sub]==false)
	{
		speedTime[Sub] = -SCREEN_SIZE;
		speedFlag[Sub] = false;
	}
	/*if (speedTime[Main] > MAP_SIZE||speedFlag[Main]==false)
	{
		speedTime[Main] = -SCREEN_SIZE;
		speedFlag[Main] = false;
	}*/
	if (standardTime > MAP_SIZE * 8-SCREEN_SIZE)
	{
		reset();
	}
	if (speedFlag[Sub2] && !Seasonflag[static_cast<int>(SEASON::WINTER)])
	{
		reset();
		lpMapControl.ReLoadMap();
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
	speed = SPEED + yellowstar / 15;

}

int SpeedMng::GetYellow(void)
{
	return yellowstar;
}

int SpeedMng::GetSpeed(MapType type,SEASON season)
{
	if (type == MapType::Std)
	{
		return standardTime;
	}
	else if(type==Sub||type==Sub2){
		return speedTime[type];
	}
	else {
		return seasonTime[static_cast<int>(season)];
	}

}

bool SpeedMng::GetFlag(MapType type,SEASON season)
{
	if (season == SEASON::MAX)
	{
		return speedFlag[type];

	}
	else {
		return Seasonflag[static_cast<int>(season)];
	}
}

bool SpeedMng::Init(void)
{
	
	yellowstar = 0;
	speed = SPEED;
	time = 0;
	switchFlag.resize(6);
	switchFlag = {
		-1280,		//ètèåè1
		3840,		//âƒèåè
		8960,		//èHèåè
		14080,		//ì~èåè
		-1280,			//ÉTÉuÇÃèåè
		19200		//ÉTÉuÇÃèåè2
	};
	Seasonflag.resize(static_cast<int>(SEASON::MAX));
	reset();
	return false;
	
}

bool SpeedMng::GetSeasonFlag(MapType type,SEASON season)
{
	if (type == Main)
	{
		return Seasonflag[static_cast<int>(season)];
	}
	return subseasonFlag;
}

SEASON SpeedMng::GetSeason(void)
{
	if (speedFlag[Sub])
	{
		if (Seasonflag[static_cast<int>(SEASON::SPRING)])
		{
			if (seasonTime[static_cast<int>(SEASON::SPRING)] > 0)
			{
				return SEASON::SPRING;
			}
			else {
				return SEASON::MAX;
			}
		}
		else {
			return SEASON::MAX;
		}
	}
	if (Seasonflag[static_cast<int>(SEASON::SPRING)])
	{
		if (Seasonflag[static_cast<int>(SEASON::SUMMER)])
		{
			if (seasonTime[static_cast<int>(SEASON::SUMMER)] > 0)
			{
				return SEASON::SUMMER;
			}
			else {
				return SEASON::SPRING;
			}
		}
		else {
			return SEASON::SPRING;
		}
	}
	else if (Seasonflag[static_cast<int>(SEASON::SUMMER)])
	{
		if (Seasonflag[static_cast<int>(SEASON::AUTUMN)])
		{
			if (seasonTime[static_cast<int>(SEASON::AUTUMN)] > 0)
			{
				return SEASON::AUTUMN;
			}
			else {
				return SEASON::SUMMER;
			}
		}
		else {
			return SEASON::SUMMER;
		}
	}
	else if(Seasonflag[static_cast<int>(SEASON::AUTUMN)]){
		if (Seasonflag[static_cast<int>(SEASON::WINTER)])
		{
			if (seasonTime[static_cast<int>(SEASON::WINTER)] > 0)
			{
				return SEASON::WINTER;
			}
			else {
				return SEASON::AUTUMN;
			}
		}
		else {
			return SEASON::AUTUMN;
		}
	}
	else if (Seasonflag[static_cast<int>(SEASON::WINTER)])
	{
		if (speedFlag[Sub2])
		{
			if (speedTime[Sub2] > -64)
			{
				return SEASON::MAX;
			}
			else {
				return SEASON::WINTER;
			}
		}
		else {
			return SEASON::WINTER;
		}

	}
	else {
		return SEASON::MAX;
	}
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
	speedTime[Sub2] = -1280;
	speedFlag[Main] = true;
	speedFlag[Sub] = false;
	speedFlag[Sub] = false;
	standardTime = -1280;
	for (auto flag : Seasonflag)
	{
		flag = false;
	}
	for (auto speed=0;speed<static_cast<int>(SEASON::MAX);speed++)
	{
		seasonTime[speed] =-1280;
	}
	subseasonFlag=false;
}
