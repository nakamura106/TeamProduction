#include "Player.h"
#include "Engine/Input.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	//m_fbx_mesh_data = m_fbx_manager.LoadFbxMesh("Res/FBX/PopBird_Export.fbx");

	m_pinfo.pos_x = pos_x_;
	m_pinfo.pos_y = pos_y_;
	m_pinfo.pos_z = pos_z_;

	FirstPersonPerspective(m_pinfo.pos_x, m_pinfo.pos_y, m_pinfo.pos_z);

	D3DXMatrixIdentity(&m_minfo.mat_world);
}

Character::Player::~Player()
{
	m_fbx_manager.ReleaseFbxMesh(&m_fbx_mesh_data);
}

void Character::Player::Update()
{
	//Move();

	p_camera->Update();
	p_camera->Move();
	p_camera->MouseRotate();

	D3DXMatrixRotationX(&m_minfo.mat_rot_x, D3DXToRadian(p_camera->GetYaw()));
	D3DXMatrixTranslation(&m_minfo.mat_world, m_pinfo.pos_x, m_pinfo.pos_y, m_pinfo.pos_z);
	D3DXMatrixMultiply(&m_minfo.mat_world, &m_minfo.mat_rot_x, &m_minfo.mat_trans);

	m_fbx_mesh_data.fbxinfo.world = m_minfo.mat_world;

	m_fbx_manager.Animation(&m_fbx_mesh_data, 1.0f / 60.0f);
}

void Character::Player::Move()
{
	m_pinfo.pos_x = p_camera->GetCamaraPos().x;
	m_pinfo.pos_y = p_camera->GetCamaraPos().y;
	m_pinfo.pos_z = p_camera->GetCamaraPos().z;


	//const float speed = 3.0f;

	//// �O
	//if (GetKey(W_KEY)) 
	//{
	//	m_pinfo.pos_z += speed;
	//}
	//// ��
	//if (GetKey(S_KEY)) 
	//{
	//	m_pinfo.pos_z -= speed;
	//}
	//// ��
	//if (GetKey(A_KEY)) 
	//{
	//	m_pinfo.pos_x -= speed;
	//}
	//// �E
	//if (GetKey(D_KEY)) 
	//{
	//	m_pinfo.pos_x += speed;
	//}

	//// �������ǉ����Ă܂�(�㉺�ɍs���������֗����Ǝv�����̂�)
	//// ��
	//if (GetKey(E_KEY)) 
	//{
	//	m_pinfo.pos_y += speed;
	//}
	//// ��
	//if (GetKey(Q_KEY)) 
	//{
	//	m_pinfo.pos_y -= speed;
	//}
}

void Character::Player::Draw()
{
	m_fbx_manager.DrawFbx(&m_fbx_mesh_data);
}




void Character::Player::FirstPersonPerspective(float pos_x_, float pos_y_, float pos_z_)
{
	float camera_pos_x, camera_pos_y, camera_pos_z;
	camera_pos_x = pos_x_;
	camera_pos_y = pos_y_ + 10.0f;
	camera_pos_z = pos_z_;

	p_camera = new CAMERA(camera_pos_x, camera_pos_y, camera_pos_z);
}