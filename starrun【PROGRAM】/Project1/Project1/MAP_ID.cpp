#include <type_traits> // static_cast を使用する際ｴﾗｰが出ることがあり<type_traits>をｲﾝｸﾙｰﾄﾞする必要が出てくることがある
#include "MAP_ID.h"

MAP_ID operator+(MAP_ID m, int j)
{
	return static_cast<MAP_ID>(static_cast<int>(m)+j);
}
