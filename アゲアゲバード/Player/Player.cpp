#include "Player.h"
#include"../Object/Pot.h"
#include"../Object/Oil.h"
#include"../Object/Block.h"
#include"../Object/Item.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
#include"../Manager/FbxManager.h"
#include"../Manager/SoundManager.h"
#include "../CSV/CSV.h"

Character::Player::Player(std::string str_)
{
	std::vector<std::string> strvec = *CSV::GetInstance()->GetParam(str_);

	m_pinfo.m_key = str_;			// アニメーション追加後は"player_wait"になる
	m_pinfo.state = PlayerInfo::PlayerStatus::WAIT;

	m_pinfo.m_pos.x = std::stof(strvec[static_cast<float>(PARAM::X)]);
	m_pinfo.m_pos.y = std::stof(strvec[static_cast<float>(PARAM::Y)]);
	m_pinfo.m_pos.z = std::stof(strvec[static_cast<float>(PARAM::Z)]);
	m_pinfo.radius = std::stof(strvec[static_cast<float>(PARAM::RADIUS)]);
	m_pinfo.jamp_power = std::stof(strvec[static_cast<float>(PARAM::JAMP_POWER)]);
	m_pinfo.walk_speed = std::stof(strvec[static_cast<float>(PARAM::WALK_SPEED)]);
	m_pinfo.sprint_speed = std::stof(strvec[static_cast<float>(PARAM::SPRINT_SPEED)]);
	m_pinfo.m_blockstock = std::stof(strvec[static_cast<float>(PARAM::BLOCK_STOCK)]);

	m_pinfo.speed = m_pinfo.walk_speed;

	m_pinfo.m_camera_pos.x = 0.0f;
	m_pinfo.m_camera_pos.y = 150.0f;
	m_pinfo.m_camera_pos.z = 0.0f;
	m_pinfo.m_p_camera = new CAMERA(m_pinfo.m_camera_pos);

	m_pinfo.eye = m_pinfo.m_p_camera->GetCameraData()->m_EyePos;
	m_pinfo.upvec = m_pinfo.m_p_camera->GetCameraData()->m_CameraUp;

	m_pinfo.m_item_effect_time = 0.0f;

	m_pinfo.m_jflag = false;
	m_pinfo.m_stand_flag = false;
	m_pinfo.m_item_hit_flag = false;
	m_pinfo.filloilfly = false;

	// かけ合わせ(拡縮×回転×移動)
	D3DXMatrixIdentity(&m_pinfo.m_mat_world);
	D3DXMatrixIdentity(&m_pinfo.m_mat_scale);
	D3DXMatrixIdentity(&m_pinfo.m_mat_rot_y);
	D3DXMatrixIdentity(&m_pinfo.m_mat_move);
	D3DXMatrixScaling(&m_pinfo.m_mat_scale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&m_pinfo.m_mat_rot_y, D3DXToRadian(m_pinfo.m_p_camera->GetCameraData()->m_Yaw));
	D3DXMatrixTranslation(&m_pinfo.m_mat_move, m_pinfo.m_pos.x, m_pinfo.m_pos.y, m_pinfo.m_pos.z);
	m_pinfo.m_mat_world = m_pinfo.m_mat_scale * m_pinfo.m_mat_rot_y * m_pinfo.m_mat_move;
	m_item = m_objectmanager->GetItem();
	m_block = m_objectmanager->GetBlock();
}

void Character::Player::Update()
{
	if (m_startproduction->GetStartProductionInfo()->m_uistartflag == true
		&& m_endproduction->GetEndProductionInfo()->fly_seflag != true
		&& m_endproduction->GetEndProductionInfo()->clear_seflag != true)
	{
		Move();

		SetBlock();
	}

	CollisionDetection();

	m_pinfo.m_p_camera->Update();


	//ThrowingItems();

	//Animation();

	// かけ合わせ(拡縮×回転×移動)
	D3DXMatrixScaling(&m_pinfo.m_mat_scale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&m_pinfo.m_mat_rot_y, D3DXToRadian(m_pinfo.m_p_camera->GetCameraData()->m_Yaw));
	D3DXMatrixTranslation(&m_pinfo.m_mat_move, m_pinfo.m_pos.x, m_pinfo.m_pos.y, m_pinfo.m_pos.z);
	m_pinfo.m_mat_world = m_pinfo.m_mat_scale * m_pinfo.m_mat_rot_y * m_pinfo.m_mat_move;
}

