#pragma once
#include <array>
#include "VECTOR2.h"
#include <DxLib.h>

enum KEY_TYPE			//����1�O�̷����
{
	NOW,
	OLD,
	MAX,
};

class EditCursor;

using KEY_ARRAY = std::array<char, 256>;			//�S�Ă̷��������Ă����ϐ��i�Œ蒷�j

class GameCtl
{
public:
	GameCtl();
	~GameCtl();
	bool UpDate(void);
	const KEY_ARRAY &GetCtl(KEY_TYPE type) const;		//�wstd::array<char, 256>�x=>�^   std::array<char, 256> GetCtl(void);
	const VECTOR2 &GetChipPos(VECTOR2 pos) const;
private:
	KEY_ARRAY data;
	KEY_ARRAY dataOld;
};