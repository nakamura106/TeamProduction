#ifndef PLAYER_H_
#define PLAYER_H_

#include "Manager/FbxManager.h"
#include "Engine/Camera.h"

struct PlayerInfo {
	float pos_x, pos_y, pos_z;
};

struct MatrixInfo {
	D3DXMATRIX mat_world;	// ƒ[ƒ‹ƒh
	D3DXMATRIX mat_scale;	// Šgk
	D3DXMATRIX mat_rot;		// ‰ñ“]
	D3DXMATRIX mat_rot_x;	// ‰ñ“]x²
	D3DXMATRIX mat_rot_y;	// ‰ñ“]y²
	D3DXMATRIX mat_rot_z;	// ‰ñ“]z²
	D3DXMATRIX mat_trans;	// ˆÚ“®
};

namespace Character
{
	class Player {
	public:
		Player() {}
		Player(float pos_x_, float pos_y_, float pos_z_);
		~Player();

	public:
		void Update();
		void Draw();

		void Move();

		PlayerInfo GetPos()
		{
			return m_pinfo;
		}

	private:
		void FirstPersonPerspective(float pos_x_, float pos_y_, float pos_z_);

	private:
		FbxManagera m_fbx_manager;
		FBXMeshData m_fbx_mesh_data;

		PlayerInfo m_pinfo;
		MatrixInfo m_minfo;

		CAMERA* p_camera;
		
	};
}
#endif