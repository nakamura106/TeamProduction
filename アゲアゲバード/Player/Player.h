#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Manager/FbxManager.h"
#include "../Engine/Camera.h"
#include "../Object/ObjectBase.h"

enum class PlayerStatus {
	WAIT,		// �ҋ@
	WALK,		// ����
	SPRINT,		// ����
	JAMP,		// �W�����v
	THROW,		// ������
};

struct PlayerInfo {
	D3DXVECTOR3 pos;			// �v���C���[���W
	D3DXVECTOR3 eye;			// �v���C���[�̌����Ă������

	PlayerStatus state;			// ���

	//float mass;				// ����
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

		void Move();

		PlayerInfo GetPos()
		{
			return m_pinfo;
		}

	private:

	private:

		FBXMeshData m_fbx_mesh_data;

		PlayerInfo m_pinfo;
		MatrixInfo m_minfo;

		CAMERA* m_p_camera;
	};
}
#endif