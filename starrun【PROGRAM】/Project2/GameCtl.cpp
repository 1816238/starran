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
	if (type == KEY_TYPE_OLD)
	{
		return dataOld;
	}
	return data;
}