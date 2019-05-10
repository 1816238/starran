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
	
	ClickOld = Click;
	Click = GetMouseInput();

	wheel.old = wheel.now;
	wheel.now = GetMouseWheelRotVol() % 2;
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

const bool GameCtl::GetClick(int mouse_type, KEY_TYPE type) const
{

	if (type == OLD)
	{
		return ClickOld & mouse_type;
	}
	return Click & mouse_type;
}

const bool GameCtl::WheelCheck(KEY_TYPE type) const
{
	if (type == OLD)
	{
		return wheel.old;
	}
	return wheel.now;

}
