#ifndef OBJBASE_H_
#define OBJBASE_H_

#include"../Utility/Vec.h"
#include "../Object/ObjectBase.h"
#include"../Manager/FbxManager.h"
#include"../Engine/FBX.h"
#include"../DataBank/Definition.h"

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

		std::string m_key;
	}m_ObjectData;

public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Update();
	virtual void Draw();
	virtual const ObjectData* GetObjectData()const { return &m_ObjectData; }

private:
	

};

#endif
