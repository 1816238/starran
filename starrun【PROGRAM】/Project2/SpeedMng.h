#pragma once

#include <vector>
#include "VECTOR2.h"
class MapControl;
using namespace std;
#define lpSpeedMng SpeedMng::GetInstance()
#define Speed(x) SpeedMng::GetInstance().GetSpeed(x)	//Main��Ҳ݂����+���F�����̎擾��/10*30�ASub�Ż�ނ����+���F�����̎擾��/10*30���擾�ł���
#define SPEED 4

enum MapType {
	Main,
	Sub,
	Sub2,
	Std,
	Max
};
enum class SEASON {
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER,
	MAX
};

class SpeedMng
{
public:
	static SpeedMng &GetInstance(void)
	{
		static SpeedMng s_Instance;
		return s_Instance;
	}
	void move(void);
	int GetTime(void);
	void AddStar(void);
	int GetYellow(void);
	int GetSpeed(MapType type,SEASON season=SEASON::MAX);	//�ǂꂭ�炢���������̎擾season�͓���Ȃ�������MAX������
	bool GetFlag(MapType type,SEASON season=SEASON::MAX);	//�e�^�C�v�̃t���O�̎擾season�ɓ����Ƃ���seasonFlag��Ԃ��Ă����
	bool Init(void);
	SpeedMng(SpeedMng& in) {};
	void operator=(SpeedMng& in) {};
	bool GetSeasonFlag(MapType type,SEASON season=SEASON::MAX);	//
	vector<int> switchFlag;
	SEASON GetSeason(void);
private:
	SpeedMng();
	~SpeedMng();
	void reset(void);

	int speedTime[Max];
	int seasonTime[static_cast<int>(SEASON::MAX)];
	int yellowstar;
	int SpeedCnt;
	int speed;
	bool speedFlag[Max];	
	int time;				//�o�ߎ���
	int standardTime;		//speedflag�̔���Ɏg�p�����{�ƂȂ鶳��
	vector<bool> Seasonflag;			//0�ŏt�A1�ŉāA2�ŏH�A3�œ~�A4��EX
	bool subseasonFlag;
	
};

