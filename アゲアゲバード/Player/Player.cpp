#include "Player.h"
#include "../Engine/Input.h"
#include "../Gravity.h"
#include "../Utility/Collision.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	//m_fbx_mesh_data = m_fbx_manager.LoadFbxMesh("Res/FBX/PopBird_Export.fbx");

	m_pinfo.pos_x = pos_x_;
	m_pinfo.pos_y = pos_y_;
	m_pinfo.pos_z = pos_z_;
	m_pinfo.mass = 100.0f;

	FirstPersonPerspective(m_pinfo.pos_x, m_pinfo.pos_y, m_pinfo.pos_z);

	D3DXMatrixIdentity(&m_minfo.mat_world);
}

Character::Player::~Player()
{
	MyFbxManager::FbxManager::Instance()->AllReleaseMesh(&m_fbx_mesh_data);
}

void Character::Player::Update()
{
	Move(m_pinfo.mass);

	p_m_camera->Update();
	p_m_camera->Move();
	p_m_camera->MouseRotate();

	Collision collision;
	/*
		// ��1�A2����	�F�v���C���[�̍��W
		// ��3�A4����	�F�}�b�v�̍��W
		// ��5����		�F�v���C���[�̔��a
		// ��6����		�F�}�b�v�̔��a
	*/
	if (collision.HitMap(m_pinfo.pos_x, m_pinfo.pos_z, 0.0f, 0.0f, 10.0f, 100.0f) == true)
	{

	}

	D3DXMatrixRotationX(&m_minfo.mat_rot_x, D3DXToRadian(p_m_camera->GetYaw()));
	D3DXMatrixTranslation(&m_minfo.mat_world, m_pinfo.pos_x, m_pinfo.pos_y, m_pinfo.pos_z);
	D3DXMatrixMultiply(&m_minfo.mat_world, &m_minfo.mat_rot_x, &m_minfo.mat_trans);

	m_fbx_mesh_data.fbxinfo.world = m_minfo.mat_world;

	MyFbxManager::FbxManager::Instance()->Animation("player", 1.0f / 60.0f);
}

void Character::Player::Move(float mass_)
{
	// �J�����̑O�����x�N�g�����o��
	D3DXVECTOR3 forward;
	forward = m_pinfo.pos_x - m_CameraPos;

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&forward, &forward);
	//forward.y = 0.0f;

	// �J�����̍������̃x�N�g��
	// �O�����̃x�N�g���ɒ��p�ȃx�N�g�����Z�o����
	D3DXVECTOR3 left;
	left = D3DXVECTOR3(forward.z, forward.y, forward.x);

	m_Velocity.x = forward.x * m_Speed;
	m_Velocity.z = forward.z * m_Speed;

	// �v���C���[�̑O�㍶�E�̈ړ�
	// �O
	if (GetKey(W_KEY)) {
		m_CameraPos.x += forward.x * m_Speed;
		//m_CameraPos.y += forward.y * m_Speed;
		m_CameraPos.z += forward.z * m_Speed;
	}
	// ��
	if (GetKey(S_KEY)) {
		m_CameraPos.x -= forward.x * m_Speed;
		m_CameraPos.z -= forward.z * m_Speed;
	}
	// ��
	if (GetKey(A_KEY)) {
		m_CameraPos.x -= left.x * m_Speed;
		m_CameraPos.z += left.z * m_Speed;
	}
	// �E
	if (GetKey(D_KEY)) {
		m_CameraPos.x += left.x * m_Speed;
		m_CameraPos.z -= left.z * m_Speed;
	}

	// �W�����v
	if (GetKeyDown(E_KEY) && jflag == false)
	{
		jflag = true;
	}
	if (jflag == true)
	{
		grav.AddGravity(m_CameraPos.y, m_jamp);
		m_CameraPos.y = grav.GetPosY();

		if (m_CameraPos.y < 10.0f)
		{
			jflag = false;
			m_CameraPos.y = 10.0f;
			grav.ResetPalam();
		}
	}
}

void Character::Player::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx("player", m_minfo.mat_world);
}




void Character::Player::FirstPersonPerspective(float pos_x_, float pos_y_, float pos_z_)
{
	float camera_pos_x, camera_pos_y, camera_pos_z;
	camera_pos_x = pos_x_;
	camera_pos_y = pos_y_ + 10.0f;
	camera_pos_z = pos_z_;

	p_m_camera = new CAMERA(camera_pos_x, camera_pos_y, camera_pos_z);
}