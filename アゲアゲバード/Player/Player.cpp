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

	m_pinfo.m_key = str_;			// �A�j���[�V�����ǉ����"player_wait"�ɂȂ�
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

	// �������킹(�g�k�~��]�~�ړ�)
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

	// �������킹(�g�k�~��]�~�ړ�)
	D3DXMatrixScaling(&m_pinfo.m_mat_scale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&m_pinfo.m_mat_rot_y, D3DXToRadian(m_pinfo.m_p_camera->GetCameraData()->m_Yaw));
	D3DXMatrixTranslation(&m_pinfo.m_mat_move, m_pinfo.m_pos.x, m_pinfo.m_pos.y, m_pinfo.m_pos.z);
	m_pinfo.m_mat_world = m_pinfo.m_mat_scale * m_pinfo.m_mat_rot_y * m_pinfo.m_mat_move;
}

void Character::Player::Move()
{
	m_pinfo.m_before_player_pos = m_pinfo.m_pos;
	m_pinfo.eye = m_pinfo.m_p_camera->GetCameraData()->m_EyePos;

	// �v���C���[�̑O�����x�N�g�����o��
	D3DXVECTOR3 forward;
	forward = m_pinfo.eye - m_pinfo.m_pos;

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&forward, &forward);

	// �v���C���[�̍������̃x�N�g��
	// �O�����̃x�N�g���ɒ��p�ȃx�N�g�����Z�o����
	D3DXVECTOR3 left;
	left = D3DXVECTOR3(forward.z, forward.y, forward.x);

#pragma region �v���C���[�̈ړ�
	// �O
	if (GetKey(W_KEY) || IsButtonPush(L_UpStick)) {
		m_pinfo.m_pos.x += forward.x * m_pinfo.speed;
		m_pinfo.m_pos.z += forward.z * m_pinfo.speed;

		m_pinfo.state = PlayerInfo::PlayerStatus::WALK;
	}
	// ��
	if (GetKey(S_KEY) || IsButtonPush(L_DownStick)) {
		m_pinfo.m_pos.x -= forward.x * m_pinfo.speed;
		m_pinfo.m_pos.z -= forward.z * m_pinfo.speed;

		m_pinfo.state = PlayerInfo::PlayerStatus::WALK;
	}
	// ��
	if (GetKey(A_KEY) || IsButtonPush(L_LeftStick)) {
		m_pinfo.m_pos.x -= left.x * m_pinfo.speed;
		m_pinfo.m_pos.z += left.z * m_pinfo.speed;

		m_pinfo.state = PlayerInfo::PlayerStatus::WALK;
	}
	// �E
	if (GetKey(D_KEY) || IsButtonPush(L_RightStick)) {
		m_pinfo.m_pos.x += left.x * m_pinfo.speed;
		m_pinfo.m_pos.z -= left.z * m_pinfo.speed;

		m_pinfo.state = PlayerInfo::PlayerStatus::WALK;
	}

	// ����
	if (GetKey(L_SHIFT) ||IsButtonPush(XButton)) {
		m_pinfo.speed = m_pinfo.sprint_speed;
	}
	else {
		m_pinfo.speed = m_pinfo.walk_speed;
	}

	// �W�����v
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

		// �n�ʂɂ��܂�
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
	// �f�o�b�O�p
	// ��
	if (GetKey(E_KEY) || IsButtonPush(UpButton) || IsButtonPush(RightTButton)) {
		m_pinfo.m_pos.y += m_pinfo.upvec.y * m_pinfo.speed;
	}
	// ��
	if (GetKey(Q_KEY) || IsButtonPush(DownButton) || IsButtonPush(LeftTButton)) {
		m_pinfo.m_pos.y -= m_pinfo.upvec.y * m_pinfo.speed;
	}

#pragma endregion 

	// �����̏�ɏ��܂ŗ�����
	if (m_pinfo.m_stand_flag == false && m_pinfo.m_jflag == false && m_pinfo.m_grav.GetPosY() >= 0.0f)
	{
		// ���R����
		m_pinfo.m_grav.FreeFall(m_pinfo.m_pos.y);
		m_pinfo.m_pos.y = m_pinfo.m_grav.GetPosY();
	}
}

