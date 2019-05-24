#pragma once
#include <map>
#include <vector>
//���ޯ��p�̒藝
#ifdef _DEBUG
#define AST(){\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d�s�ځ�0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "���ĕ\��", MB_OK);\
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
	const VEC_INT& GetID(std::string f_name);		// SE����ق̓���
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

