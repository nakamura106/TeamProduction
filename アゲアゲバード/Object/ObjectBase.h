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
	D3DXMATRIX m_mat_world;		// [h
	D3DXMATRIX m_mat_scale;		// gk		๋ scallจscaleH
	D3DXMATRIX m_mat_move;		// ฺฎ
	D3DXMATRIX m_mat_rot;		// ๑]
	D3DXMATRIX m_mat_rot_x;		// ๑]xฒ
	D3DXMATRIX m_mat_rot_y;		// ๑]yฒ
	D3DXMATRIX m_mat_rot_z;		// ๑]zฒ
	std::string m_key;	

private:


};

#endif
