#ifndef ITEM_H_
#define ITEM_H_

#include "../Object/ObjectBase.h"
#include "../Utility/Vec.h"

enum class ItemID
{
	Bomb,
	SpeedDown,
};

class Item :public ObjectBase
{
public:
	Item();
	~Item() {};

private:
	void UpdateHit();

	void UpdateSpeed();

	Vec3 m_speed;
	Vec3 m_pos;

	float m_radius;

	bool m_hit;
};

#endif

