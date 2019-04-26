#pragma once

/*enumは名前空間を持ってない
便宜上int型となっているが実際には型が存在していない
enumをｸﾗｽにすることで名前空間を持てるためMAXなど同じ名前を使用することができる
又、
しかし、ｸﾗｽにした場合不定だった型を指定してあげる必要が出てくる*/
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
	ITEM_BOMB,		//【ｱｲﾃﾑ】所持数UP
	ITEM_FIRE,		//【ｱｲﾃﾑ】火力UP
	ITEM_SPEED,		//【ｱｲﾃﾑ】移動速度UP
	ITEM_WALL_PASS,
	ITEM_FIRE_GUARD,
	ITEM_BOMB_THROW,
	ITEM_RAND,
	ITEM_CTL,		//【ｱｲﾃﾑ】遠隔爆弾化
	MAX				//		  IDの最大数
};
#define ITEM_ID_START MAP_ID::BOMB
#define ITEM_MAX static_cast<int>(static_cast<int>(MAP_ID::MAX) - static_cast<int>(MAP_ID::ITEM_BOMB))
MAP_ID operator+(MAP_ID m, int j);
