#include "Player.h"
#include "Engine/Input.h"
#include "Gravity.h"

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

	D3DXMatrixRotationX(&m_minfo.mat_rot_x, D3DXToRadian(p_m_camera->GetYaw()));
	D3DXMatrixTranslation(&m_minfo.mat_world, m_pinfo.pos_x, m_pinfo.pos_y, m_pinfo.pos_z);
	D3DXMatrixMultiply(&m_minfo.mat_world, &m_minfo.mat_rot_x, &m_minfo.mat_trans);

	m_fbx_mesh_data.fbxinfo.world = m_minfo.mat_world;

	MyFbxManager::FbxManager::Instance()->Animation("player", 1.0f / 60.0f);
}

void Character::Player::Move(float mass_)
{
	// プレイヤーの前後左右の移動
	m_pinfo.pos_x += p_m_camera->GetCamaraPos().x - m_pinfo.pos_x;
	m_pinfo.pos_y += p_m_camera->GetCamaraPos().y - m_pinfo.pos_y;
	m_pinfo.pos_z += p_m_camera->GetCamaraPos().z - m_pinfo.pos_z;
}

void Character::Player::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx("player",m_minfo.mat_world);
}




void Character::Player::FirstPersonPerspective(float pos_x_, float pos_y_, float pos_z_)
{
	float camera_pos_x, camera_pos_y, camera_pos_z;
	camera_pos_x = pos_x_;
	camera_pos_y = pos_y_ + 10.0f;
	camera_pos_z = pos_z_;

	p_m_camera = new CAMERA(camera_pos_x, camera_pos_y, camera_pos_z);
}