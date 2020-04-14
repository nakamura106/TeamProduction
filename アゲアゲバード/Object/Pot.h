#ifndef POT_H_
#define POT_H_

#include "../Object/ObjectBase.h"
#include"../Manager/FbxManager.h"
#include"../Engine/FBX.h"

class Pot :public ObjectBase
{
public:
	Pot();
	~Pot() {};
private:
	D3DXVECTOR3 m_map_centerpos;//マップの中心点(※生成位置なら(0,0,0)、オブジェクトの中心なら(0,1500,0)おそらく)
	float m_map_top;
	float m_map_radius;			//マップの半径(※ビューアーで採寸したものが29、生成時に大きさを30倍にしているため870)
};

#endif