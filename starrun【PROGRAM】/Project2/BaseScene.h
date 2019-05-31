#pragma once
#include <memory>

#define SCREEN_SIZE_X 1280
#define SCREEN_SIZE_Y 680

#define GAME_SCREEN_X 40
#define GAME_SCREEN_Y 75

#define GAME_SCREEN_SIZE_X 640
#define GAME_SCREEN_SIZE_Y 480

#define SEASONE_LIM	(SCREEN_SIZE_X * 3)

#define GIMMICK_POP_X (SCREEN_SIZE_X - (SCREEN_SIZE_X / 2 - SCREEN_SIZE_X / 3))

#define CHIP_SIZE 32

#define ENEMY_DEF_HP 100

#define ENEMY_DEF_FREQUENCY	10

#define BG_SPEED 1

#define EFFECT_TIME 5

#define SOUND_METEO "Sound/SE/earth-tremor1.mp3"

#define PI    3.1415926535897932384626433832795f

enum SEASONE
{
	SPRING,
	SUMMER, 
	AUTUMN,
	WINTER,
	SEASONE_MAX
};

class BaseScene;
class GameCtl;

using namespace std;

using unique_Base = unique_ptr<BaseScene>;

class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base UpDate(unique_Base own, const GameCtl &controller) = 0;
	virtual bool CheckEditMode(void)
	{
		return false;
	};
private:
	virtual int Init(void) = 0;
};
