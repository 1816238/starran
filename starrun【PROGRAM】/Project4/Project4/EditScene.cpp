#include <array>
#include "Dxlib.h"
#include "classObj.h"
#include "ImageMng.h"
#include "MapControl.h"
#include "EditCursor.h"
#include "GameCtl.h"
#include "ImageMng.h"
#include "SceneMng.h"
#include "EditScene.h"


EditScene::EditScene()
{
	Init();
	VECTOR2 offset( lpSceneMng.GetDrawOffset() );

	Color = GetColor( 0, 0, 0 );
	 string_Tbl = 
	{	"Ctrl����������1�`9�������ق̕ύX",
		"space���Ŋm��",
		"�ݷ���2,4,6,8���������͖�󷰂Ŷ��ق̈ړ�",
		"F5����Map����۰��",
		"F6����Map���̾���"
	};
}

EditScene::~EditScene()
{
}

unique_Base EditScene::UpDate( unique_Base own, const GameCtl & controller )
{

	SetMainWindowText("�y�{���o�[�}��.exe�zMODE_EDIT");

	if ( controller.GetCtl(KEY_TYPE::NOW)[KEY_INPUT_F5] )
	{
		//۰��
		if ( MessageBox(NULL, "�G�f�B�b�g���e�����[�h���܂����H",
						"�m�F�_�C�A���O", MB_YESNO) == IDYES )
		{
			lpMapControl.MapLoad( objList,true );
		}
	}
	if ( controller.GetCtl(KEY_TYPE::NOW)[KEY_INPUT_F6] )
	{
		//����
		if ( MessageBox(NULL, "�G�f�B�b�g���e���Z�[�u���܂����H",
						"�m�F�_�C�A���O", MB_YESNO) == IDYES )
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
	//�J�[�\���̈ʒu�̕`��
	VECTOR2 CurPos = EditCursor::GetInstance().SetCur();
	CurPos.x = (CurPos.x / CHIP_SIZE * CHIP_SIZE) + CHIP_SIZE / 2;
	CurPos.y = (CurPos.y / CHIP_SIZE * CHIP_SIZE) + CHIP_SIZE / 2;
	CurPos.x += (EditCursor::GetInstance().ifCurShift() * 16);
	DrawBox(CurPos.x - CHIP_SIZE / 2, CurPos.y - CHIP_SIZE / 2, CurPos.x + CHIP_SIZE / 2, CurPos.y + CHIP_SIZE / 2, 0xff00ff, true);
	
	//������
	VECTOR2 Mpos;
	Mpos=EditCursor::GetInstance().SetMove_Mouse();
	for ( ; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += CHIP_SIZE )
	{
		tmp2.x = tmp1.x;
		DrawLine(  tmp1- Mpos,  tmp2 - Mpos, GetColor( 0 , 255 , 255 ) , true );
	}
	tmp1 = VECTOR2( 0, 0 );
	tmp2.x = GAME_SCREEN_SIZE_X;
	for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += CHIP_SIZE )
	{
		tmp2.y = tmp1.y;
		DrawLine(tmp1 , tmp2 , GetColor( 0 , 255 , 255 ) , true);
	}
		DrawFormatString(0, 0, 0xffffff, "%d", Mpos);
	ScreenFlip();
	return true;
}

int EditScene::Init(void)
{
	if (!objList)//objList�̒��ɉ��������ĂȂ��Ɨ�O������̂ŉ��������ĂȂ��ꍇ��objList�̒��ɓ���鏈�����s��
	{
		objList = std::make_shared<sharedObjList>();
	}
	objList->clear();
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapControl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	auto obj = AddObjList()(objList, std::make_unique<EditCursor>(lpSceneMng.GetDrawOffset()));
	(*obj)->init("image/map.png", VECTOR2(32, 32), VECTOR2(4, 2));
	return 0;
}
