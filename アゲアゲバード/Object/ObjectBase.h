#ifndef OBJBASE_H_
#define OBJBASE_H_

#include"../Utility/Vec.h"
#include "../Object/ObjectBase.h"
#include"../Manager/FbxManager.h"
#include"../Engine/FBX.h"
class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Update();
	virtual void Draw();

	virtual D3DXVECTOR3 GetPos()const{ return m_pos; };

protected:
	D3DXVECTOR3 m_pos;
	FBXMeshData m_object;
	D3DXMATRIX m_mat_world;		// ���[���h
	D3DXMATRIX m_mat_scall;		// �g�k		�뎚 scall��scale�H
	D3DXMATRIX m_mat_move;		// trans�Ɠ����ړ��H
	D3DXMATRIX m_mat_rot;		// ��]
	D3DXMATRIX m_mat_rot_x;		// ��]x��
	D3DXMATRIX m_mat_rot_y;		// ��]y��
	D3DXMATRIX m_mat_rot_z;		// ��]z��
	std::string m_key;
	
	D3DXMATRIX m_mat_trans;	// �ړ�

private:


};

#endif
