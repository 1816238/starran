#pragma once

/*enum�͖��O��Ԃ������ĂȂ�
�֋X��int�^�ƂȂ��Ă��邪���ۂɂ͌^�����݂��Ă��Ȃ�
enum��׽�ɂ��邱�ƂŖ��O��Ԃ����Ă邽��MAX�ȂǓ������O���g�p���邱�Ƃ��ł���
���A
�������A�׽�ɂ����ꍇ�s�肾�����^���w�肵�Ă�����K�v���o�Ă���*/
enum class MAP_ID
{
	CUR,
	FLOOR1,
	FLOOR2,
	BOMB,
	NON,
	WALL1,
	WALL2,
	BLOCK,
	ITEM_BOMB,		//�y���сz������UP
	ITEM_FIRE,		//�y���сz�Η�UP
	ITEM_SPEED,		//�y���сz�ړ����xUP
	ITEM_WALL_PASS,
	ITEM_FIRE_GUARD,
	ITEM_BOMB_THROW,
	ITEM_RAND,
	ITEM_CTL,		//�y���сz���u���e��
	MAX				//		  ID�̍ő吔
};
#define ITEM_ID_START MAP_ID::BOMB
#define ITEM_MAX static_cast<int>(static_cast<int>(MAP_ID::MAX) - static_cast<int>(MAP_ID::ITEM_BOMB))
MAP_ID operator+(MAP_ID m, int j);
