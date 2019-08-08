#include "DxLib.h"
#include "ImageMng.h"
#include "GameScene.h"
#include "SceneMng.h"
#include "SoundMng.h"
#include "MapControl.h"
#include "GameCtl.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::UpDate(unique_Base own, const GameCtl & controller)
{
	ClickCheckOld = ClickCheck;
	ClickCheck = (GetMouseInput()&MOUSE_INPUT_LEFT?true:false);
	VECTOR2 Mpos = {0,0};
	GetMousePoint(&Mpos.x, &Mpos.y);
	if ((ClickCheck&(~ClickCheckOld)) && (Mpos > start&&Mpos < start + VECTOR2{ 320,160 }))
	{
		lpSoundMng.PlaySound("Sound/SE/decision27.mp3", DX_PLAYTYPE_BACK);
		lpSoundMng.StopSound("Sound/BGM/milkyway.mp3");

		return std::make_unique<GameScene>(mode);
	}

	if (controller.GetCtl(KEY_TYPE::NOW)[KEY_INPUT_SPACE]
		& (~controller.GetCtl(KEY_TYPE::OLD)[KEY_INPUT_SPACE]))
		//ﾋﾞｯﾄ演算をして~でﾋﾞｯﾄを反転させる反転させた情報と比べ判定する
	{
		return std::make_unique<GameScene>(mode);
	}
	auto MODE = [&](VECTOR2 pos, VECTOR2 offset,Mode mode)
	{
		if ((ClickCheck&(~ClickCheckOld)) && (Mpos > pos&&Mpos < pos + offset))
		{
			this->mode = mode;
		}
	};
	MODE(VECTOR2(120,194),VECTOR2(easy_size.x, easy_size.y), Mode::Easy);
	MODE( VECTOR2(120,304),VECTOR2(Normal_size.x, Normal_size.y),Mode::Normal);
	MODE( VECTOR2(120,422),VECTOR2(Hard_size.x, Hard_size.y),Mode::Hard);

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	//叙述【ﾌﾟﾚﾃﾞｨｹｰﾄ】
	(*objList).remove_if([](uniqueObj& obj) {return obj->CheckEnd(); });
	
	TitleMove();
	TitleDraw();
	return std::move(own);		//所有権を移す
}

bool TitleScene::TitleDraw(void)
{
	ClsDrawScreen();
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, IMAGE_ID("image/back.jpg")[0], true);

	//星座の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(int(cnt % 512 - 256)));
	DrawRectGraph(pos.x,pos.y ,drawChip.x,drawChip.y,250,250, IMAGE_ID("image/constellation.png")[0], true,false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(120, 194, IMAGE_ID("image/Easy.png")[0], true);
	DrawGraph(120, 308, IMAGE_ID("image/Normal.png")[0], true);
	DrawGraph(120, 422, IMAGE_ID("image/Hard.png")[0], true);
	DrawRotaGraph2(70, 194 + 194/4 + 114 * static_cast<int>(mode),200,200, 0.2f, time / DX_PI_F * 2, IMAGE_ID("image/boss_escap.png")[0], true, false);
	//コメントの描画
	if (cnt / 60 % 2)
	{
		DrawGraph(start.x,start.y, IMAGE_ID("image/start.png")[0], true);
		DrawString(start.x+30, start.y+100, "クリックでスタート", 0xffff00);

	}
	DrawRotaGraph(300, 80, 1.5f,0,IMAGE_ID("image/star run.png")[0], true, false);
	time+= 0.1;
	ScreenFlip();
	return false;
}

void TitleScene::TitleMove(void)
{

	if (cnt % 512-256 == 0)
	{
		pos = { rand() % (SCREEN_SIZE_X - 250) ,rand() % (SCREEN_SIZE_Y - 500) + 250 };
		drawChip = { (rand() % 4) * 250,(rand() % 3) * 250 };
	}
	cnt++;
}

int TitleScene::Init(void)
{
	if (!objList)//objListの中に何も入ってないと例外が走るので何も入ってない場合はobjListの中に入れる処理を行う
	{
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	SetWindowText("AGS.exe Title");
	lpSoundMng.PlaySound("Sound/BGM/wind1.mp3", DX_PLAYTYPE_LOOP);
	lpSoundMng.PlaySound("Sound/BGM/space.mp3", DX_PLAYTYPE_LOOP);
	lpSoundMng.ChangeVol(40, "Sound/BGM/wind1.mp3");
	lpSoundMng.ChangeVol(30, "Sound/BGM/space.mp3");
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapControl.SetUp(VECTOR2(SCREEN_SIZE_X,SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	cnt = 255;
	pos = { 0, 250 };
	drawChip = { 0, 0};
	ClickCheck = false;
	ClickCheckOld = false;
	start = { 800, 500 };
	GetGraphSize(IMAGE_ID("image/Easy.png")[0], &easy_size.x, &easy_size.y);
	GetGraphSize(IMAGE_ID("image/Normal.png")[0], &Normal_size.x, &Normal_size.y);
	GetGraphSize(IMAGE_ID("image/Hard.png")[0], &Hard_size.x, &Hard_size.y);
	return 0;
}
