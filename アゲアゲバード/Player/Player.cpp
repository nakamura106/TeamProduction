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

	m_pinfo.radius = 5.0f;	// �������

	m_pinfo.jamp_power = 3.0f;

	m_p_camera = new CAMERA(m_pos);

	m_pinfo.eye = m_p_camera->GetEyePos();
	m_pinfo.upvec = m_p_camera->GetCameraUp();

	m_jflag = false;
	m_stand_flag = false;
	
	m_key = "player";

	// �������킹(�g�k�~��]�~�ړ�)
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

	//Animation();

	// �������킹(�g�k�~��]�~�ړ�)
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

	// �v���C���[�̑O�����x�N�g�����o��
	D3DXVECTOR3 forward;
	forward = m_pinfo.eye - m_pos;

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&forward, &forward);

	// �v���C���[�̍������̃x�N�g��
	// �O�����̃x�N�g���ɒ��p�ȃx�N�g�����Z�o����
	D3DXVECTOR3 left;
	left = D3DXVECTOR3(forward.z, forward.y, forward.x);

#pragma region �v���C���[�̈ړ�
	// �O
	if (GetKey(W_KEY) || IsButtonPush(L_UpStick)) {
		m_pos.x += forward.x * m_pinfo.speed;
		m_pos.z += forward.z * m_pinfo.speed;

		m_pinfo.state = PlayerStatus::WALK;
	}
	// ��
	if (GetKey(S_KEY) || IsButtonPush(L_DownStick)) {
		m_pos.x -= forward.x * m_pinfo.speed;
		m_pos.z -= forward.z * m_pinfo.speed;

		m_pinfo.state = PlayerStatus::WALK;
	}
	// ��
	if (GetKey(A_KEY) || IsButtonPush(L_LeftStick)) {
		m_pos.x -= left.x * m_pinfo.speed;
		m_pos.z += left.z * m_pinfo.speed;

		m_pinfo.state = PlayerStatus::WALK;
	}
	// �E
	if (GetKey(D_KEY) || IsButtonPush(L_RightStick)) {
		m_pos.x += left.x * m_pinfo.speed;
		m_pos.z -= left.z * m_pinfo.speed;

		m_pinfo.state = PlayerStatus::WALK;
	}

	// ����
	if (GetKey(L_SHIFT) || IsButtonPush(AButton)) {
		m_pinfo.speed = m_pinfo.sprint_speed;
	}
	else {
		m_pinfo.speed = m_pinfo.walk_speed;
	}


	// �f�o�b�O�p
	// ��
	if (GetKey(E_KEY) || IsButtonPush(UpButton) || IsButtonPush(RightTButton)) {
		m_pos.y += m_pinfo.upvec.y * m_pinfo.speed;
	}
	//// ��
	//if (GetKey(Q_KEY) || IsButtonPush(DownButton) || IsButtonPush(LeftTButton)) {
	//	m_pos.y -= m_pinfo.upvec.y * m_pinfo.speed;
	//}

	// �W�����v
	if (GetKeyDown(Q_KEY) && m_stand_flag == true && m_jflag == false)
	{
		m_stand_flag = false;
		m_jflag = true;

		m_pinfo.state = PlayerStatus::JAMP;
	}
	if (m_jflag == true)
	{
		m_grav.ThrowingUp(m_pos.y, m_pinfo.jamp_power);
		m_pos.y = m_grav.GetPosY();

		// �n�ʂɂ��܂�
		if (m_pos.y < 0.0f)
		{
			m_stand_flag = true;
			m_jflag = false;
			m_pos.y = 0.0f;
			m_grav.ResetPalam();

			m_pinfo.state = PlayerStatus::WAIT;
		}
	}

	// �����̏�ɏ��܂ŗ�����
	if (m_stand_flag == false && m_jflag == false)
	{
		// ���R����
		m_grav.FreeFall(m_pos.y);
		m_pos.y = m_grav.GetPosY();
	}
}

