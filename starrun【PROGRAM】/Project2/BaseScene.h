#pragma once
#include <memory>

#define SCREEN_SIZE_X 1280
#define SCREEN_SIZE_Y 680

#define GAME_SCREEN_X 40
#define GAME_SCREEN_Y 75

#define GAME_SCREEN_SIZE_X 640
#define GAME_SCREEN_SIZE_Y 480

#define CHIP_SIZE 20

#define BG_SPEED 1

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
