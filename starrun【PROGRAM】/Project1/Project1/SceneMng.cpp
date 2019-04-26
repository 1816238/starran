#include <Dxlib.h>
#include "VECTOR2.h"
#include "ImageMng.h"
#include "EditCursor.h"
#include "EditScene.h"
#include "MapControl.h"
#include "GameController.h"
#include "SceneMng.h"

SceneMng::SceneMng()
{
	SysInit();
}

SceneMng::~SceneMng()
{
}

void SceneMng::Run(void)
{
	activeScene = make_unique<EditScene>();

	// ---------- ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{	
		gameCtl->UpDate();
		activeScene = activeScene->UpDate(move(activeScene), *gameCtl);//

	}
}

VECTOR2 SceneMng::GetScreenSize(void)
{
	return VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

bool SceneMng::SetDrawOffset(VECTOR2 vec)
{
	drawOffset = vec;
	return true;
}

const VECTOR2 & SceneMng::GetDrawOffset(void)
{
	return drawOffset;
}

/*↓返り値の型*/   /*↓型*/		/*↓引数*/
bool SceneMng::DelObjList(list<Obj*>::iterator itr)
{
	/*(*itr)->Draw()『*』と『->』では『->』のほうが強い*/;
	delete (*itr);
	return true;
}

//bool SceneMng::CheckEditMode(void)
//{
//	return activeScene->CheckEditMode();
//}

bool SceneMng::SysInit(void)
{
		// ｼｽﾃﾑ処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);				// true:window　false:ﾌﾙｽｸﾘｰﾝ
	SetWindowText("ボンバーマン.exe");
	if (DxLib_Init() == -1) return false;	// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);		// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
	gameCtl = make_unique<GameController>();
	return true;
}

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness)
{
	DxLib::DrawLine(vec1.x, vec1.y, vec2.x, vec2.y, Color, Thickness);
	return 0;
}
