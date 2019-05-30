#include<math.h>
#include "Dxlib.h"
#include "time.h"
#include "classObj.h"
#include "SceneMng.h"
#include "MapControl.h"
#include "Obj.h"
#include "GameCtl.h"
#include "ImageMng.h"
#include "Enemy.h"
#include "Player.h"
#include "ResultCtl.h"
#include "ResultScene.h"
#include "SpeedMng.h"
#include "SoundMng.h"
#include "Effect.h"
#include "GameScene.h"

GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

unique_Base GameScene::UpDate(unique_Base own, const GameCtl & controller)
{
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpDate(controller, objList);
	}
	//���q�y����ި��āz
	//(*objList).remove_if([](uniqueObj& obj) {return obj->CheckDeth(); });
	for (auto itr = objList->begin(); itr != objList->end(); )
	{
		if ((*itr)->CheckObjType() == TYPE_PLAYER)
		{
			if ((*itr)->CheckDeath())
			{
				objList->erase(itr);
				lpResultCtl.SetUp(1000, 10);
				lpResultCtl.ResultSave(objList);
				return std::make_unique<ResultScene>();

			}
			(*itr)->Setdeath(playerPos.deathFlag);
			(*itr)->SetDamage(playerPos.damageFlag);
			playerPos.damageFlag = false;
			playerPos.deathFlag = false;

			playerPos.pos = VECTOR2{ 64,(*itr)->GetPos().y };	
			itr++;
		}
		else if ((*itr)->CheckObjType() == TYPE_ENEMY_BIT)
		{
			bool tmpFlag = false;
			for (Bit_itr = BitObj.begin(); Bit_itr != BitObj.end();	Bit_itr++)
			{
				if ((*itr)->GetBitNo() == Bit_itr->ObjNo)
				{
					if (Bit_itr->damageFlag)
					{
						(*itr)->SetDamage(true, SHOT_DAMAGE);
						Bit_itr->damageFlag = false;
					}
					Bit_itr->pos = (*itr)->GetPos();

					if (Bit_itr->deathFlag || (*itr)->CheckDeath())
					{
						objList->erase(itr);
						Bit_itr->deathFlag = true;
						tmpFlag = true;
						break;
					}

				}
			
			}
			if (!tmpFlag)
			{
				itr++;

			}
			else {
				break;
			}
		}
		else if ((*itr)->CheckObjType() == TYPE_PLAYER_SHOT || (*itr)->CheckObjType() == TYPE_ENEMY_SHOT|| (*itr)->CheckObjType() == TYPE_METEO)
		{
			if ((*itr)->CheckObjType() == TYPE_PLAYER_SHOT)
			{
				
				for (Bit_itr = BitObj.begin(); Bit_itr != BitObj.end(); Bit_itr++)
				{
					if (!Bit_itr->deathFlag)
					{
						if (circleHit(Bit_itr->pos + 22, 22, (*itr)->GetPos() + VECTOR2{ 32,16 }, 10))
						{
							Bit_itr->damageFlag = true;
							(*itr)->Setdeath(true);
						}
					}
				}

			}
			else 
			{
				if (circleHit((*itr)->GetPos() + 15, 10, playerPos.pos + VECTOR2{14,0}, VECTOR2{ PLAYER_SIZE_X-14,PLAYER_SIZE_Y }))
				{
					if (playerPos.damageFlag)
					{
						playerPos.deathFlag = true;
					}
					else {
						playerPos.damageFlag = true;
						lpEffect.SetEffectFlag(true);
					}

					(*itr)->Setdeath(true);
				}
			}
			

			if ((*itr)->CheckDeath())
			{
				objList->erase(itr);
				break;
			}
			else { itr++; }
		}
		else {
			itr++;
		}
	}
	SeasonSwitch();
	lpSpeedMng.move();
	GameDraw();

	return std::move(own);		//���L�����ڂ�
}

