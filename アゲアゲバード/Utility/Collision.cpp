#include "Collision.h"
#include <math.h>
#include <d3dx9.h>
#include "Vec.h"

//�g��Ȃ�
//bool Collision::UpdateHit(HitObject tareget, HitObject tareget2)
//{
//	if ((tareget == HitObject::Player && tareget == HitObject::Block)||(tareget == HitObject::Block && tareget == HitObject::Player))
//	{
//		if (HitBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_,
//			float block_wight_, float player_radius_) == true)
//		{
//			return true;
//		}
//	}
//	if ((tareget == HitObject::Player && tareget == HitObject::Item) || (tareget == HitObject::Item && tareget == HitObject::Player))
//	{
//		if (HitItem(float player_pos_x_, float player_pos_y_, float player_pos_z_, float item_pos_x_, float item_pos_y_, float item_pos_z_, float player_radius, float item_radius) == true)
//		{
//			return true;
//		}
//	}
//	if ((tareget == HitObject::Player && tareget == HitObject::Map) || (tareget == HitObject::Map && tareget == HitObject::Player))
//	{
//		if (HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_, float player_circle_radius_, float map_circle_radius_) == true)
//		{
//			return true;
//		}
//		else if (HitAngle(float player_pos_x, float player_pos_y, float player_pos_z, float maptop_pos_x, float maptop_pos_y, float maptop_pos_z, float mapunder_pos_x, float mapunder_pos_y, float mapunder_pos_z, float flg_angle) == true)
//		{
//			return true;
//		}
//	}
//
//	if (tareget == HitObject::PlayerEye && tareget == HitObject::Block)
//	{
//		if (HitBox1(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth_) == true)
//		{
//			return true;
//		}
//	}
//	
//}

//�v���C���[�ƃA�C�e��
bool Collision::HitItemPlayer(float player_pos_x_, float player_pos_y_, float player_pos_z_, float item_pos_x_, float item_pos_y_, float item_pos_z_, float player_radius, float item_radius)
{
	float x = player_pos_x_ - item_pos_x_;
	float y = player_pos_y_ - item_pos_y_;
	float z = player_pos_z_ - item_pos_z_;

	float c = sqrtf(x * x + y * y + z * z);

	float sum_radius = player_radius + item_radius;

	//�v���C���[�ƃA�C�e���̔��a�̍��v��2�̋������Z��������true
	if (c <= sum_radius)
	{
		return true;
	}
	else
		false;
}

//�����̂Ƌ��̔���
bool Collision::HitItemBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float item_pos_x_, float item_pos_y_, float item_pos_z_, float block_width_, float item_radius_)
{
	if (item_pos_x_ + item_radius_ >= block_pos_x_ - (block_width_ / 2) && item_pos_x_ - item_radius_ <= block_pos_x_ + (block_width_ / 2)
		&& item_pos_y_ + item_radius_ >= block_pos_y_ - (block_width_ / 2) && item_pos_y_ - item_radius_ <= block_pos_y_ + (block_width_ / 2)
		&& item_pos_z_ + item_radius_ >= block_pos_z_ - (block_width_ / 2) && item_pos_z_ - item_radius_ <= block_pos_z_ + (block_width_ / 2))
	{
		return true;
	}

	return false;
}

#pragma region �u���b�N�ƃv���C���[
//�����̂Ƌ��̔���
bool Collision::HitBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_width_, float player_radius_)
{
	if (player_pos_x_ + player_radius_ >= block_pos_x_ - (block_width_ / 2) && player_pos_x_ - player_radius_ <= block_pos_x_ + (block_width_ / 2)
		&& player_pos_y_ + player_radius_ >= block_pos_y_ - (block_width_ / 2) && player_pos_y_ - player_radius_ <= block_pos_y_ + (block_width_ / 2)
		&& player_pos_z_ + player_radius_ >= block_pos_z_ - (block_width_ / 2) && player_pos_z_ - player_radius_ <= block_pos_z_ + (block_width_ / 2))
	{
		return true;
	}

	return false;
}

#pragma region �g��Ȃ�
//bool Collision::HitBox(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_,
//	float block_height, float block_wight_, float block_depth_, float player_radius_)
//{
//	//���Ɨ����̂̏㉺����
//	if (HitBox(block_pos_x_, block_pos_y_, block_pos_z_, player_pos_x_, player_pos_y_, player_pos_z_, block_height, block_wight_, block_depth_, player_radius_) == true)
//	{
//		return true;
//	}
//	//���Ɨ����̂̍��E����
//	if (HitBoxRightLeft(block_pos_x_, block_pos_y_, block_pos_z_, player_pos_x_, player_pos_y_, player_pos_z_, block_height, block_wight_, block_depth_, player_radius_) == true)
//	{
//		return true;
//	}
//	//���Ɨ����̂̑O�㔻��
//	if (HitBoxInnerBack(block_pos_x_, block_pos_y_, block_pos_z_, player_pos_x_, player_pos_y_, player_pos_z_, block_height, block_wight_, block_depth_, player_radius_) == true)
//	{
//		return true;
//	}
//}



//�����̂Ƌ���Y������
//bool Collision::HitBoxTopUnder(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_width_, float player_radius_)
//{
//	if (player_pos_x_ >= block_pos_x_ - (block_width_ / 2) && player_pos_x_ <= block_pos_x_ + (block_width_ / 2)
//		&& player_pos_y_ + player_radius_ >= block_pos_y_ - (block_width_ / 2) && player_pos_y_ - player_radius_ <= block_pos_y_ + (block_width_ / 2)
//		&& player_pos_z_ >= block_pos_z_ + (block_width_ / 2) && player_pos_z_ <= block_pos_z_ - (block_width_ / 2))
//	{
//		return true;
//	}
//
//	return false;
//}

