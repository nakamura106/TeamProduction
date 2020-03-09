#include "Collision.h"
#include <math.h>
#include <d3dx9.h>

//�v���C���[�ƃA�C�e��
 bool Collision::HitItem(float circleA_pos_x, float circleA_pos_y, float circleA_pos_z, float circleB_pos_x, float circleB_pos_y, float circleB_pos_z, float circleA_radius, float circleB_radius)
 {
	 float x = circleA_pos_x - circleB_pos_x;
	 float y = circleA_pos_y - circleB_pos_y;
	 float z = circleA_pos_z - circleB_pos_z;

	 float c = sqrtf(x * x + y * y + z * z);

	 float sum_radius = circleA_radius + circleB_radius;

	 if (c <= sum_radius)
	 {
		 return true;
	 }
	 else
		 false;
 }

#pragma region �u���b�N�ƃv���C���[
 bool Collision::HitBox(float block_pos_x, float block_pos_y, float block_pos_z, float ball_center_pos_x, float ball_center_pos_y, float ball_center_pos_z,
	 float block_height, float block_wight, float block_depth, float ball_radius_top, float ball_radius_under, float ball_radius_left, float ball_radius_right,
	 float ball_radius_inner, float ball_radius_back)
 {
	 if (HitBoxTopUnder(block_pos_x, block_pos_y, block_pos_z, ball_center_pos_x, ball_center_pos_y, ball_center_pos_z, block_height, block_wight, block_depth, ball_radius_top, ball_radius_under) == true)
	 {
		 return true;
	 }


	 if (HitBoxRightLeft(block_pos_x, block_pos_y, block_pos_z, ball_center_pos_x, ball_center_pos_y, ball_center_pos_z, block_height, block_wight, block_depth, ball_radius_left, ball_radius_right) == true)
	 {
		 return true;
	 }
 
	 if (HitBoxInnerBack(block_pos_x, block_pos_y, block_pos_z, ball_center_pos_x, ball_center_pos_y, ball_center_pos_z, block_height, block_wight, block_depth, ball_radius_inner, ball_radius_back) == true)
	 {
		 return true;
	 }
 }

 //�����̂Ƌ���Y������
 bool Collision:: HitBoxTopUnder(float block_pos_x, float block_pos_y, float block_pos_z, float ball_center_pos_x, float ball_center_pos_y, float ball_center_pos_z, float block_height, float block_wight, float block_depth, float ball_radius_top, float ball_radius_under)
 {
	 if (ball_center_pos_x >= block_pos_x && ball_center_pos_x <= block_pos_x + block_wight
		 && ball_center_pos_y >= block_pos_y - ball_radius_top && ball_center_pos_y <= block_pos_y + block_height + ball_radius_under
		 && ball_center_pos_z >= block_pos_z && ball_center_pos_z >= block_pos_z + block_depth)
	 {
		 return true;
	 }

	 return false;
 }

 //�����̂Ƌ���X������
 bool Collision::HitBoxRightLeft(float block_pos_x, float block_pos_y, float block_pos_z, float ball_center_pos_x, float ball_center_pos_y, float ball_center_pos_z, float block_height, float block_wight, float block_depth, float ball_radius_left, float ball_radius_right)
 {
	 if (ball_center_pos_x >= block_pos_x - ball_radius_left && ball_center_pos_x <= block_pos_x + block_wight + ball_radius_right
		 && ball_center_pos_y >= block_pos_y && ball_center_pos_y <= block_pos_y + block_height
		 && ball_center_pos_z >= block_pos_z && ball_center_pos_z >= block_pos_z + block_depth)
	 {
		 return true;
	 }
	 return false;
 }

 //�����̂Ƌ���Z������
 bool Collision::HitBoxInnerBack(float block_pos_x, float block_pos_y, float block_pos_z, float ball_center_pos_x, float ball_center_pos_y, float ball_center_pos_z, float block_height, float block_wight, float block_depth, float ball_radius_inner, float ball_radius_back)
 {
	 if (ball_center_pos_x >= block_pos_x && ball_center_pos_x <= block_pos_x + block_wight
		 && ball_center_pos_y >= block_pos_y && ball_center_pos_y <= block_pos_y + block_height
		 && ball_center_pos_z >= block_pos_z - ball_radius_inner && ball_center_pos_z >= block_pos_z + block_depth + ball_radius_back)
	 {
		 return true;
	 }
	 return false;
 }
#pragma endregion

 //�~�Ɠ��ډ~�̂����蔻��
 bool Collision::HitMap(float player_circle_pos_x_, float player_circle_pos_z_, float map_circle_pos_x_, float map_circle_pos_z_,float player_circle_radius_,float map_circle_radius)
 {
	 float x = player_circle_pos_x_ - map_circle_pos_x_;
	 float z = player_circle_pos_z_ - map_circle_pos_z_;

	 float c = sqrtf(x * x + z * z);

	 float sub_radius = player_circle_radius_ - map_circle_radius;

	 if (c >= sub_radius)
	 {
		 return true;
	 }
	 else
		 false;
 }


 bool Collision::HitBox1(float block_pos_x_, float block_pos_y_,float block_pos_z_,float block_width_,float block_height_,float block_depth,float x, float y, float z)
 {
	 //�O��
	 if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, block_width_, block_height_, 0.0f, 0.0f, 0.0f, 1.0f) == true)
	 {
		 return true;
	 }
	 //���
	 if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, block_width_, block_height_, (block_depth * 2), 0.0f, 0.0f, -1.0f) == true)
	 {
		 return true;
	 }
	 //����
	 if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, 0.0f, block_height_, block_depth, -1.0f, 0.0f, 0.0f) == true)
	 {
		 return true;
	 }
	 //�E��
	 if (HitBox2(block_pos_x_, block_pos_y_, block_pos_z_, (block_width_ * 2), block_height_, block_depth, 1.0f, 0.0f, 0.0f) == true)
	 {
		 return true;
	 }
 }

 bool Collision::HitBox2(float block_pos_x_, float block_pos_y_, float block_pos_z_, float block_width_, float block_height_, float block_depth, float x, float y, float z)
{
	//�����̖̂ʂ̒��_
	 D3DXVECTOR3 P(block_pos_x_ + block_width_ / 2, block_pos_y_ + block_height_ / 2, -(block_pos_z_ + block_depth / 2));

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
