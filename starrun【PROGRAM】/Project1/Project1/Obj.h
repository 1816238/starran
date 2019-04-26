#pragma once
#include <map>
#include <string>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"

enum class DIR
{
	DOWN,		//��
	LEFT,		//��
	RIGHT,		//�E
	UP,			//��
	MAX
};

enum class ANIM_TBL {
	START_ID,	//
	FRAME,		//�摜��
	INV,		//�Ԋu
	LOOP,		//���[�v���邩�ǂ���
	MAX
};

enum OBJ_TYPE{
	PLAYER,
	ENEMY,
	BOMB,
	EDIT_CUR,
	MAX
};



class GameController;
using namespace std;
using DIR_STRING_ARRAY = array<string, static_cast<size_t>(DIR::MAX)>;
using Type_long = unsigned long long;															// �����̂ŏȗ�����
 
class Obj
{
public:
	Obj(VECTOR2 drawOffset);
	Obj();
	bool init(string fileName, VECTOR2 divSize, VECTOR2 divCnt,VECTOR2 pos);				// �摜��̧�ٖ���������������������W
	bool init(string fileName, VECTOR2 divSize, VECTOR2 divCnt);							// �摜��̧�ٖ�����������������
	virtual bool initAnim(void) { return true; };
	virtual ~Obj();
	void UpDate(const GameController &controller, weekListObj objList);
	virtual bool CheckDeth(void) { return false; };
	virtual bool CheackObjType(OBJ_TYPE Obj_type) = 0;										// ���݂̃N���X�m�F
	void Draw(unsigned int id);																// �Œ�ID�ł̐���
	virtual void Draw(void);																// map�摜�̕`��֌W
	const VECTOR2 & GetPos(void);															// pos�̎擾
	bool AddAnim(string animName, int ID_x, int ID_y, int frame, int inv,bool loop);		// �摜�̊Ԋu�▇���Ȃǂ�animTbl�ɑ��
	bool SetAnim(string animName);															// �\���摜̧�ٖ��y�ѱ�Ұ��ݶ�����̏�����
	string GetAnim(void);																	// �\���摜̧�ٖ��̎擾
private:
	virtual void SetMove(const GameController &controller, weekListObj objList) = 0;		// �摜�ړ��̷�����		�������z�֐�

	map<string, int[static_cast<Type_long>(ANIM_TBL::MAX)]> animTbl;
	string animName;																		// �\���摜̧�ٖ�
protected:
	bool animEndFlag;																		// ��Ұ��ݍŏI�ϓ��B�׸�
	unsigned int animCnt;																	// ��Ұ��ݶ����
	const VECTOR2 drawOffset;																// �`��̾��
	VECTOR2 pos;																			// ���W
	void SetPos(VECTOR2 pos);
	string imageName;																		// �\����Ұ��ݖ�
	VECTOR2 divSize;																		// ��������
	VECTOR2 divCnt;																			// ������
	DIR dir;																				// �i�s����

	bool visible;																			// �\���E��\��
};

