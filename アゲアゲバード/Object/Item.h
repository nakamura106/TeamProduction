#ifndef ITEM_H_
#define ITEM_H_

#include "../Object/ObjectBase.h"
#include "../Utility/Vec.h"
#include "../Engine/Camera.h"
#include "../Utility/Collision.h"

enum class ItemID
{
	Bomb,
	SpeedDown,
	Blindness,
	MaxItem
};

class Item :public ObjectBase
{
public:
	Item();
	~Item() {};


	void Update();

	//bool UpdateHitItem();



private:
	
	Vec3 m_direction;
	float m_speed;
	float m_provisional_speed;
	

	float m_radius;

	bool m_hit;

	CAMERA* p_camera;
	Collision* collision;
};

#endif

