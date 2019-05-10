#pragma once
#include <array>

enum KEY_TYPE			//今と1つ前のｷｰ情報
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

using KEY_ARRAY = std::array<char, 256>;			//全てのｷｰ情報を入れておく変数（固定長）

class GameCtl
{
public:
	GameCtl();
	~GameCtl();
	bool UpDate(void);
	const KEY_ARRAY &GetCtl(KEY_TYPE type) const;		//『std::array<char, 256>』=>型   std::array<char, 256> GetCtl(void);
	const bool GetClick(int mouse_type, KEY_TYPE type) const;
	const bool WheelCheck(KEY_TYPE type)const;
private:
	KEY_ARRAY data;
	KEY_ARRAY dataOld;
	int Click;
	int ClickOld;
	type wheel;
	
};