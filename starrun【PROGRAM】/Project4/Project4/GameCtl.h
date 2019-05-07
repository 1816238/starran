#pragma once
#include <array>
#include "VECTOR2.h"
#include <DxLib.h>

enum KEY_TYPE			//今と1つ前のｷｰ情報
{
	NOW,
	OLD,
	MAX,
};

class EditCursor;

using KEY_ARRAY = std::array<char, 256>;			//全てのｷｰ情報を入れておく変数（固定長）

class GameCtl
{
public:
	GameCtl();
	~GameCtl();
	bool UpDate(void);
	const KEY_ARRAY &GetCtl(KEY_TYPE type) const;		//『std::array<char, 256>』=>型   std::array<char, 256> GetCtl(void);
	const VECTOR2 &GetChipPos(VECTOR2 pos) const;
private:
	KEY_ARRAY data;
	KEY_ARRAY dataOld;
};