bool GameScene::circleHit(VECTOR2 CePos, int CeRad, VECTOR2 SquPos, VECTOR2 SquRange)
{
	if (CePos > SquPos&&CePos < SquPos + SquRange)
	{
		return true;
	}
	if (abs(CePos.x - SquPos.x) < CeRad && abs(CePos.y - SquPos.y) < CeRad)					//����
	{
		return true;
	}
	if (abs(CePos.x - SquPos.x) < CeRad && abs(CePos.y - (SquPos.y+SquRange.y)) < CeRad)	//����
	{
		return true;
	}
	if (abs(CePos.x - (SquPos.x+SquRange.x)) < CeRad && abs(CePos.y - SquPos.y) < CeRad)	//�E��
	{
		return true;
	}	
	if (abs(CePos.x - SquPos.x) < CeRad && abs(CePos.y - (SquPos.y+SquRange.y)) < CeRad)	//�E��
	{
		return true;
	}
	return false;
}

bool GameScene::circleHit(VECTOR2 CePos, int CeRad, VECTOR2 CePos2, int CeRad2)
{
	if (sqrt(pow(abs(CePos.x - CePos2.x), 2) + pow(abs(CePos.y - CePos2.y), 2)) <= static_cast<double>(CeRad + CeRad2))
	{
		return true;
	}
	return false;
}



bool GameScene::GameDraw(void)
{
	(*objList).sort([](uniqueObj& obj1, uniqueObj& obj2) {return ((*obj1).GetPos().y < (*obj2).GetPos().y); });
	
	if (lpEffect.GetEffectFlag())		//��Ұ�ނ��󂯂��ۂ�effect
	{
		OutputDebugString("effect\n");
			lpEffect.Shake();
			//lpEffect.Draw();
	}
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/back.jpg")[0], true);
	lpMapControl.Draw(false);
	for (auto &data : (*objList))
	{
		(*data).Draw();
	}
	
		//��Ұ�ނ��󂯂��ۂ�effect
		lpEffect.Draw();

	/*
	for (int i = 0; i < 21; i++)
	{
		DrawLine(0, i*CHIP_SIZE, 1280, i*CHIP_SIZE, 0xffff00);

	}*/
	//[]() {};		�������_���̈��[]{};�������ȗ������`
	//std::for_each((*objList).begin(), (*objList).end(), [](std::unique_ptr<Obj>&itr) {itr->Draw(); }/*�����_��*/);
	ScreenFlip();
	return false;
}

int GameScene::Init(void)
{
	if (!objList)//objList�̒��ɉ��������ĂȂ��Ɨ�O������̂ŉ��������ĂȂ��ꍇ��objList�̒��ɓ���鏈�����s��
	{
		objList = std::make_shared<uniqueObjList>();
	}
	objList->clear();
	SetWindowText("AGS.exe Game");

	srand(time(NULL));
	lpSoundMng.StopSound("Sound/BGM/milkyway.mp3");
	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapControl.SetUp(VECTOR2(SCREEN_SIZE_X*4, SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), lpSceneMng.GetDrawOffset());
	player = AddObjList()(objList, std::make_unique<Player>(VECTOR2(CHIP_SIZE * 2, CHIP_SIZE * 15),TYPE_PLAYER, lpSceneMng.GetDrawOffset()));
	auto obj = AddObjList()(objList, std::make_unique<Enemy>(TYPE_ENEMY));
	(*obj)->init("image/map.png", VECTOR2(32, 32), VECTOR2(4, 2));
	lpMapControl.MapLoad("data/mapdata2.map",objList, false,true);
	lpMapControl.MapLoad("data/submap.map", objList, false, false);
	lpSpeedMng.Init();
	SeasonSwitchFlag = 0;
	playerPos.damageFlag = false;
	playerPos.deathFlag = false;

	Bit_itr = BitObj.begin();
	BitObj.resize(4);
	int i = 0;
	for (auto itr = BitObj.begin(); itr != BitObj.end(); itr++)
	{
		
		itr->ObjNo = i;
		i++;
	}
	return 0;
}
void GameScene::SeasonSwitch(void)
{
	if (lpSpeedMng.GetSeasoonFlag(Main) == SeasonSwitchFlag)
	{
		switch (SeasonSwitchFlag)
		{
		case 0:
			lpMapControl.MapLoad("data/mapdata1.map", objList, false, true);
			SeasonSwitchFlag++;
				break;
		case 1:
			lpMapControl.MapLoad("data/mapdata2.map", objList, false, true);
			SeasonSwitchFlag++;
			break;
		case 2:
			break;
		case 3:

			break;
		case 4:
			break;
		default:
			break;
		}
	}
}