void Character::Player::Move()
{
	m_pinfo.m_before_player_pos = m_pinfo.m_pos;
	m_pinfo.eye = m_pinfo.m_p_camera->GetCameraData()->m_EyePos;

	// プレイヤーの前向きベクトルを出す
	D3DXVECTOR3 forward;
	forward = m_pinfo.eye - m_pinfo.m_pos;

	// ベクトルの正規化
	D3DXVec3Normalize(&forward, &forward);

	// プレイヤーの左向きのベクトル
	// 前向きのベクトルに直角なベクトルを算出する
	D3DXVECTOR3 left;
	left = D3DXVECTOR3(forward.z, forward.y, forward.x);

#pragma region プレイヤーの移動
	// 前
	if (GetKey(W_KEY) || IsButtonPush(L_UpStick)) {
		m_pinfo.m_pos.x += forward.x * m_pinfo.speed;
		m_pinfo.m_pos.z += forward.z * m_pinfo.speed;

		m_pinfo.state = PlayerInfo::PlayerStatus::WALK;
	}
	// 後
	if (GetKey(S_KEY) || IsButtonPush(L_DownStick)) {
		m_pinfo.m_pos.x -= forward.x * m_pinfo.speed;
		m_pinfo.m_pos.z -= forward.z * m_pinfo.speed;

		m_pinfo.state = PlayerInfo::PlayerStatus::WALK;
	}
	// 左
	if (GetKey(A_KEY) || IsButtonPush(L_LeftStick)) {
		m_pinfo.m_pos.x -= left.x * m_pinfo.speed;
		m_pinfo.m_pos.z += left.z * m_pinfo.speed;

		m_pinfo.state = PlayerInfo::PlayerStatus::WALK;
	}
	// 右
	if (GetKey(D_KEY) || IsButtonPush(L_RightStick)) {
		m_pinfo.m_pos.x += left.x * m_pinfo.speed;
		m_pinfo.m_pos.z -= left.z * m_pinfo.speed;

		m_pinfo.state = PlayerInfo::PlayerStatus::WALK;
	}

	// 走る
	if (GetKey(L_SHIFT) ||IsButtonPush(XButton)) {
		m_pinfo.speed = m_pinfo.sprint_speed;
	}
	else {
		m_pinfo.speed = m_pinfo.walk_speed;
	}

	// ジャンプ
	if ((GetKeyDown(SPACE_KEY) || IsButtonDown(AButton)) && m_pinfo.m_jflag == false)
	{
		m_pinfo.m_stand_flag = false;
		m_pinfo.m_jflag = true;
		m_pinfo.m_grav.ResetPalam();

		m_pinfo.state = PlayerInfo::PlayerStatus::JAMP;
	}
	if (m_pinfo.m_jflag == true)
	{
		m_pinfo.m_grav.ThrowingUp(m_pinfo.m_pos.y, m_pinfo.jamp_power);
		m_pinfo.m_pos.y = m_pinfo.m_grav.GetPosY();

		// 地面につくまで
		if (m_pinfo.m_pos.y <= 0.0f)
		{
			m_pinfo.m_stand_flag = true;
 			m_pinfo.m_jflag = false;
			m_pinfo.m_pos.y = 0.0f;
			m_pinfo.m_grav.ResetPalam();

			m_pinfo.state = PlayerInfo::PlayerStatus::WAIT;
		}
	}
	if (m_pinfo.m_pos.y <= 0.0f && m_pinfo.m_grav.GetPosY() <= 0.0f)
	{
		m_pinfo.m_stand_flag = true;
		m_pinfo.m_grav.ResetPalam();
	}
	// デバッグ用
	// 上
	if (GetKey(E_KEY) || IsButtonPush(UpButton) || IsButtonPush(RightTButton)) {
		m_pinfo.m_pos.y += m_pinfo.upvec.y * m_pinfo.speed;
	}
	// 下
	if (GetKey(Q_KEY) || IsButtonPush(DownButton) || IsButtonPush(LeftTButton)) {
		m_pinfo.m_pos.y -= m_pinfo.upvec.y * m_pinfo.speed;
	}

#pragma endregion 

	// 何かの上に乗るまで落ちる
	if (m_pinfo.m_stand_flag == false && m_pinfo.m_jflag == false && m_pinfo.m_grav.GetPosY() >= 0.0f)
	{
		// 自由落下
		m_pinfo.m_grav.FreeFall(m_pinfo.m_pos.y);
		m_pinfo.m_pos.y = m_pinfo.m_grav.GetPosY();
	}
}

