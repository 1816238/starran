#include "SpeedMng.h"

#define SCREEN_SIZE 1280
#define MAP_SIZE SCREEN_SIZE*4
#define OFFSET 1280

void SpeedMng::move(void)
{
	int start;
	int end ;
	if (Seasonflag != 4 && subseasonFlag != 4)
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

	}
	//���Z����
	speedTime[Main] += (speedFlag[Main] ? speed : 0);
	speedTime[Sub] += (speedFlag[Sub] ? speed : 0);
	//�e�ꏊ�̏��
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
	switchFlag.resize(10);
	switchFlag = {
		-1280,		//�t����1
		8960,		//�ď���
		19200,		//�H����
		29440,		//�~����
		39680,		//�t����2
		-1280 ,		//�T�u�t����1
		10240,		//�T�u�ď���
		20480,		//�T�u�H����
		30720,		//�T�u�~����
		40960		//�T�u�t����2
	};
	reset();
	return false;
	
}

unsigned int SpeedMng::GetSeasoonFlag(MapType type)
{
	if (type == Main)
	{
		return Seasonflag;
	}
	return subseasonFlag;
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
