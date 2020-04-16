#include "Player.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
#include "../DataBank/DataBank.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	m_pinfo.state = PlayerStatus::WAIT;

	m_pos.x = pos_x_;
	m_pos.y = pos_y_;
	m_pos.z = pos_z_;

	m_pinfo.walk_speed = 0.5f;
	m_pinfo.sprint_speed = 1.0f;
	m_pinfo.speed = m_pinfo.walk_speed;

	m_pinfo.radius = 1.0f;	// 分からん

	m_pinfo.jamp_power = 3.0f;

	m_p_camera = new CAMERA(m_pos);

	m_pinfo.eye = m_p_camera->GetEyePos();
	m_pinfo.upvec = m_p_camera->GetCameraUp();
	
	m_key = "player";

	// かけ合わせ(拡縮×回転×移動)
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixIdentity(&m_mat_scale);
	D3DXMatrixIdentity(&m_mat_rot_y);
	D3DXMatrixIdentity(&m_mat_move);
	D3DXMatrixScaling(&m_mat_scale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&m_mat_rot_y, D3DXToRadian(m_p_camera->GetYaw()));
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);
	m_mat_world = m_mat_scale * m_mat_rot_y * m_mat_move;
}

void Character::Player::Update()
{
	Move();

	CollisionDetection();

	m_p_camera->Update();

	// かけ合わせ(拡縮×回転×移動)
	D3DXMatrixScaling(&m_mat_scale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&m_mat_rot_y, D3DXToRadian(m_p_camera->GetYaw()));
	D3DXMatrixTranslation(&m_mat_move, m_pos.x, m_pos.y, m_pos.z);
	m_mat_world = m_mat_scale * m_mat_rot_y * m_mat_move;
}

void Character::Player::Move()
{
	DataBank* p_db = DataBank::Instance();
	p_db->SetBeforePlayerPos(m_pos);
	
	m_pinfo.eye = m_p_camera->GetEyePos();

	// プレイヤーの前向きベクトルを出す
	D3DXVECTOR3 forward;
	forward = m_pinfo.eye - m_pos;

	// ベクトルの正規化
	D3DXVec3Normalize(&forward, &forward);

	// プレイヤーの左向きのベクトル
	// 前向きのベクトルに直角なベクトルを算出する
	D3DXVECTOR3 left;
	left = D3DXVECTOR3(forward.z, forward.y, forward.x);

#pragma region プレイヤーの移動
	// 前
	if (GetKey(W_KEY) || IsButtonPush(L_UpStick)) {
		m_pos.x += forward.x * m_pinfo.speed;
		m_pos.z += forward.z * m_pinfo.speed;
	}
	// 後
	if (GetKey(S_KEY) || IsButtonPush(L_DownStick)) {
		m_pos.x -= forward.x * m_pinfo.speed;
		m_pos.z -= forward.z * m_pinfo.speed;
	}
	// 左
	if (GetKey(A_KEY) || IsButtonPush(L_LeftStick)) {
		m_pos.x -= left.x * m_pinfo.speed;
		m_pos.z += left.z * m_pinfo.speed;
	}
	// 右
	if (GetKey(D_KEY) || IsButtonPush(L_RightStick)) {
		m_pos.x += left.x * m_pinfo.speed;
		m_pos.z -= left.z * m_pinfo.speed;
	}

	// 走る
	if (GetKey(L_SHIFT) || IsButtonPush(AButton)) {
		m_pinfo.speed = m_pinfo.sprint_speed;
	}
	else {
		m_pinfo.speed = m_pinfo.walk_speed;
	}


	// デバッグ用
	// 上
	if (GetKey(E_KEY) || IsButtonPush(UpButton) || IsButtonPush(RightTButton)) {
		m_pos.y += m_pinfo.upvec.y * m_pinfo.speed;
	}
	//// 下
	//if (GetKey(Q_KEY) || IsButtonPush(DownButton) || IsButtonPush(LeftTButton)) {
	//	m_pos.y -= m_pinfo.upvec.y * m_pinfo.speed;
	//}

	// ジャンプ
	if (GetKeyDown(Q_KEY) && m_jflag == false)
	{
		m_jflag = true;
	}
	if (m_jflag == true)
	{
		m_grav.AddGravity(m_pos.y, m_pinfo.jamp_power);
		m_pos.y = m_grav.GetPosY();

		if (m_pos.y < 0.0f)
		{
			m_jflag = false;
			m_pos.y = 0.0f;
			m_grav.ResetPalam();
		}
	}
}