void Character::Player::CollisionDetection()
{
#pragma region �}�b�v�ƃv���C���[�̓����蔻��

	// ����map_radius = p_db->GetMapRadius();
	if (m_pinfo.m_p_collision->HitMap(
		m_pinfo.m_pos.x, m_pinfo.m_pos.z,	// ���A�����	�F�v���C���[�̍��W(x,z)
		m_objectmanager->GetMap()->GetMapData()->m_pos.x, m_objectmanager->GetMap()->GetMapData()->m_pos.z,		// ��O�A�l����	�F�}�b�v�̍��W(x,z)
		m_pinfo.radius,		// ��܈���		�F�v���C���[�̔��a
		m_objectmanager->GetMap()->GetMapData()->radius			// ��Z����		�F�}�b�v�̔��a
	) == true)
	{
		m_pinfo.m_pos = m_pinfo.m_before_player_pos;
	}

	// �V��ƃv���C���[�̓����蔻��
	if (m_pinfo.m_p_collision->HitAngle(
		m_pinfo.m_pos,					// �������F�v���C���[�̍��W
		m_objectmanager->GetMap()->GetMapData()->m_map_top,					// �������F�}�b�v�̒���̒��S���W
		m_objectmanager->GetMap()->GetMapData()->m_map_bottom,					// ��O�����F�}�b�v�̒�ӂ̒��S���W
		30.0f	// ������		// ��l�����F���E�p�x
	) == true)
	{
		m_pinfo.m_pos = m_pinfo.m_before_player_pos;
	}
	// �n�ʂƃv���C���[�̓����蔻��
	/*
		//�|�b�g�̓����ɂ���Ƃ�
		�|�b�g�̒�ӂ̒l��艺����Ă���Ƃ�
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
			m_pinfo.radius,		// ��܈���		�F�v���C���[�̔��a
			m_objectmanager->GetFillOil()->GetFillOilData()->radius			// ��Z����		�F�}�b�v�̔��a
		) == true)
		{
			m_pinfo.filloilfly = true;
		}
	}
#pragma endregion

#pragma region �A�C�e���ƃv���C���[�̓����蔻��


	for (const auto&itr:*m_item)
	{
		if (m_pinfo.m_p_collision->HitItemPlayer(
			m_pinfo.m_pos,							// �������F�v���C���[���W
			itr->GetItemData()->m_pos,				// �������F�A�C�e�����W
			m_pinfo.radius,							// ��O�����F�v���C���[�̔��a
			itr->GetItemData()->m_radius			// ��l�����F�A�C�e���̔��a
		) == true)
		{
			m_pinfo.m_item_hit_flag = true;
		}
		if (m_pinfo.m_item_hit_flag == true)
		{
			// �X�s�[�h�x������
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

#pragma region �u���b�N�ƃv���C���[�̓����蔻��

	// �u���b�N�̕��͍�����
	// ��ʂƑ���
	for (const auto& itr : *m_block)
	{
		if (m_pinfo.m_p_collision->HitBox(
			itr->GetBlockData()->m_pos,			// �������F�u���b�N�̍��W
			m_pinfo.m_pos,						// �������F�v���C���[���W
			1.0f,								// ��O�����F�u���b�N�̕�
			m_pinfo.radius						// ��l�����F�v���C���[�̔��a
		) == true)
		{
			m_pinfo.m_pos = m_pinfo.m_before_player_pos;
			if (m_pinfo.m_pos.y > itr->GetBlockData()->m_pos.y + 2.0f)
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
	// �v���C���[������������ = ���݂̃v���C���[�̈ʒu - �ߋ��̃v���C���[�̈ʒu
	D3DXVECTOR3 amount_of_movement = m_pinfo.m_after_player_pos - m_pinfo.m_before_player_pos;

	return amount_of_movement;
}

const Character::Player::PlayerInfo* Character::Player::GetPlayerData() const
{
	return &m_pinfo;
}