#include "Player.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
#include "../Utility/Collision.h"
#include "../DataBank/DataBank.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	//m_fbx_mesh_data = m_fbx_manager.LoadFbxMesh("Res/FBX/PopBird_Export.fbx");

	m_pinfo.pos.x = pos_x_;
	m_pinfo.pos.y = pos_y_;
	m_pinfo.pos.z = pos_z_;

	m_p_camera = new CAMERA(m_pinfo.pos);

	m_pinfo.eye = m_p_camera->GetEyePos();
	
	D3DXMatrixIdentity(&m_mat_world);
}

Character::Player::~Player()
{
	MyFbxManager::FbxManager::Instance()->AllReleaseMesh(&m_fbx_mesh_data);
}

void Character::Player::Update()
{
	DataBank* p_db = DataBank::Instance();

	m_p_camera->Move();
	m_p_camera->MouseRotate();
	m_p_camera->Update();

	Move();

	Collision collision;
	/*
		// ��1�A2����	�F�v���C���[�̍��W
		// ��3�A4����	�F�}�b�v�̍��W
		// ��5����		�F�v���C���[�̔��a
		// ��6����		�F�}�b�v�̔��a
	*/
	
	if (collision.HitMap(m_pinfo.pos.x, m_pinfo.pos.z, 0.0f, 0.0f, 10.0f, 100.0f) == true)
	{
		
	}

	D3DXMatrixRotationX(&m_minfo.mat_rot_x, D3DXToRadian(m_p_camera->GetYaw()));
	D3DXMatrixTranslation(&m_minfo.mat_world, m_pinfo.pos.x, m_pinfo.pos.y, m_pinfo.pos.z);
	D3DXMatrixMultiply(&m_minfo.mat_world, &m_minfo.mat_rot_x, &m_minfo.mat_trans);

	m_fbx_mesh_data.fbxinfo.world = m_minfo.mat_world;

	//MyFbxManager::FbxManager::Instance()->Animation("player", 1.0f / 60.0f);

	p_db->SetPlayerPos(m_pinfo.pos);
}

void Character::Player::Move()
{
	DataBank* p_db = DataBank::Instance();

	// ���݂̃J�����̈ʒu���擾
	D3DXVECTOR3 after_cam = m_p_camera->GetCamaraPos();
	// �ߋ��̃J�����̈ʒu���擾
	D3DXVECTOR3 befor_cam = p_db->GetCameraPos();
	// �J���������������� = ���݂̃J�����̈ʒu - �ߋ��̃J�����̈ʒu
	D3DXVECTOR3 amount_of_movement = after_cam - befor_cam;
	// �v���C���[�ɃJ�����̈ړ��ʂ𑫂�
	m_pinfo.pos += amount_of_movement;
}

void Character::Player::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx("player", m_minfo.mat_world);
}