#pragma once
#include <map>
#include <string>
#include "VECTOR2.h"
#include "classObj.h"

enum DIR
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_MAX
};

enum ANIM_TBL {
	ANIM_TBL_START_ID,	//
	ANIM_TBL_FRAME,		//�摜��
	ANIM_TBL_INV,		//�Ԋu
	ANIM_TBL_LOOP,		//���[�v���邩�ǂ���
	ANIM_TBL_MAX
};



class GameCtl;
using namespace std;


class Obj
{
public:
	Obj(VECTOR2 drawOffset);
	Obj();
	bool init(string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos);//�摜��̧�ٖ���������������������W
	bool init(string fileName, VECTOR2 divSize, VECTOR2 divCnt);			//�摜��̧�ٖ�����������������
	virtual bool initAnim(void) { return true; };
	virtual ~Obj();
	void UpDate(const GameCtl &controller, weekListObj objList);
	virtual bool CheckDeth(void) { return false; };
	void Draw(unsigned int id);				//�Œ�ID�ł̐���
	virtual void Draw(void);						//map�摜�̕`��֌W
	const VECTOR2 & GetPos(void);			//pos�̎擾
	bool AddAnim(string animName, int ID_x, int ID_y, int frame, int inv, bool loop);		//�摜�̊Ԋu�▇���Ȃǂ�animTbl�ɑ��
	bool SetAnim(string animName);			//�\���摜̧�ٖ��y�ѱ�Ұ��ݶ�����̏�����
	string GetAnim(void);			//�\���摜̧�ٖ��̎擾
private:
	virtual void SetMove(const GameCtl &controller, weekListObj objList) = 0;		//�摜�ړ��̷�����		�������z�֐�

	map<string, int[ANIM_TBL_MAX]> animTbl;
	string animName;				//�\���摜̧�ٖ�
protected:
	bool animEndFlag;				//��Ұ��ݍŏI�ϓ��B�׸�
	unsigned int animCnt;			//��Ұ��ݶ����
	const VECTOR2 drawOffset;		//�`��̾��
	VECTOR2 pos;					//���W
	VECTOR2 pos2;					//���W
	void SetPos(VECTOR2 pos);
	string imageName;				//�\����Ұ��ݖ�
	VECTOR2 divSize;				//��������
	VECTOR2 divCnt;					//������
	DIR dir;						//�i�s����
};

