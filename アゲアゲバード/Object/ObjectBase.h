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
	~ObjectBase();

	virtual void Update();
	virtual void Draw();

	//Vec3 GetPos(return m_pos);

protected:
	Vec3 m_pos;
	FbxManagera m_manager;
	FBXMeshData m_object;
	D3DXMATRIX m_mat_world;
	D3DXMATRIX m_mat_scall;
	D3DXMATRIX m_mat_move;
	D3DXMATRIX m_mat_rot;

};

#endif