//�����̂Ƌ���X������
//bool Collision::HitBoxRightLeft(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_, float block_width_, float player_radius_)
//{
//	if (player_pos_x_ + player_radius_ >= block_pos_x_ - (block_width_ / 2) && player_pos_x_ - player_radius_ <= block_pos_x_ + (block_width_ / 2)
//		&& player_pos_y_ >= block_pos_y_ - (block_width_ / 2) && player_pos_y_ <= block_pos_y_ + (block_width_ / 2)
//		&& player_pos_z_ >= block_pos_z_ + (block_width_ / 2) && player_pos_z_ <= block_pos_z_ - (block_width_ / 2))
//	{
//		return true;
//	}
//	return false;
//}

//�����̂Ƌ���Z������
//bool Collision::HitBoxInnerBack(float block_pos_x_, float block_pos_y_, float block_pos_z_, float player_pos_x_, float player_pos_y_, float player_pos_z_,  float block_width_, float player_radius_)
//{
//	if (player_pos_x_ >= block_pos_x_ - (block_width_ / 2) && player_pos_x_ <= block_pos_x_ + (block_width_ / 2)
//		&& player_pos_y_ >= block_pos_y_ - (block_width_ / 2) && player_pos_y_ <= block_pos_y_ + (block_width_ / 2)
//		&& player_pos_z_ + player_radius_ >= block_pos_z_ - (block_width_ / 2) && player_pos_z_ - player_radius_ <= block_pos_z_ + (block_width_ / 2))
//	{
//		return true;
//	}
//	return false;
//}
#pragma endregion

#pragma endregion

//�~�Ɠ��ډ~�̂����蔻��
bool Collision::HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_, float player_circle_radius_, float map_circle_radius_)
{
	//�S�̂��ォ�猩�ăv���C���[�ƕǂ͉~�ł��邩��

	float x = player_circle_pos_x_ - map_circle_pos_x_;
	float z = player_circle_pos_z_ - map_circle_pos_z_;

	float c = sqrtf(x * x + z * z);

	float sub_radius = player_circle_radius_ - map_circle_radius_;

	if (c >= sub_radius)
	{
		return true;
	}
	else
		false;
}


bool Collision::HitBox1(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_depth_)
{
	//�O��
	if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, 0.0f, block_depth_, 0.0f, 0.0f, 1.0f) == true)
	{
		return true;
	}
	//���
	if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, 0.0f, -block_depth_, 0.0f, 0.0f, -1.0f) == true)
	{
		return true;
	}
	//����
	if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, -block_width_, 0.0f, -1.0f, 0.0f, 0.0f) == true)
	{
		return true;
	}
	//�E��
	if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, block_width_, 0.0f, 1.0f, 0.0f, 0.0f) == true)
	{
		return true;
	}
}

bool Collision::HitBox2(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_depth, float x, float y, float z)
{
	//�����̖̂ʂ̒��_
	D3DXVECTOR3 P(block_pos_x_ + block_width_ / 2, block_pos_y_, block_pos_z_ + block_depth / 2);

	//�@���x�N�g��
	D3DXVECTOR3 N(x, y, z);

	//���K��
	float lenght = sqrtf(N.x * N.x + N.y * N.y * N.z * N.z);

	N.x = N.x / lenght;
	N.y = N.y / lenght;
	N.z = N.z / lenght;

	//�J����Pos
	D3DXVECTOR3 PA(P.x - p_camera->GetCamaraPos().x, P.y - p_camera->GetCamaraPos().x, P.z - p_camera->GetCamaraPos().z);
	//�����_Pos
	D3DXVECTOR3 PB(P.x - p_camera->GetEyePos().x, P.y - p_camera->GetEyePos().y, P.z - p_camera->GetEyePos().z);

	//���ς����߂�
	float dot_PA = (PA.x * N.x) + (PA.y * N.y) + (PA.z * N.z);
	float dot_PB = (PB.x * N.x) + (PB.y * N.y) + (PB.z * N.z);

	if (dot_PA * dot_PB <= 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//�v���C���[�ƓV��
bool Collision::HitAngle(float player_pos_x, float player_pos_y, float player_pos_z, float maptop_pos_x, float maptop_pos_y, float maptop_pos_z, float mapunder_pos_x, float mapunder_pos_y, float mapunder_pos_z, float flg_angle)
{
	D3DXVECTOR3 player_vec;
	D3DXVECTOR3 map_vec;

	player_vec.x = player_pos_x - maptop_pos_x;
	player_vec.y = player_pos_y - maptop_pos_y;
	player_vec.z = player_pos_z - maptop_pos_z;

	map_vec.x = maptop_pos_x - mapunder_pos_x;
	map_vec.y = maptop_pos_y - mapunder_pos_y;
	map_vec.z = maptop_pos_z - mapunder_pos_z;


	float angle = acosf((player_vec.x * map_vec.x + player_vec.y * map_vec.y + player_vec.z * map_vec.z) /
		(sqrtf(player_vec.x * player_vec.x) * sqrtf(player_vec.y * player_vec.y) * sqrtf(player_vec.z * player_vec.z)));


	if (angle >= flg_angle)
	{
		return true;
	}
	else
		return false;
}