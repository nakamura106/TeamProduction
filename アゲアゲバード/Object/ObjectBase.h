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
	D3DXMATRIX m_mat_world;
	D3DXMATRIX m_mat_scall;
	D3DXMATRIX m_mat_move;
	D3DXMATRIX m_mat_rot;
	std::string m_key;

private:


};

#endif