void Character::Player::CollisionDetection()
{
#pragma region マップとプレイヤーの当たり判定

	// 側面map_radius = p_db->GetMapRadius();
	if (m_pinfo.m_p_collision->HitMap(
		m_pinfo.m_pos.x, m_pinfo.m_pos.z,	// 第一、二引数	：プレイヤーの座標(x,z)
		m_objectmanager->GetMap()->GetMapData()->m_pos.x, m_objectmanager->GetMap()->GetMapData()->m_pos.z,		// 第三、四引数	：マップの座標(x,z)
		m_pinfo.radius,		// 第五引数		：プレイヤーの半径
		m_objectmanager->GetMap()->GetMapData()->radius			// 第六引数		：マップの半径
	) == true)
	{
		m_pinfo.m_pos = m_pinfo.m_before_player_pos;
	}

	// 天井とプレイヤーの当たり判定
	if (m_pinfo.m_p_collision->HitAngle(
		m_pinfo.m_pos,					// 第一引数：プレイヤーの座標
		m_objectmanager->GetMap()->GetMapData()->m_map_top,					// 第二引数：マップの頂上の中心座標
		m_objectmanager->GetMap()->GetMapData()->m_map_bottom,					// 第三引数：マップの底辺の中心座標
		30.0f	// 今だけ		// 第四引数：限界角度
	) == true)
	{
		m_pinfo.m_pos = m_pinfo.m_before_player_pos;
	}
	// 地面とプレイヤーの当たり判定
	/*
		//ポットの内側にいるとき
		ポットの底辺の値より下回っているとき
	*/
	if (m_pinfo.m_pos.y <= m_objectmanager->GetMap()->GetMapData()->m_map_bottom.y)
	{
		m_pinfo.m_stand_flag = true;
		m_pinfo.m_pos = m_pinfo.m_before_player_pos;
	}

	if (m_objectmanager->GetFillOil()->GetFillOilData()->m_fall_flag == false)
	{
		if (m_pinfo.m_p_collision->HitOil(
			m_pinfo.m_pos,
			m_objectmanager->GetFillOil()->GetFillOilData()->m_pos,
			m_pinfo.radius,		// 第五引数		：プレイヤーの半径
			m_objectmanager->GetFillOil()->GetFillOilData()->radius			// 第六引数		：マップの半径
		) == true)
		{
			m_pinfo.filloilfly = true;
		}
	}
#pragma endregion

#pragma region アイテムとプレイヤーの当たり判定


	for (const auto&itr:*m_item)
	{
		if (m_pinfo.m_p_collision->HitItemPlayer(
			m_pinfo.m_pos,							// 第一引数：プレイヤー座標
			itr->GetItemData()->m_pos,				// 第二引数：アイテム座標
			m_pinfo.radius,							// 第三引数：プレイヤーの半径
			itr->GetItemData()->m_radius			// 第四引数：アイテムの半径
		) == true)
		{
			m_pinfo.m_item_hit_flag = true;
		}
		if (m_pinfo.m_item_hit_flag == true)
		{
			// スピード遅くする
			m_pinfo.speed = 0.2f;
			m_pinfo.m_item_effect_time++;
			if (m_pinfo.m_item_effect_time >= 5.0f)
			{
				m_pinfo.speed = m_pinfo.walk_speed;
				m_pinfo.m_item_hit_flag = false;
			}
		}
	}
	

#pragma endregion

#pragma region ブロックとプレイヤーの当たり判定

	// ブロックの幅は今だけ
	// 上面と側面
	for (const auto& itr : *m_block)
	{
		if (m_pinfo.m_p_collision->HitBox2(
			itr->GetBlockData()->m_pos,			// 第一引数：ブロックの座標
			m_pinfo.m_pos,						// 第二引数：プレイヤー座標
			1.5f,								// 第三引数：ブロックの幅
			m_pinfo.radius                     // 第四引数：プレイヤーの半径
		) == true)
		{
			m_pinfo.m_pos = m_pinfo.m_before_player_pos;
			if (m_pinfo.m_pos.y > itr->GetBlockData()->m_pos.y + 1.5f)
			{
				m_pinfo.m_stand_flag = true;
				m_pinfo.m_jflag = false;
				m_pinfo.m_grav.ResetPalam();
			}
		}
		else
		{
			m_pinfo.m_stand_flag = false;
		}
	
	}



#pragma endregion

	m_pinfo.m_after_player_pos = m_pinfo.m_pos;
}

