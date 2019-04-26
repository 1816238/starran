#include "DxLib.h"	
#include "SceneMng.h"
#include "Obj.h"
#include "ImageMng.h"
#include "MapControl.h"


#define BBM_VER_ID 0x01		//failﾊﾞｰｼﾞｮﾝID
#define BBM_FILE_ID "BBM_MAP_DATA"		//failID
//炎ｱﾆﾒｰｼｮﾝ
#define FIRE_ANIM_FLAME			( 7 )											// 1ｺﾏあたりのﾌﾚｰﾑ数
#define FIRE_ANIM_CNT			( 7 )											// 総コマ数
#define FIRE_ANIM_TOP			( FIRE_ANIM_CNT / 2 )							// ｱﾆﾒｰｼｮﾝの折り返しｺﾏ位置
#define FIRE_ANIM_TOTAL_FLAME	( FIRE_ANIM_FLAME * FIRE_ANIM_CNT )			// ｱﾆﾒｰｼｮﾝの折り返しｺﾏ位置
#define FIRE_ANIM_PTN_X			( 3 )											// 炎の種類

struct DataHeader
{
	char fileID[13];		//ﾌｧｲﾙのID情報
	char verID;			//ﾊﾞｰｼﾞｮﾝID
	char reserve1[2];	//予約領域
	int sizeX;
	int sizeY;
	char reserve2[3];	//予約領域
	char sum;
};

void MapControl::UpDate()
{
	
}

void MapControl::Draw(bool EditFlag)
{

	auto img = lpImageMng.GetID("image/map.png");
	
	if (!EditFlag)
	{
		DrawGraph(0, 0, bgImage, false);
	}
	
	for (int y = 0; y < mapSize.y;y++) 
	{
		for (int x = 0;x < mapSize.x;x++)
		{
			MAP_ID id = mapData[y][x];
			switch (id)
			{
	//常に描画しない
			case MAP_ID::NON:
				break;
			case MAP_ID::BOMB:
				if (!EditFlag)
				{
					break;
				}
				//editMode時は描画するのでそのまま処理を下に流す
				//break


	//背景

			case MAP_ID::WALL1:
			case MAP_ID::WALL2:
			case MAP_ID::BLOCK:
			case MAP_ID::ITEM_FIRE:
			case MAP_ID::ITEM_BOMB:
			case MAP_ID::ITEM_CTL:
			case MAP_ID::ITEM_SPEED:
				DrawGraph(drawOffSet.x + x * chipSize.x, drawOffSet.y + y * chipSize.y
					, lpImageMng.GetID("image/map.png")[ static_cast<int>(id) ], true);
				break;
			case MAP_ID::CUR:
			case MAP_ID::FLOOR1:
			case MAP_ID::FLOOR2:
				break;
	//ｴﾗｰ
			default:
#ifdef _DEBUG
				DrawGraph(drawOffSet.x + x * chipSize.x, drawOffSet.y + y * chipSize.y
					, lpImageMng.GetID("image/map.png")[ static_cast<int>(MAP_ID::CUR) ], true);
#endif
				break;
			}
		}
	}
}

bool MapControl::SetUp(const VECTOR2 & size, const VECTOR2 &ChipSize, const VECTOR2 DrawOffSet)
{
	lpImageMng.GetID("image/map.png", VECTOR2(20, 20), VECTOR2(4, 3));

	mapSize = VECTOR2(size.x / ChipSize.x, size.y / ChipSize.y);
	MapControl::chipSize = ChipSize;
	MapControl::drawOffSet = DrawOffSet;

	auto createMap = [=](auto &base, auto &front , auto initNum)
	{
		base.resize(mapSize.x * mapSize.y);
		front.resize(mapSize.y);
		for (int count = 0; count < front.size(); count++)
		{
			front[count] = &base[mapSize.x * count];
		}
		for (int j = 0; j < base.size(); j++)
		{
			base[j] = initNum;
		}
	};
	createMap(mapDataBace, mapData, MAP_ID::NON);

	lpImageMng.GetID("image/fire.png", { 20,20 }, { 3,4 });

	if (bgImage <= 0)
	{
		auto s_size = lpSceneMng.GetScreenSize();
		bgImage = MakeScreen(s_size.x, s_size.y);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		SetDrawScreen(bgImage);

		//auto img = lpImageMng.GetID("image/map.png");

		int Cnt = 0;
		for (int y = 0; y < mapSize.y; y++)
		{
			Cnt = (y % 2);
			for (int x = 0; x < mapSize.x; x++)
			{
				Cnt++;
				DrawGraph(drawOffSet.x + x * chipSize.x, drawOffSet.y + y * chipSize.y
					, IMAGE_ID("image/map.png")[static_cast<int>(MAP_ID::FLOOR1) + (Cnt % 2)], true);
			}
		}

		SetDrawScreen(DX_SCREEN_BACK);
	}

	return false;
}
struct CheckSize
{
	bool operator()(const VECTOR2 &selPos, const VECTOR2 &mapSize) {

		if ((selPos.x < 0) || (selPos.x >= mapSize.x)
			|| (selPos.y < 0) || (selPos.y >= mapSize.y))
		{
			return false;
		}
		return true;
	}
};
bool MapControl::SetMapData(const VECTOR2 & pos, MAP_ID id)
{
	return 	SetData( mapData, pos, id );
}

