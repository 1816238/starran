//////////////////////////////////////////////////////////////////////
///////////////////// 「ゲーム制作」 基本ｿｰｽ  ////////////////////////
//////////////////////////////////////////////////////////////////////
using namespace std;
#include <stdlib.h>
#include "Dxlib.h"	// DxLibﾗｲﾌﾞﾗﾘを使用する
#include "SceneMng.h"
#include "ImageMng.h"

// ---------- WinMain関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SceneMng::GetInstance().Run();

	DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
	return 0;
}

void Destroy(void)
{
}