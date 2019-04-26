#pragma once
#include <mutex>
#include <list>
#include <memory>
#include "VECTOR2.h"
#include "BaseScene.h"

using namespace std;

class Obj;
class GameController;

#define lpSceneMng SceneMng::GetInstance()

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int   Thickness = 1);	
// ����`�悷��

class SceneMng
{
public:
	static SceneMng &GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run(void);
	VECTOR2 GetScreenSize(void);		//��ذݻ��ނ̎擾
	bool SetDrawOffset(VECTOR2 vec);
	const VECTOR2 &GetDrawOffset(void);
	bool DelObjList(list<Obj*>::iterator itr);
private:
	SceneMng();
	~SceneMng();
	//SceneMng::*SmngPtr�@=>�ϐ����@����ȊO�͌^

	VECTOR2 drawOffset;
	/*std::unique_ptr<Obj>�^�Ƃ��Ďg����*/
	unique_ptr<GameController> gameCtl;
	unique_Base activeScene;
	bool SysInit(void);			//�ްъJ�n����1�x����������
	/*Edit�֌W*/
};