void Character::Player::CollisionDetection()
{
	DataBank* p_db = DataBank::Instance();

	// 過去のプレイヤーの位置を取得(移動前)
	D3DXVECTOR3 befor_player = p_db->GetBeforePlayerPos();
	// 現在のプレイヤーの位置を取得(移動後)
	D3DXVECTOR3 after_player = p_db->GetAfterPlayerPos();
	// プレイヤーが動いた距離 = 現在のプレイヤーの位置 - 過去のプレイヤーの位置
	D3DXVECTOR3 amount_of_movement = after_player - befor_player;

#pragma region マップとプレイヤーの当たり判定

	// 側面
	D3DXVECTOR3 map;
	float map_radius;
	map.x = p_db->GetMapCenterPos().x;
	map.z = p_db->GetMapCenterPos().z;
	map_radius = p_db->GetMapRadius();
	if (m_p_collision->HitMap(
		m_pos.x, m_pos.z,	// 第一、二引数	：プレイヤーの座標(x,z)
		map.x, map.z,		// 第三、四引数	：マップの座標(x,z)
		m_pinfo.radius,		// 第五引数		：プレイヤーの半径
		map_radius			// 第六引数		：マップの半径
	) == true)
	{
		m_pos = befor_player;
	}
	// 天井とプレイヤーの当たり判定
	D3DXVECTOR3 top;
	D3DXVECTOR3 bottom;
	top = p_db->GetMapTop();
	bottom = p_db->GetMapBottom();
	if (m_p_collision->HitAngle(
		m_pos,					// 第一引数：プレイヤーの座標
		top,					// 第二引数：マップの頂上の中心座標
		bottom,					// 第三引数：マップの底辺の中心座標
		30.0f	// 今だけ		// 第四引数：限界角度
	) == true)
	{
		m_pos = befor_player;
	}

#pragma endregion

#pragma region アイテムとプレイヤーの当たり判定

	//D3DXVECTOR3 item;
	//float item_radius;
	//item.x = p_db.GetItemPos().x;
	//item.y = p_db.GetItemPos().y;
	//item.z = p_db.GetItemPos().z;
	//item_radius = p_db.GetItemRadius();
	//if (m_p_collision->HitItemPlayer(
	//	m_pos.x, m_pos.y, m_pos.z,	// 第一、二、三引数：プレイヤー座標
	//	item.x, item.y, item.z,		// 第四、五、六引数：アイテム座標
	//	m_pinfo.radius,				// 第七引数　　　　：プレイヤーの半径
	//	item_radius					// 第八引数　　　　：アイテムの半径
	//) == true)
	//{
	//	
	//}

#pragma endregion

#pragma region ブロックとプレイヤーの当たり判定

	// ブロックの幅は今だけ
	// 側面
	for (const auto& itr : p_db->GetBlockPos())
	{
		if (m_p_collision->HitBox2(
			itr,			// 第一引数：ブロックの座標
			m_pos,			// 第二引数：プレイヤー座標
			5.0f,			// 第三引数：ブロックの幅
			m_pinfo.radius	// 第四引数：プレイヤーの半径
		) == true)
		{
			m_pos = befor_player;
		}
	}
	// 上部にいるかどうか
	for (const auto& itr : p_db->GetBlockPos())
	{
		if (m_p_collision->HitBoxTop(
			itr,
			m_pos,
			5.0f,
			m_pinfo.radius
		) == true)
		{
			m_jflag = false;
		}
	}
	//// プレイヤーの視線とブロック
	//for (const auto& itr : p_db->GetBlockPos())
	//{
	//	if (m_p_collision->HitVisualBox(
	//		itr,				// 第一引数：ブロックの座標
	//		10.0f,				// 第二引数：ブロックの幅
	//		10.0f				// 第三引数：ブロックの奥行き
	//		) == true)
	//	{
	//		
	//	}
	//}

#pragma endregion

	p_db->SetAfterPlayerPos(m_pos);
}

void Character::Player::Draw()
{
	if (m_pinfo.state == PlayerStatus::WAIT)
	{
		m_key = "player_wait";
		MyFbxManager::FbxManager::Instance()->Animation(m_key, 1.0f / 60.0f);
	}
	if (m_pinfo.state == PlayerStatus::WALK)
	{
		m_key = "player_walk";
		MyFbxManager::FbxManager::Instance()->Animation(m_key, 1.0f / 60.0f);
	}
	if (m_pinfo.state == PlayerStatus::JAMP)
	{
		m_key = "player_jamp";
		MyFbxManager::FbxManager::Instance()->Animation(m_key, 1.0f / 60.0f);
	}
	if (m_pinfo.state == PlayerStatus::THROW)
	{
		m_key = "player_shrow";
		MyFbxManager::FbxManager::Instance()->Animation(m_key, 1.0f / 60.0f);
	}
}