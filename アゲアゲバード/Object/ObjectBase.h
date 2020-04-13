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
	D3DXMATRIX m_mat_world;		// ƒ[ƒ‹ƒh
	D3DXMATRIX m_mat_scale;		// Šgk		Œëš scall¨scaleH
	D3DXMATRIX m_mat_move;		// ˆÚ“®
	D3DXMATRIX m_mat_rot;		// ‰ñ“]
	D3DXMATRIX m_mat_rot_x;		// ‰ñ“]x²
	D3DXMATRIX m_mat_rot_y;		// ‰ñ“]y²
	D3DXMATRIX m_mat_rot_z;		// ‰ñ“]z²
	std::string m_key;	

private:


};

#endif