template<typename mapType, typename idType>
bool MapControl::SetData(mapType maps, const VECTOR2 & pos, idType id)
{
	VECTOR2 selPos(pos / chipSize);
	if (!CheckSize()(selPos, mapSize))		//何度も実態を作ることになるので再利用する際は注意
	{
		return false;
	}
	maps[selPos.y][selPos.x] = id;
	_RPTN(_CRT_WARN, "write[%d,%d]%d\n", pos.x, pos.y, id);
	return true;
}

template<typename mapType, typename idType>
idType MapControl::GetDate(mapType maps, const VECTOR2 & pos, idType defID)
{
	VECTOR2 selpos(pos / chipSize);
	if (!CheckSize()(selpos, mapSize))
	{
		//範囲外の場合、下記のIDを固定で返す
		return defID;//無効な値として返す(システム上一番問題が起きないだろう物を使用する)
	}
	_RPTN(_CRT_WARN, "maps : %d\n", maps[selpos.y][selpos.x]);
	return maps[selpos.y][selpos.x];
}

bool MapControl::MapSave(sharedListObj objList)
{
	DataHeader expData = {
		BBM_FILE_ID,
		BBM_VER_ID,
		{0,0},
		mapSize.x,
		mapSize.y,
		{ 0,0,0 },
		(char)0xff
	};
	//SUMﾁｪｯｸ-------------------------------------------------------------------
	int sum = 0;

	for (auto data : mapDataBace)
	{
		sum += static_cast<int>(data);
	}
	expData.sum = static_cast<char>(sum);

	FILE *file;
	fopen_s(&file, "date/mapdate.map", "wb");
	fwrite(&expData, sizeof(expData), 1, file);
	fwrite(&mapDataBace[0],sizeof(MAP_ID)*mapDataBace.size(),1,file);
	fclose(file);
	return true;
}

bool MapControl::MapLoad(sharedListObj objList	, bool objFlag)
{
	FILE *file;
	DataHeader expData;
	fopen_s(&file, "date/mapdate.map", "rb");
	fread(&expData, sizeof(expData), 1, file);
	//ﾍｯﾀﾞｰのｻｲｽﾞ情報を元にmapDataBaceのｻｲｽﾞする
	mapDataBace.resize(expData.sizeX * expData.sizeY);
	fread(&mapDataBace[0], sizeof(MAP_ID),mapDataBace.size(), file);
	fclose(file);
	bool flag = true;
	int sum = 0;
	for (auto data : mapDataBace)
	{
		sum += static_cast<int>(data);
	}

	//ﾍｯﾀﾞｰのﾌｧｲﾙID情報と内部で持っているIDと比べる
	//ﾍｯﾀﾞｰのﾊﾞｰｼﾞｮﾝ番号と内部持っている番号を比べる	
	//sum値を計算しﾍｯﾀﾞｰのSUM値と比べて違ったら、
	//if(strcmp(expData.fileID, BBM_FILE_ID))
	if ((std::string)expData.fileID!= BBM_FILE_ID
		|| expData.verID != BBM_VER_ID ||expData.sum != static_cast<char>(sum))
	{
		flag = false;
	}
	//ﾃﾞｰﾀをｸﾘｱする
	if (!flag)
	{
		for (auto &data : mapDataBace)
		{
			data = MAP_ID::NON;
			if (MessageBox(NULL, "ERROR!!",
				"確認ダイアログ", MB_OK) == IDOK)
			{
				DxLib_End();	// DXﾗｲﾌﾞﾗﾘの終了処理
			}
		}
	}
	return flag;
}

const VECTOR2 & MapControl::GetChipSize(void)
{
	return chipSize;
}

MapControl::MapControl()
{
	bgImage = 0;
}


MapControl::~MapControl()
{
}


