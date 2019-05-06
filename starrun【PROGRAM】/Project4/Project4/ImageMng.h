#pragma once
#include <map>
#include <vector>
#include <mutex>
#include "VECTOR2.h"

#ifdef _DEBUG
#define AST(){\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d�s�ځ�0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "���ĕ\��", MB_OK);\
	}
#else
#define AST()
#endif    // _DEBUG
class VECTOR2;

using namespace std;
using VEC_INT = vector<int>;
#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

class ImageMng
{
public:
	static ImageMng &GetInstance(void)
	{
		static ImageMng s_Instance;
		return s_Instance;
	}

	const VEC_INT& GetID(string f_name);			//��؂̎擾
	const VEC_INT& GetID(string f_name, VECTOR2 divSize, VECTOR2 divCnt);			//�摜�̕����ǂݍ���

private:
	ImageMng();
	~ImageMng();
	//std::map<���̌^,�A�z�^�z��̌^> �A�z�z��;
	//std::map<std::string, std::vector<int>> imgMap;
	map<string, VEC_INT> imgMap;
};

