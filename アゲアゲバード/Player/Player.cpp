#include "Player.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
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
	//Move(m_pinfo.mass);

	p_m_camera->Update();
	p_m_camera->Move();
	p_m_camera->MouseRotate();

	Collision collision;
	/*
		// 第1、2引数	：プレイヤーの座標
		// 第3、4引数	：マップの座標
		// 第5引数		：プレイヤーの半径
		// 第6引数		：マップの半径
	*/
	/*if (collision.HitMap(m_pinfo.pos_x, m_pinfo.pos_z, 0.0f, 0.0f, 10.0f, 100.0f) == true)
	{

	}*/

	D3DXMatrixRotationX(&m_minfo.mat_rot_x, D3DXToRadian(p_m_camera->GetYaw()));
	D3DXMatrixTranslation(&m_minfo.mat_world, m_pinfo.pos_x, m_pinfo.pos_y, m_pinfo.pos_z);
	D3DXMatrixMultiply(&m_minfo.mat_world, &m_minfo.mat_rot_x, &m_minfo.mat_trans);

	m_fbx_mesh_data.fbxinfo.world = m_minfo.mat_world;

	//MyFbxManager::FbxManager::Instance()->Animation("player", 1.0f / 60.0f);
}

//void Character::Player::Move(float mass_)
//{
//	// カメラの前向きベクトルを出す
//	D3DXVECTOR3 forward;
//	forward = m_pinfo.pos_x - m_CameraPos;
//
//	// ベクトルの正規化
//	D3DXVec3Normalize(&forward, &forward);
//	//forward.y = 0.0f;
//
//	// カメラの左向きのベクトル
//	// 前向きのベクトルに直角なベクトルを算出する
//	D3DXVECTOR3 left;
//	left = D3DXVECTOR3(forward.z, forward.y, forward.x);
//
//	m_Velocity.x = forward.x * m_Speed;
//	m_Velocity.z = forward.z * m_Speed;
//
//	// プレイヤーの前後左右の移動
//	// 前
//	if (GetKey(W_KEY)) {
//		m_CameraPos.x += forward.x * m_Speed;
//		//m_CameraPos.y += forward.y * m_Speed;
//		m_CameraPos.z += forward.z * m_Speed;
//	}
//	// 後
//	if (GetKey(S_KEY)) {
//		m_CameraPos.x -= forward.x * m_Speed;
//		m_CameraPos.z -= forward.z * m_Speed;
//	}
//	// 左
//	if (GetKey(A_KEY)) {
//		m_CameraPos.x -= left.x * m_Speed;
//		m_CameraPos.z += left.z * m_Speed;
//	}
//	// 右
//	if (GetKey(D_KEY)) {
//		m_CameraPos.x += left.x * m_Speed;
//		m_CameraPos.z -= left.z * m_Speed;
//	}
//
//	// ジャンプ
//	if (GetKeyDown(E_KEY) && jflag == false)
//	{
//		jflag = true;
//	}
//	if (jflag == true)
//	{
//		grav.AddGravity(m_CameraPos.y, m_jamp);
//		m_CameraPos.y = grav.GetPosY();
//
//		if (m_CameraPos.y < 10.0f)
//		{
//			jflag = false;
//			m_CameraPos.y = 10.0f;
//			grav.ResetPalam();
//		}
//	}
//}

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