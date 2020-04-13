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


	void Update()override;

	//bool UpdateHitItem();



private:
	
	D3DXVECTOR3 m_direction;
	float m_speed;
	float m_provisional_speed;
	
	D3DXVECTOR3 vec;

	float m_radius;

	bool m_hit;

	//CAMERA* p_camera;
	Collision* collision;
};

#endif

