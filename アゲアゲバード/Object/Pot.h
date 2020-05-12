#ifndef POT_H_
#define POT_H_

#include "../Object/ObjectBase.h"
class Pot :public ObjectBase
{
private:
	struct mapdata:public ObjectData
	{
		D3DXVECTOR3 m_map_centerpos;//�}�b�v�̒��S�_(�������ʒu�Ȃ�(0,0,0)�A�I�u�W�F�N�g�̒��S�Ȃ�(0,1500,0)�����炭)
		D3DXVECTOR3 m_map_top;		// �}�b�v�̒���̒��S���W
		D3DXVECTOR3 m_map_bottom;	// �}�b�v�̒�ӂ̒��S���W
		
	}m_mapdata;
public:
	Pot();
	~Pot() {};

	void Update()override;
	void Draw()override;

	const mapdata* GetMapData()const { return &m_mapdata; }


};

#endif