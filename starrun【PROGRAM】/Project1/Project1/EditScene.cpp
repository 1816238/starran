#include <array>
#include "Dxlib.h"
#include "SceneMng.h"
#include "classObj.h"
#include "ImageMng.h"
#include "MapControl.h"
#include "EditCursor.h"
#include "GameController.h"
#include "ImageMng.h"
#include "VECTOR2.h"
#include "EditScene.h"

EditScene::EditScene()
{
	Init();
	VECTOR2 offset( lpSceneMng.GetDrawOffset() );

	Color = GetColor( 0, 0, 0 );
	 string_Tbl = 
	{	"Ctrlｷｰもしくは1〜9ｷｰでﾊﾟﾈﾙの変更",
		"spaceｷｰで確定",
		"ﾃﾝｷｰの2,4,6,8ｷｰもしくは矢印ｷｰでｶｰｿﾙの移動",
		"F5ｷｰでMap情報のﾛｰﾄﾞ",
		"F6ｷｰでMap情報のｾｰﾌﾞ"
	};
}

EditScene::~EditScene()
{
}

unique_Base EditScene::UpDate( unique_Base own, const GameController & controller )
{

	SetMainWindowText("【ボンバーマン.exe】MODE_EDIT");

	if ( controller.GetCtl(KEY_TYPE::NOW)[KEY_INPUT_F5] )
	{
		//ﾛｰﾄﾞ
		if ( MessageBox(NULL, "エディット内容をロードしますか？",
						"確認ダイアログ", MB_YESNO) == IDYES )
		{
			lpMapControl.MapLoad( objList,true );
		}
	}
	if ( controller.GetCtl(KEY_TYPE::NOW)[KEY_INPUT_F6] )
	{
		//ｾｰﾌﾞ
		if ( MessageBox(NULL, "エディット内容をセーブしますか？",
						"確認ダイアログ", MB_YESNO) == IDYES )
		{
			lpMapControl.MapSave( objList );
		}
	}
	for ( auto itr = objList->begin(); itr != objList->end(); itr++ )
	{
		(*itr)->UpDate( controller,objList );
	}
	EditDraw();
	return move(own);
}

bool EditScene::EditDraw(void)
{
	VECTOR2 tmp1( 0,0 );
	VECTOR2 tmp2( 0,GAME_SCREEN_SIZE_Y );


	ClsDrawScreen();
	
	lpMapControl.Draw(true);
	auto itr = objList->begin();
	for ( auto Itr = objList->begin(); Itr != objList->end(); Itr++ )
	{
		(*itr)->Draw();
	}

	for ( ; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += CHIP_SIZE )
	{
		tmp2.x = tmp1.x;
		EditCursor::GetInstance().SetMove_Mouse();
		DrawLine(tmp1 + EditCursor::GetInstance().GetChipPos(),tmp2 + EditCursor::GetInstance().GetChipPos(), GetColor( 0 , 255 , 255 ) , true );
	}

	tmp1 = VECTOR2( 0, 0 );
	tmp2.x = GAME_SCREEN_SIZE_X;
	
	for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += CHIP_SIZE )
	{
		tmp2.y = tmp1.y;
		DrawLine(tmp1 , tmp2 , GetColor( 0 , 255 , 255 ) , true);
	}

	for (int n = 3; n <= 11; n++)
	{
	/*	DrawGraph( static_cast<int>((SCREEN_SIZE_X - CHIP_SIZE) * 1.5), (CHIP_SIZE / 2) + (CHIP_SIZE + 5)*n
			, lpImageMng.GetID("image/map.png")[n], true );
		DrawFormatString( ( offset.x + offset.x/2 ) + GAME_SCREEN_SIZE_X , (CHIP_SIZE / 2) + (CHIP_SIZE + 5)*n , GetColor( 0 , 0 , 0 ), "ｷｰ  %d" , n-2 );*/
	}

	ScreenFlip();
	return true;
}

int EditScene::Init(void)
{
	if (!objList)//objListの中に何も入ってないと例外が走るので何も入ってない場合はobjListの中に入れる処理を行う
	{
		objList = std::make_shared<sharedObjList>();
	}
	objList->clear();
	lpMapControl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	auto obj = AddObjList()(objList, std::make_unique<EditCursor>(lpSceneMng.GetDrawOffset()));
	(*obj)->init("image/map.png", VECTOR2(20, 20), VECTOR2(4, 3));
	return 0;
}