void Character::Player::CollisionDetection()
{
	DataBank* p_db = DataBank::Instance();

	// �ߋ��̃v���C���[�̈ʒu���擾(�ړ��O)
	D3DXVECTOR3 befor_player = p_db->GetBeforePlayerPos();
	// ���݂̃v���C���[�̈ʒu���擾(�ړ���)
	D3DXVECTOR3 after_player = p_db->GetAfterPlayerPos();
	// �v���C���[������������ = ���݂̃v���C���[�̈ʒu - �ߋ��̃v���C���[�̈ʒu
	D3DXVECTOR3 amount_of_movement = after_player - befor_player;

#pragma region �}�b�v�ƃv���C���[�̓����蔻��

	// ����
	D3DXVECTOR3 map;
	float map_radius;
	map.x = p_db->GetMapCenterPos().x;
	map.z = p_db->GetMapCenterPos().z;
	map_radius = p_db->GetMapRadius();
	if (m_p_collision->HitMap(
		m_pos.x, m_pos.z,	// ���A�����	�F�v���C���[�̍��W(x,z)
		map.x, map.z,		// ��O�A�l����	�F�}�b�v�̍��W(x,z)
		m_pinfo.radius,		// ��܈���		�F�v���C���[�̔��a
		map_radius			// ��Z����		�F�}�b�v�̔��a
	) == true)
	{
		m_pos = befor_player;
	}
	// �V��ƃv���C���[�̓����蔻��
	D3DXVECTOR3 top;
	D3DXVECTOR3 bottom;
	top = p_db->GetMapTop();
	bottom = p_db->GetMapBottom();
	if (m_p_collision->HitAngle(
		m_pos,					// �������F�v���C���[�̍��W
		top,					// �������F�}�b�v�̒���̒��S���W
		bottom,					// ��O�����F�}�b�v�̒�ӂ̒��S���W
		30.0f	// ������		// ��l�����F���E�p�x
	) == true)
	{
		m_pos = befor_player;
	}
	// �n�ʂƃv���C���[�̓����蔻��
	/*
		//�|�b�g�̓����ɂ���Ƃ�
		�|�b�g�̒�ӂ̒l��艺����Ă���Ƃ�
	*/
	if (m_pos.y <= bottom.y)
	{
		m_stand_flag = true;
		m_pos = befor_player;
	}


#pragma endregion

#pragma region �A�C�e���ƃv���C���[�̓����蔻��

	//D3DXVECTOR3 item;
	//float item_radius;
	//item.x = p_db.GetItemPos().x;
	//item.y = p_db.GetItemPos().y;
	//item.z = p_db.GetItemPos().z;
	//item_radius = p_db.GetItemRadius();
	//if (m_p_collision->HitItemPlayer(
	//	m_pos.x, m_pos.y, m_pos.z,	// ���A��A�O�����F�v���C���[���W
	//	item.x, item.y, item.z,		// ��l�A�܁A�Z�����F�A�C�e�����W
	//	m_pinfo.radius,				// �掵�����@�@�@�@�F�v���C���[�̔��a
	//	item_radius					// �攪�����@�@�@�@�F�A�C�e���̔��a
	//) == true)
	//{
	//	
	//}

#pragma endregion

#pragma region �u���b�N�ƃv���C���[�̓����蔻��

	// �u���b�N�̕��͍�����
	// ��ʂƑ���
	for (const auto& itr : p_db->GetBlockPos())
	{
		if (m_p_collision->HitBox2(
			itr,			// �������F�u���b�N�̍��W
			m_pos,			// �������F�v���C���[���W
			5.0f,			// ��O�����F�u���b�N�̕�
			m_pinfo.radius	// ��l�����F�v���C���[�̔��a
		) == true)
		{
			m_pos = befor_player;
			if (m_pos.y > itr.y + 2.5f)
			{
				m_stand_flag = true;
				m_jflag = false;
				m_grav.ResetPalam();
			}
		}
		//else {
		//	// �����̏�ɏ��܂ŗ�����
		//	if (m_stand_flag == false)
		//	{
		//		// ���R����
		//		m_grav.FreeFall(m_pos.y);
		//		m_pos.y = m_grav.GetPosY();
		//	}
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

	p_db->SetAfterPlayerPos(m_pos);
}

void Character::Player::Animation()
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
		m_key = "player_throw";
		MyFbxManager::FbxManager::Instance()->Animation(m_key, 1.0f / 60.0f);
	}
}

void Character::Player::Draw()
{
	m_key = "player";
	MyFbxManager::FbxManager::Instance()->DrawFbx(m_key, m_mat_world);

	/*if (m_pinfo.state == PlayerStatus::WAIT)
	{
		m_key = "player_wait";
		MyFbxManager::FbxManager::Instance()->DrawFbx(m_key, m_mat_world);
	}
	if (m_pinfo.state == PlayerStatus::WALK)
	{
		m_key = "player_walk";
		MyFbxManager::FbxManager::Instance()->DrawFbx(m_key, m_mat_world);
	}
	if (m_pinfo.state == PlayerStatus::JAMP)
	{
		m_key = "player_jamp";
		MyFbxManager::FbxManager::Instance()->DrawFbx(m_key, m_mat_world);
	}
	if (m_pinfo.state == PlayerStatus::THROW)
	{
		m_key = "player_throw";
		MyFbxManager::FbxManager::Instance()->DrawFbx(m_key, m_mat_world);
	}*/
}