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

	// ---------- �ް�ٰ��
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

/*���Ԃ�l�̌^*/   /*���^*/		/*������*/
bool SceneMng::DelObjList(list<Obj*>::iterator itr)
{
	/*(*itr)->Draw()�w*�x�Ɓw->�x�ł́w->�x�̂ق�������*/;
	delete (*itr);
	return true;
}

//bool SceneMng::CheckEditMode(void)
//{
//	return activeScene->CheckEditMode();
//}

bool SceneMng::SysInit(void)
{
		// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);				// true:window�@false:�ٽ�ذ�
	SetWindowText("�{���o�[�}��.exe");
	if (DxLib_Init() == -1) return false;	// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);		// �ЂƂ܂��ޯ��ޯ̧�ɕ`��
	gameCtl = make_unique<GameController>();
	return true;
}

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness)
{
	DxLib::DrawLine(vec1.x, vec1.y, vec2.x, vec2.y, Color, Thickness);
	return 0;
}
