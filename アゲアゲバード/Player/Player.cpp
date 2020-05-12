#include "Player.h"
#include"../Object/Pot.h"
#include"../Object/Block.h"
#include"../Object/Item.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
#include"../Production/StartProduction.h"
#include"../Manager/FbxManager.h"
#include"../Manager/ProductionManager.h"
#include"../Manager/SoundManager.h"
#include"../Manager/ObjectManager.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	m_pinfo.m_key = "player";	// �A�j���[�V�����ǉ����"player_wait"�ɂȂ�
	m_pinfo.state = PlayerInfo::PlayerStatus::WAIT;

	m_pinfo.m_pos.x = pos_x_;
	m_pinfo.m_pos.y = pos_y_;
	m_pinfo.m_pos.z = pos_z_;

	m_pinfo.m_camera_pos.x = 0.0f;
	m_pinfo.m_camera_pos.y = 150.0f;
	m_pinfo.m_camera_pos.z = 0.0f;


	m_pinfo.walk_speed = 0.5f;
	m_pinfo.sprint_speed = 1.0f;
	m_pinfo.speed = m_pinfo.walk_speed;

	m_pinfo.radius = 2.0f;	// �������

	m_pinfo.jamp_power = 2.0f;

	m_pinfo.m_blockstock = 20;
	
	m_pinfo.m_p_camera = new CAMERA(m_pinfo.m_camera_pos);

	m_pinfo.eye = m_pinfo.m_p_camera->GetCameraData()->m_EyePos;
	m_pinfo.upvec = m_pinfo.m_p_camera->GetCameraData()->m_CameraUp;

	m_pinfo.m_item_effect_time = 0.0f;

	m_pinfo.m_jflag = false;
	m_pinfo.m_stand_flag = false;
	m_pinfo.m_item_hit_flag = false;

	// �������킹(�g�k�~��]�~�ړ�)
	D3DXMatrixIdentity(&m_pinfo.m_mat_world);
	D3DXMatrixIdentity(&m_pinfo.m_mat_scale);
	D3DXMatrixIdentity(&m_pinfo.m_mat_rot_y);
	D3DXMatrixIdentity(&m_pinfo.m_mat_move);
	D3DXMatrixScaling(&m_pinfo.m_mat_scale, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationY(&m_pinfo.m_mat_rot_y, D3DXToRadian(m_pinfo.m_p_camera->GetCameraData()->m_Yaw));
	D3DXMatrixTranslation(&m_pinfo.m_mat_move, m_pinfo.m_pos.x, m_pinfo.m_pos.y, m_pinfo.m_pos.z);
	m_pinfo.m_mat_world = m_pinfo.m_mat_scale * m_pinfo.m_mat_rot_y * m_pinfo.m_mat_move;
	m_item = ObjectManager::Instance()->GetItem();
	m_block = ObjectManager::Instance()->GetBlock();
}

void Character::Player::Update()
{
	if (ProductionManager::Instance()->GetStartProduction()->GetStartProductionInfo()->m_uistartflag == true)
	{
		Move();

		SetBlock();
	}

	CollisionDetection();

	m_pinfo.m_p_camera->Update();


	ThrowingItems();

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
	if (GetKeyDown(E_KEY) || IsButtonDown(AButton) && m_pinfo.m_jflag == false)
	{
		m_pinfo.m_stand_flag = false;
		m_pinfo.m_jflag = true;

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
	m_pinfo.m_after_player_pos = m_pinfo.m_pos;
}

void Character::Player::CollisionDetection()
{
#pragma region �}�b�v�ƃv���C���[�̓����蔻��

	// ����map_radius = p_db->GetMapRadius();
	if (m_pinfo.m_p_collision->HitMap(
		m_pinfo.m_pos.x, m_pinfo.m_pos.z,	// ���A�����	�F�v���C���[�̍��W(x,z)
		ObjectManager::Instance()->GetMap()->GetMapData()->m_pos.x, ObjectManager::Instance()->GetMap()->GetMapData()->m_pos.z,		// ��O�A�l����	�F�}�b�v�̍��W(x,z)
		m_pinfo.radius,		// ��܈���		�F�v���C���[�̔��a
		ObjectManager::Instance()->GetMap()->GetMapData()->radius			// ��Z����		�F�}�b�v�̔��a
	) == true)
	{
		m_pinfo.m_pos = m_pinfo.m_before_player_pos;
	}

	// �V��ƃv���C���[�̓����蔻��
	if (m_pinfo.m_p_collision->HitAngle(
		m_pinfo.m_pos,					// �������F�v���C���[�̍��W
		ObjectManager::Instance()->GetMap()->GetMapData()->m_map_top,					// �������F�}�b�v�̒���̒��S���W
		ObjectManager::Instance()->GetMap()->GetMapData()->m_map_bottom,					// ��O�����F�}�b�v�̒�ӂ̒��S���W
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
	if (m_pinfo.m_pos.y <= ObjectManager::Instance()->GetMap()->GetMapData()->m_map_bottom.y)
	{
		m_pinfo.m_stand_flag = true;
		m_pinfo.m_pos = m_pinfo.m_before_player_pos;
	}

#pragma endregion

#pragma region �A�C�e���ƃv���C���[�̓����蔻��


	for (const auto&itr:*m_item)
	{
		if (m_pinfo.m_p_collision->HitItemPlayer(
			m_pinfo.m_pos,				// �������F�v���C���[���W
			itr->GetItemData()->m_pos,				// �������F�A�C�e�����W
			m_pinfo.radius,		// ��O�����F�v���C���[�̔��a
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
			m_pinfo.m_pos,			// �������F�v���C���[���W
			2.0f,			// ��O�����F�u���b�N�̕�
			m_pinfo.radius	// ��l�����F�v���C���[�̔��a
		) == true)
		{
			m_pinfo.m_pos = m_pinfo.m_before_player_pos;
			if (m_pinfo.m_pos.y > itr->GetBlockData()->m_pos.y + 2.5f)
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
		//if (m_p_collision->HitBoxTop(
		//	itr,			// �������F�u���b�N�̍��W
		//	m_pos,			// �������F�v���C���[���W
		//	2.0f,			// ��O�����F�u���b�N�̕�
		//	m_pinfo.radius	// ��l�����F�v���C���[�̔��a
		//) == false)
		//{
		//	m_stand_flag = false;
		//}
	}

	//// �v���C���[�̎����ƃu���b�N
	//for (const auto& itr : p_db->GetBlockPos())
	//{
	//	if (m_p_collision->HitVisualBox(
	//		itr,				// �������F�u���b�N�̍��W
	//		5.0f,				// �������F�u���b�N�̕�
	//		5.0f				// ��O�����F�u���b�N�̉��s��
	//		) == true)
	//	{
	//		
	//	}
	//}

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
		if (GetKeyDown(SPACE_KEY) || IsButtonDown(LeftBButton))
		{
			if (ObjectManager::Instance()->CreateBlock() == true)
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
		ObjectManager::Instance()->CreateItem();
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








