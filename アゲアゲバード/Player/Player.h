#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Manager/FbxManager.h"
#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"

struct PlayerInfo {
	float pos_x, pos_y, pos_z;		// �v���C���[���W
	float mass;						// ����
};

struct MatrixInfo {
	D3DXMATRIX mat_world;	// ���[���h
	D3DXMATRIX mat_scale;	// �g�k
	D3DXMATRIX mat_rot;		// ��]
	D3DXMATRIX mat_rot_x;	// ��]x��
	D3DXMATRIX mat_rot_y;	// ��]y��
	D3DXMATRIX mat_rot_z;	// ��]z��
	D3DXMATRIX mat_trans;	// �ړ�
};

namespace Character
{
	class Player : public ObjectBase {
	public:
		Player(float pos_x_, float pos_y_, float pos_z_);
		~Player();

	public:
		void Update();
		void Draw();

		void Move(float mass_);

		PlayerInfo GetPos()
		{
			return m_pinfo;
		}

	private:
		void FirstPersonPerspective(float pos_x_, float pos_y_, float pos_z_);

	private:

		FBXMeshData m_fbx_mesh_data;

		PlayerInfo m_pinfo;
		MatrixInfo m_minfo;


		CAMERA* p_m_camera;

	};
}
#endif