#ifndef ITEM_H_
#define ITEM_H_

#include "../Object/ObjectBase.h"
#include "../Utility/Vec.h"
#include "../Engine/Camera.h"

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
	

	void UpdateSpeed();

	Vec3 m_direction;
	float m_speed;
	float m_provisional_speed;
	Vec3 m_pos;

	float m_radius;

	bool m_hit;

	CAMERA* p_camera;
};

#endif

