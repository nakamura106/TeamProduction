#ifndef OBJBASE_H_
#define OBJBASE_H_


#include "../Object/ObjectBase.h"
#include"../Engine/FBX.h"
class ObjectBase
{
protected:
	struct ObjectData {

		FBXMeshData m_object;

		D3DXVECTOR3 m_pos;
		D3DXMATRIX m_mat_world;		// ƒ[ƒ‹ƒh
		D3DXMATRIX m_mat_scale;		// Šgk		Œëš scall¨scaleH
		D3DXMATRIX m_mat_move;		// ˆÚ“®
		D3DXMATRIX m_mat_rot;		// ‰ñ“]
		D3DXMATRIX m_mat_rot_x;		// ‰ñ“]x²
		D3DXMATRIX m_mat_rot_y;		// ‰ñ“]y²
		D3DXMATRIX m_mat_rot_z;		// ‰ñ“]z²

		float radius;					// ”¼Œa(ƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è‚ğ‚Æ‚é‚½‚ß‚Ì)

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
