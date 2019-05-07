#include <DxLib.h>
#include "GameCtl.h"



GameCtl::GameCtl()
{
}


GameCtl::~GameCtl()
{
}

bool GameCtl::UpDate(void)
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);		// ‘S‚Ä‚ÌƒL[‚Ì“ü—Íó‘Ô‚ğ“¾‚é

	return true;
}

const KEY_ARRAY & GameCtl::GetCtl(KEY_TYPE type) const
{
	if (type == OLD)
	{
		return dataOld;
	}
	return data;
}

const VECTOR2 &GameCtl::GetChipPos(VECTOR2 pos) const
{

	if (pos.x < 0)
	{
		pos.x = 0;
	}
	if (pos.x > (1280 * 3))
	{
		pos.x = (1280 * 3);
	}
	pos.x -= (GetMouseWheelRotVol() % 2) * 48;


	return pos;
}
