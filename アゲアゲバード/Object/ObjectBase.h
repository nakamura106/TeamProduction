#ifndef OBJBASE_H_
#define OBJBASE_H_

//#include "../Object/ObjectBase.h"
#include"../Engine/FBX.h"



class ObjectBase
{
protected:
	struct ObjectData {

		FBXMeshData m_object;

		D3DXVECTOR3 m_pos;
		D3DXMATRIX m_mat_world;		// ���[���h
		D3DXMATRIX m_mat_scale;		// �g�k		�뎚 scall��scale�H
		D3DXMATRIX m_mat_move;		// �ړ�
		D3DXMATRIX m_mat_rot;		// ��]
		D3DXMATRIX m_mat_rot_x;		// ��]x��
		D3DXMATRIX m_mat_rot_y;		// ��]y��
		D3DXMATRIX m_mat_rot_z;		// ��]z��

		float radius;					// ���a(�v���C���[�̓����蔻����Ƃ邽�߂�)

		D3DXVECTOR3 angle_;
		D3DXVECTOR3 scale_;

		std::string m_key;
	};

public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Update()=0;
	virtual void Draw()=0;
	
	
private:
	

};

#endif
