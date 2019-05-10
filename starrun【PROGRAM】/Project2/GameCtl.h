#pragma once
#include <array>

enum KEY_TYPE			//����1�O�̷����
{
	NOW,
	OLD,
	MAX,
};
typedef struct {
	bool now;
	bool old;
}type;

class EditCursor;

using KEY_ARRAY = std::array<char, 256>;			//�S�Ă̷��������Ă����ϐ��i�Œ蒷�j

class GameCtl
{
public:
	GameCtl();
	~GameCtl();
	bool UpDate(void);
	const KEY_ARRAY &GetCtl(KEY_TYPE type) const;		//�wstd::array<char, 256>�x=>�^   std::array<char, 256> GetCtl(void);
	const bool GetClick(int mouse_type, KEY_TYPE type) const;
	const bool WheelCheck(KEY_TYPE type)const;
private:
	KEY_ARRAY data;
	KEY_ARRAY dataOld;
	int Click;
	int ClickOld;
	type wheel;
	
};