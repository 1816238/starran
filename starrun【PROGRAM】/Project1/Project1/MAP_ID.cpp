#include <type_traits> // static_cast ���g�p����۴װ���o�邱�Ƃ�����<type_traits>��ݸٰ�ނ���K�v���o�Ă��邱�Ƃ�����
#include "MAP_ID.h"

MAP_ID operator+(MAP_ID m, int j)
{
	return static_cast<MAP_ID>(static_cast<int>(m)+j);
}
