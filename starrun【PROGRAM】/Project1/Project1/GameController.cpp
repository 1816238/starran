#include "DxLib.h"
#include "EditCursor.h"
#include "GameController.h"

GameController::GameController()
{

}

GameController::~GameController()
{
}

bool GameController::UpDate(void)
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);		// ‘S‚Ä‚ÌƒL[‚Ì“ü—Íó‘Ô‚ğ“¾‚é

	return true;
}

const KEY_ARRAY & GameController::GetCtl(KEY_TYPE type) const
{
	if(type == KEY_TYPE::OLD)
	{
		return dataOld;
	}
	return data;
}


