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
	D3DXVECTOR3 m_map_centerpos;//�}�b�v�̒��S�_(�������ʒu�Ȃ�(0,0,0)�A�I�u�W�F�N�g�̒��S�Ȃ�(0,1500,0)�����炭)
	D3DXVECTOR3 m_map_top;		// �}�b�v�̒���̒��S���W
	D3DXVECTOR3 m_map_bottom;	// �}�b�v�̒�ӂ̒��S���W
	float m_map_radius;			//�}�b�v�̔��a(���r���[�A�[�ō̐��������̂�29�A�������ɑ傫����30�{�ɂ��Ă��邽��870)
};

#endif