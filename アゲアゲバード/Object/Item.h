#ifndef ITEM_H_
#define ITEM_H_

#include "../Object/ObjectBase.h"
#include "../Utility/Vec.h"
#include "../Engine/Camera.h"
#include "../Utility/Collision.h"

//�O���錾
class Block;

enum class ItemID
{
	Bomb,
	SpeedDown,
	Blindness,
	MaxItem
};

class Item :public ObjectBase
{
private:

	std::vector<Block*>* m_block;

	struct ItemData :public ObjectData {

		D3DXVECTOR3 m_direction;
		D3DXVECTOR3 vec;

		//CAMERA* p_camera;
		Collision* collision;

		float m_speed;
		float m_provisional_speed;
		float m_radius;
		float m_gravity;

		bool m_hit;

	}m_itemdata;
public:
	Item();
	~Item() {};


	void Update()override;

	const ItemData* GetItemData()const { return &m_itemdata; };

private:
	bool UpdateHitItem();

};

class GetItemBox :public ObjectBase
{
private:
	void BoxProduction();

	struct ItemBoxData :public ObjectData {

		Collision* m_collision;

		int m_floattime;

		float m_rotspeed;

		bool m_Upward;

	}m_boxdata;

public:
	GetItemBox();
	~GetItemBox();

	void Update()override;

	const ItemBoxData* GetBoxData()const { return &m_boxdata; };


};


#endif

