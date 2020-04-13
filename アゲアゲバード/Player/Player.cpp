#include "Player.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
#include "../DataBank/DataBank.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	m_pos.x = pos_x_;
	m_pos.y = pos_y_;
	m_pos.z = pos_z_;
	m_pinfo.radius = 1.0f;	// 分からん

	m_p_camera = new CAMERA(m_pos);

	m_pinfo.eye = -m_p_camera->GetEyePos();
	
	m_key = "player";

	// かけ合わせ(拡縮×回転×移動)
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixIdentity(&m_mat_scale);
	//D3DXMatrixIdentity(&m_mat_rot);
	D3DXMatrixIdentity(&m_mat_rot);
	D3DXMatrixIdentity(&m_mat_rot_x);
	D3DXMatrixIdentity(&m_mat_rot_y);
	D3DXMatrixIdentity(&m_mat_rot_z);
	D3DXMatrixIdentity(&m_mat_move);
	D3DXMatrixScaling(&m_mat_scale, 10.0f, 10.0f, 10.0f);						// 拡縮そのまま
	D3DXMatrixRotationX(&m_mat_rot_x, D3DXToRadian(m_p_camera->GetYaw()));
	D3DXMatrixRotationY(&m_mat_rot_y, D3DXToRadian(m_p_camera->GetPitch()));
	D3DXMatrixRotationZ(&m_mat_rot_z, D3DXToRadian(m_p_camera->GetRoll()));
	D3DXMatrixMultiply(&m_mat_rot, &m_mat_rot, &m_mat_rot_x);
	D3DXMatrixMultiply(&m_mat_rot, &m_mat_rot, &m_mat_rot_y);
	D3DXMatrixMultiply(&m_mat_rot, &m_mat_rot, &m_mat_rot_z);
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);
	m_mat_world = m_mat_scale * m_mat_rot_x * m_mat_move;
}

void Character::Player::Update()
{
	DataBank* p_db = DataBank::Instance();

	m_p_camera->Update();

	//Move();

	//CollisionDetection();

	// かけ合わせ(拡縮×回転×移動)
	D3DXMatrixScaling(&m_mat_scale, 5.0f, 5.0f, 5.0f);
	/*D3DXMatrixRotationX(&m_mat_rot_x, D3DXToRadian(m_p_camera->GetYaw()));
	D3DXMatrixRotationY(&m_mat_rot_y, D3DXToRadian(m_p_camera->GetPitch()));
	D3DXMatrixRotationZ(&m_mat_rot_z, D3DXToRadian(m_p_camera->GetRoll()));
	D3DXMatrixMultiply(&m_mat_rot, &m_mat_rot, &m_mat_rot_x);
	D3DXMatrixMultiply(&m_mat_rot, &m_mat_rot, &m_mat_rot_y);
	D3DXMatrixMultiply(&m_mat_rot, &m_mat_rot, &m_mat_rot_z);*/
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);
	m_mat_world = m_mat_scale/* * m_mat_rot*/ * m_mat_move;

	p_db->SetPlayerPos(m_pos);
}

void Character::Player::Move()
{
	DataBank* p_db = DataBank::Instance();
	
	// 過去のカメラの位置を取得(移動前)
	D3DXVECTOR3 befor_cam = p_db->GetBeforeCameraPos();
	// 現在のカメラの位置を取得(移動後)
	D3DXVECTOR3 after_cam = p_db->GetAfterCameraPos();
	// カメラが動いた距離 = 現在のカメラの位置 - 過去のカメラの位置
	D3DXVECTOR3 amount_of_movement = after_cam - befor_cam;
	// プレイヤーにカメラの移動量を足す
	m_pos += amount_of_movement;
}

//void Character::Player::CollisionDetection()
//{
//	DataBank* p_db = DataBank::Instance();
//
//	/* マップとプレイヤーの当たり判定 */
//	// 側面
//	D3DXVECTOR3 map;
//	float map_radius;
//	map.x = p_db.GetMapPos().x;
//	map.z = p_db.GetMapPos().z;
//	map_radius = p_db.GetMapRadius();
//	if (m_p_collision->HitMap(
//		m_pos.x, m_pos.z,					// 第一、二引数	：プレイヤーの座標(x,z)
//		map.x, map.z,						// 第三、四引数	：マップの座標(x,z)
//		m_pinfo.radius,						// 第五引数		：プレイヤーの半径
//		map_radius							// 第六引数		：マップの半径
//	) == true)
//	{
//
//	}
//	// 天井とプレイヤーの当たり判定
//	D3DXVECTOR3 top;
//	D3DXVECTOR3 bottom;
//	top.x = p_db.GetMapTopPos().x;
//	top.y = p_db.GetMapTopPos().y;
//	top.z = p_db.GetMapTopPos().z;
//	bottom.x = p_db.GetMapBottomPos().x;
//	bottom.y = p_db.GetMapBottomPos().y;
//	bottom.z = p_db.GetMapBottomPos().z;
//	if (m_p_collision->HitAngle(
//		m_pos.x, m_pos.y, m_pos.z,		// 第一、二、三引数：プレイヤーの座標
//		top.x, top.y, top.z,			// 第四、五、六引数：マップの頂上の中心座標
//		bottom.x, bottom.y, bottom.z,	// 第七、八、九引数：マップの底辺の中心座標
//		flg_angle						// 第十引数　　　　：限界角度
//	) == true)
//	{
//		
//	}
//
//
//
//	/* アイテムとプレイヤーの当たり判定 */
//	D3DXVECTOR3 item;
//	float item_radius;
//	item.x = p_db.GetItemPos().x;
//	item.y = p_db.GetItemPos().y;
//	item.z = p_db.GetItemPos().z;
//	item_radius = p_db.GetItemRadius();
//	if (m_p_collision->HitItemPlayer(
//		m_pos.x, m_pos.y, m_pos.z,	// 第一、二、三引数：プレイヤー座標
//		item.x, item.y, item.z,		// 第四、五、六引数：アイテム座標
//		m_pinfo.radius,				// 第七引数　　　　：プレイヤーの半径
//		item_radius					// 第八引数　　　　：アイテムの半径
//	) == true)
//	{
//
//	}
//
//
//
//	/* ブロックとプレイヤーの当たり判定 */
//	// 側面
//	D3DXVECTOR3 block;
//	block = p_db->GetBlockPos();
//	if (m_p_collision->HitBox(
//		float block_pos_x_, float block_pos_y_, float block_pos_z_,		// 第一、二、三引数：ブロックの座標
//		m_pos.x, m_pos.y, m_pos.z,										// 第四、五、六引数：プレイヤー座標
//		float block_wight_,												// 第七引数　　　　：ブロックの幅
//		float player_radius_											// 第八引数　　　　：プレイヤーの半径
//	) == true)
//	{
//
//	}
//	// 上部にいるかどうか
//	if (m_p_collision->HitBoxTop(
//		float block_pos_x_, float block_pos_y_, float block_pos_z_,
//		m_pos.x, m_pos.y, m_pos.z,
//		float block_width_,
//		float player_radius_
//	) == true)
//	{
//
//	}
//	// プレイヤーの視線とブロック
//	if (m_p_collision->HitVisualBox(
//		// 第一、二、三引数：ブロックの座標
//		// 第四引数　　　　：ブロックの幅
//		// 第五引数　　　　：ブロックの奥行き
//	) == true)
//	{
//
//	}
//}