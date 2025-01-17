#pragma once
#include <map>
#include <vector>
//ﾃﾞﾊﾞｯｸ用の定理
#ifdef _DEBUG
#define AST(){\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d行目￥0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "ｱｻｰﾄ表示", MB_OK);\
	}
#else
#define AST()
#endif    // _DEBUG

using VEC_INT = std::vector<int>;
#define lpSoundMng SoundMng::GetInstance()
#define Sound_ID(X) (SoundMng::GetInstance().GetID(X))

class SoundMng
{
public:
	static SoundMng &GetInstance(void)
	{
		static SoundMng s_Instance;
		return (s_Instance);
	}
	const VEC_INT& GetID(std::string f_name);		// SEﾊﾝﾄﾞﾙの入手
	const int& PlaySound(std::string f_name, int soundType);
	const int& StopSound(std::string f_name);
	const int& ChangeVol(int vol,std::string f_name);
	const int& CheckSound(std::string f_name);
private:
	SoundMng();
	~SoundMng();
	SoundMng(SoundMng&);
	void operator = (SoundMng &) {};
	std::map<std::string, VEC_INT> sndMap;

};

