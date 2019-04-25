#pragma once
#include <array>

enum KEY_TYPE			//����1�O�̷����
{
	KEY_TYPE_NOW,
	KEY_TYPE_OLD,
	KEY_TYPE_MAX,
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
private:
	KEY_ARRAY data;
	KEY_ARRAY dataOld;
};