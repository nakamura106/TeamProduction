#ifndef POT_H_
#define POT_H_

#include "../Object/ObjectBase.h"
class Pot :public ObjectBase
{
private:
	struct mapdata:public ObjectData
	{
		D3DXVECTOR3 m_map_centerpos;//マップの中心点(※生成位置なら(0,0,0)、オブジェクトの中心なら(0,1500,0)おそらく)
		D3DXVECTOR3 m_map_top;		// マップの頂上の中心座標
		D3DXVECTOR3 m_map_bottom;	// マップの底辺の中心座標
		
	}m_mapdata;
public:
	Pot();
	~Pot() {};

	void Update()override;
	void Draw()override;

	const mapdata* GetMapData()const { return &m_mapdata; }


};

#endif