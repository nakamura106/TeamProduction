#include "Player.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
#include "../DataBank/DataBank.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	m_pos.x = pos_x_;
	m_pos.y = pos_y_;
	m_pos.z = pos_z_;

	m_p_camera = new CAMERA(m_pos);

	m_pinfo.eye = m_p_camera->GetEyePos();
	
	m_key = "player";

	// かけ合わせ(拡縮×回転×移動)
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixIdentity(&m_mat_scall);
	//D3DXMatrixIdentity(&m_mat_rot);
	D3DXMatrixIdentity(&m_mat_rot_x);
	D3DXMatrixIdentity(&m_mat_move);
	D3DXMatrixScaling(&m_mat_scall, 10.0f, 10.0f, 10.0f);						// 拡縮そのまま
	D3DXMatrixRotationX(&m_mat_rot_x, D3DXToRadian(m_p_camera->GetYaw()));
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);
	m_mat_world = m_mat_scall * m_mat_rot_x * m_mat_move;
}

void Character::Player::Update()
{
	DataBank* p_db = DataBank::Instance();

	m_p_camera->Update();

	//Move();

	D3DXVECTOR3 map;
	float map_radius;
	//map.x = p_db.GetMapPos().x;
	//map.z = p_db.GetMapPos().z;
	//map_radius = p_db.GetMapRadius();
	if (m_p_collision->HitMap(
		m_pos.x, m_pos.z,					// 第1、2引数	：プレイヤーの座標(x,z)
		0.0f/* map.x */, 0.0f/* map.z */,	// 第3、4引数	：マップの座標(x,z)
		10.0f,								// 第5引数		：プレイヤーの半径
		100.0f/* map_radius */				// 第6引数		：マップの半径
	) == true)
	{
		
	}

	// かけ合わせ(拡縮×回転×移動)
	D3DXMatrixRotationX(&m_mat_rot_x, D3DXToRadian(m_p_camera->GetYaw()));
	D3DXMatrixTranslation(&m_mat_world, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mat_world, &m_mat_rot_x, &m_mat_move);

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