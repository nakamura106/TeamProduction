#include "Player.h"
#include "../Engine/Input.h"
#include "../Utility/Gravity.h"
#include "../DataBank/DataBank.h"

Character::Player::Player(float pos_x_, float pos_y_, float pos_z_)
{
	m_pos.x = pos_x_;
	m_pos.y = pos_y_;
	m_pos.z = pos_z_;
	m_pinfo.radius = 1.0f;	// �������

	m_p_camera = new CAMERA(m_pos);

	m_pinfo.eye = -m_p_camera->GetEyePos();
	
	m_key = "player";

	// �������킹(�g�k�~��]�~�ړ�)
	D3DXMatrixIdentity(&m_mat_world);
	D3DXMatrixIdentity(&m_mat_scale);
	//D3DXMatrixIdentity(&m_mat_rot);
	D3DXMatrixIdentity(&m_mat_rot);
	D3DXMatrixIdentity(&m_mat_rot_x);
	D3DXMatrixIdentity(&m_mat_rot_y);
	D3DXMatrixIdentity(&m_mat_rot_z);
	D3DXMatrixIdentity(&m_mat_move);
	D3DXMatrixScaling(&m_mat_scale, 10.0f, 10.0f, 10.0f);						// �g�k���̂܂�
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

	// �������킹(�g�k�~��]�~�ړ�)
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
	
	// �ߋ��̃J�����̈ʒu���擾(�ړ��O)
	D3DXVECTOR3 befor_cam = p_db->GetBeforeCameraPos();
	// ���݂̃J�����̈ʒu���擾(�ړ���)
	D3DXVECTOR3 after_cam = p_db->GetAfterCameraPos();
	// �J���������������� = ���݂̃J�����̈ʒu - �ߋ��̃J�����̈ʒu
	D3DXVECTOR3 amount_of_movement = after_cam - befor_cam;
	// �v���C���[�ɃJ�����̈ړ��ʂ𑫂�
	m_pos += amount_of_movement;
}

//void Character::Player::CollisionDetection()
//{
//	DataBank* p_db = DataBank::Instance();
//
//	/* �}�b�v�ƃv���C���[�̓����蔻�� */
//	// ����
//	D3DXVECTOR3 map;
//	float map_radius;
//	map.x = p_db.GetMapPos().x;
//	map.z = p_db.GetMapPos().z;
//	map_radius = p_db.GetMapRadius();
//	if (m_p_collision->HitMap(
//		m_pos.x, m_pos.z,					// ���A�����	�F�v���C���[�̍��W(x,z)
//		map.x, map.z,						// ��O�A�l����	�F�}�b�v�̍��W(x,z)
//		m_pinfo.radius,						// ��܈���		�F�v���C���[�̔��a
//		map_radius							// ��Z����		�F�}�b�v�̔��a
//	) == true)
//	{
//
//	}
//	// �V��ƃv���C���[�̓����蔻��
//	D3DXVECTOR3 top;
//	D3DXVECTOR3 bottom;
//	top.x = p_db.GetMapTopPos().x;
//	top.y = p_db.GetMapTopPos().y;
//	top.z = p_db.GetMapTopPos().z;
//	bottom.x = p_db.GetMapBottomPos().x;
//	bottom.y = p_db.GetMapBottomPos().y;
//	bottom.z = p_db.GetMapBottomPos().z;
//	if (m_p_collision->HitAngle(
//		m_pos.x, m_pos.y, m_pos.z,		// ���A��A�O�����F�v���C���[�̍��W
//		top.x, top.y, top.z,			// ��l�A�܁A�Z�����F�}�b�v�̒���̒��S���W
//		bottom.x, bottom.y, bottom.z,	// �掵�A���A������F�}�b�v�̒�ӂ̒��S���W
//		flg_angle						// ��\�����@�@�@�@�F���E�p�x
//	) == true)
//	{
//		
//	}
//
//
//
//	/* �A�C�e���ƃv���C���[�̓����蔻�� */
//	D3DXVECTOR3 item;
//	float item_radius;
//	item.x = p_db.GetItemPos().x;
//	item.y = p_db.GetItemPos().y;
//	item.z = p_db.GetItemPos().z;
//	item_radius = p_db.GetItemRadius();
//	if (m_p_collision->HitItemPlayer(
//		m_pos.x, m_pos.y, m_pos.z,	// ���A��A�O�����F�v���C���[���W
//		item.x, item.y, item.z,		// ��l�A�܁A�Z�����F�A�C�e�����W
//		m_pinfo.radius,				// �掵�����@�@�@�@�F�v���C���[�̔��a
//		item_radius					// �攪�����@�@�@�@�F�A�C�e���̔��a
//	) == true)
//	{
//
//	}
//
//
//
//	/* �u���b�N�ƃv���C���[�̓����蔻�� */
//	// ����
//	D3DXVECTOR3 block;
//	block = p_db->GetBlockPos();
//	if (m_p_collision->HitBox(
//		float block_pos_x_, float block_pos_y_, float block_pos_z_,		// ���A��A�O�����F�u���b�N�̍��W
//		m_pos.x, m_pos.y, m_pos.z,										// ��l�A�܁A�Z�����F�v���C���[���W
//		float block_wight_,												// �掵�����@�@�@�@�F�u���b�N�̕�
//		float player_radius_											// �攪�����@�@�@�@�F�v���C���[�̔��a
//	) == true)
//	{
//
//	}
//	// �㕔�ɂ��邩�ǂ���
//	if (m_p_collision->HitBoxTop(
//		float block_pos_x_, float block_pos_y_, float block_pos_z_,
//		m_pos.x, m_pos.y, m_pos.z,
//		float block_width_,
//		float player_radius_
//	) == true)
//	{
//
//	}
//	// �v���C���[�̎����ƃu���b�N
//	if (m_p_collision->HitVisualBox(
//		// ���A��A�O�����F�u���b�N�̍��W
//		// ��l�����@�@�@�@�F�u���b�N�̕�
//		// ��܈����@�@�@�@�F�u���b�N�̉��s��
//	) == true)
//	{
//
//	}
//}