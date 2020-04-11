#include "Player.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
#include "../Utility/Collision.h"
#include "../DataBank/DataBank.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	//m_fbx_mesh_data = m_fbx_manager.LoadFbxMesh("Res/FBX/PopBird_Export.fbx");

	m_pos.x = pos_x_;
	m_pos.y = pos_y_;
	m_pos.z = pos_z_;

	m_p_camera = new CAMERA(m_pos);

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

	m_p_camera->Update();

	Move();

	Collision collision;
	D3DXVECTOR3 map;
	float map_radius;
	//map.x = p_db.GetMapPos().x;
	//map.z = p_db.GetMapPos().z;
	//map_radius = p_db.GetMapRadius();
	if (collision.HitMap(
		m_pos.x, m_pos.z,					// 第1、2引数	：プレイヤーの座標(x,z)
		0.0f/* map.x */, 0.0f/* map.z */,	// 第3、4引数	：マップの座標(x,z)
		10.0f,								// 第5引数		：プレイヤーの半径
		100.0f/* map_radius */				// 第6引数		：マップの半径
	) == true)
	{
		
	}
	D3DXMatrixRotationX(&m_mat_rot_x, D3DXToRadian(m_p_camera->GetYaw()));
	D3DXMatrixTranslation(&m_mat_world, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_rot_x, &m_mat_trans);

	m_fbx_mesh_data.fbxinfo.world = m_mat_world;

	//MyFbxManager::FbxManager::Instance()->Animation("player", 1.0f / 60.0f);

	p_db->SetPlayerPos(m_pos);
}

void Character::Player::Move()
{
	DataBank* p_db = DataBank::Instance();
	
	// 過去のカメラの位置を取得
	D3DXVECTOR3 befor_cam = p_db->GetBeforeCameraPos();
	// 現在のカメラの位置を取得
	D3DXVECTOR3 after_cam = p_db->GetAfterCameraPos();
	// カメラが動いた距離 = 現在のカメラの位置 - 過去のカメラの位置
	D3DXVECTOR3 amount_of_movement = after_cam - befor_cam;
	// プレイヤーにカメラの移動量を足す
	m_pos += amount_of_movement;
}

void Character::Player::Draw()
{
	MyFbxManager::FbxManager::Instance()->DrawFbx("player", m_mat_world);
}