void Character::Player::Animation()
{
	switch (m_pinfo.state)
	{
	case PlayerInfo::PlayerStatus::WAIT:
		m_pinfo.m_key = "player_wait";
		break;
	case PlayerInfo::PlayerStatus::WALK:
		m_pinfo.m_key = "player_walk";
		break;
	case PlayerInfo::PlayerStatus::JAMP:
		m_pinfo.m_key = "player_jamp";
		break;
	case PlayerInfo::PlayerStatus::THROW:
		m_pinfo.m_key = "player_throw";
		break;
	}
	MyFbxManager::FbxManager::Instance()->Animation(m_pinfo.m_key, 1.0f / 60.0f);
}

void Character::Player::SetBlock()
{
	
	if (m_pinfo.m_blockstock > 0)
	{
		if (GetKeyDown(Y_KEY) || IsButtonDown(RightBButton))
		{
			if (m_objectmanager->CreateBlock() == true)
			{
				SoundManager::Instance()->SoundClickSE();
				m_pinfo.m_blockstock--;
			}
		}
	}
}

void Character::Player::ThrowingItems()
{
	if (GetKeyDown(T_KEY) || IsButtonDown(RightBButton))
	{
		SoundManager::Instance()->SoundThrow();
		m_objectmanager->CreateItem();
	}
}

void Character::Player::Draw()
{
	m_pinfo.m_key = "player";

	/*switch (m_pinfo.state)
	{
	case PlayerStatus::WAIT:
		m_key = "player_wait";
		break;
	case PlayerStatus::WALK:
		m_key = "player_walk";
		break;
	case PlayerStatus::JAMP:
		m_key = "player_jamp";
		break;
	case PlayerStatus::THROW:
		m_key = "player_throw";
		break;
	}*/
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_pinfo.m_key, m_pinfo.m_mat_world);
}

void Character::Player::PlusBlockStock(int plusstock_)
{
	m_pinfo.m_blockstock += plusstock_;
}

D3DXVECTOR3 Character::Player::Amountofmovement()
{
	// プレイヤーが動いた距離 = 現在のプレイヤーの位置 - 過去のプレイヤーの位置
	D3DXVECTOR3 amount_of_movement = m_pinfo.m_after_player_pos - m_pinfo.m_before_player_pos;

	return amount_of_movement;
}

const Character::Player::PlayerInfo* Character::Player::GetPlayerData() const
{
	return &m_pinfo;
}